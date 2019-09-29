#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include "Component.h"
#include <iostream>

class EntityManager
{
private:
	int id_ = -1;
	std::vector<uint32_t> entities_;
	std::map < std::string, std::map<uint32_t, std::shared_ptr<Component>>> components_by_class_;

public:
	uint32_t create_entity();
	uint32_t create_entity(const std::vector<std::shared_ptr<Component>>&);
	void add_component_to_entity(uint32_t, const std::shared_ptr<Component>& comp);
	void remove_entity(uint32_t id);

	
	template<class T>
	void remove_component_from_entity(const uint32_t id)
	{
		const auto type = typeid(T).name();
		components_by_class_[type].erase(id);
	}
	template<class T>
	T& get_component(const uint32_t id)
	{
		const std::string type = typeid(T).name();
		return *static_cast<T*>(components_by_class_[type][id].get());
	}
	template<class T>
	std::vector<uint32_t> get_all_entities()
	{
		std::vector<uint32_t> list;
		const auto type = typeid(T).name();
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
