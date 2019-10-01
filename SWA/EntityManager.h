#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include "Component.h"
#include <iostream>
#include <typeindex>
#include <unordered_map>

class EntityManager
{
private:
	int id_ = -1;
	std::vector<uint32_t> entities_;
	std::unordered_map <size_t, std::unordered_map<uint32_t, std::shared_ptr<Component>>> components_by_class_;

public:
	uint32_t create_entity();
	uint32_t create_entity(std::vector<Component*>&);
	void add_component_to_entity(uint32_t, std::shared_ptr<Component> comp);
	void remove_entity(uint32_t id);

	
	template<class T>
	void remove_component_from_entity(const uint32_t id)
	{
		const auto type = typeid(T).hash_code();
		components_by_class_[type].erase(id);
	}
	template<class T>
	T& get_component(const uint32_t id)
	{
		const auto type = typeid(T).hash_code();
		return *static_cast<T*>(components_by_class_[type][id].get());
	}
	template<class T>
	std::vector<uint32_t> get_all_entities()
	{
		//TODO: use boost iterator instead of vector
		std::vector<uint32_t> list;
		const auto type = typeid(T).hash_code();
		if(components_by_class_.find(type) != components_by_class_.end())
		{
			for (auto i = components_by_class_[type].begin(); i != components_by_class_[type].end(); ++i)
			{
				list.push_back(i->first);
			}
		}
		return list;
	}

};
