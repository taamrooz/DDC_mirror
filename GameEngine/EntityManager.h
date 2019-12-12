#pragma once
#include <cstdint>
#include <vector>
#include <iostream>
#include <typeindex>
#include <unordered_map>
#include "RoomComponent.h"
#include "RoomSingleton.h"
#include "DungeonSingleton.h"

namespace Engine {
	template<typename T> class EntityManager
	{
	private:
		int id_ = -1;
		std::vector<uint32_t> entities_;
		std::unordered_map <size_t, std::unordered_map<uint32_t, std::unique_ptr<T>>> components_by_class_;

	public:

		~EntityManager()
		{
			
		}
		
		template<typename C>
		void remove_component_from_entity(uint32_t id)
		{
			const auto type = typeid(C).hash_code();
			components_by_class_[type].erase(id);
		}

		template<typename C>
		C* get_component(uint32_t id) const
		{
			const auto type = typeid(C).hash_code();
			if (components_by_class_.find(type) != components_by_class_.end() && components_by_class_.find(type)->second.find(id) != components_by_class_.find(type)->second.end())
			{
				return static_cast<C*>(components_by_class_.find(type)->second.find(id)->second.get());
			}
			return nullptr;
		}

		template<typename C>
		std::vector<uint32_t> get_all_entities() const
		{
			//TODO: use boost iterator instead of vector
			std::vector<uint32_t> list;
			const auto type = typeid(C).hash_code();
			if (components_by_class_.find(type) != components_by_class_.end())
			{
				for (auto i = components_by_class_.at(type).begin(); i != components_by_class_.at(type).end(); ++i)
				{
					list.push_back(i->first);
				}
			}
			return list;
		}
		
		template<typename C>
		std::vector<uint32_t> get_all_entities_from_current_room() const
		{
			std::vector<uint32_t> list;
			const auto type = typeid(C).hash_code();
			if(components_by_class_.find(type) != components_by_class_.end())
			{
				for(auto i = components_by_class_.at(type).begin(); i != components_by_class_.at(type).end(); ++i)
				{
					auto room_component = get_component<RoomComponent>(i->first);
					if (room_component->room_index == DungeonSingleton::get_instance()->get_current_room_number())
					{
						list.push_back(i->first);
					}
				}
			}
			return list;
		}

		[[nodiscard]] std::vector<uint32_t> get_all_entities() const
		{
			return entities_;
		}

		std::vector<T*> get_all_components_from_entity(uint32_t id)
		{
			std::vector<T*> components {};
			for(auto &&i = components_by_class_.begin(); i != components_by_class_.end(); ++i)
			{
				auto component_iterator = i->second.find(id);
				if(component_iterator != i->second.end())
					components.emplace_back(component_iterator->second.get());
;			}
			return components;
		}

		uint32_t create_entity()
		{
			entities_.push_back(++id_);
			return id_;
		}

		uint32_t create_entity(std::vector<T*>& components)
		{
			entities_.push_back(++id_);
			for (auto& component : components)
			{
				add_component_to_entity(id_, std::make_unique<T>(*component));
			}
			return id_;
		}

		void add_component_to_entity(uint32_t id, std::unique_ptr<T> comp)
		{
			const auto& ref = *comp;
			const auto type = typeid(*&ref).hash_code();
			components_by_class_[type].insert_or_assign(id, std::move(comp));
		}

		void remove_entity(uint32_t id)
		{
			const auto i = std::find(entities_.begin(), entities_.end(), id);
			for (auto& comp : components_by_class_)
			{
				comp.second.erase(id);
			}
			entities_.erase(i);
		}
	};
}
