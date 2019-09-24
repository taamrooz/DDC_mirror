#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include "Component.h"
#include <memory>

class EntityManager
{
private:
	uint32_t _id = 0;
	std::vector<uint32_t> _entities;
	std::map < std::string, std::vector<component*>> _componentsByClassName;

public:
	uint32_t create_entity(const std::vector<component*>&);
	void add_component_to_entity(uint32_t, component&);
	void remove_entity(uint32_t id);
	template<class T>
	void remove_component_from_entity(const uint32_t id)
	{
		const auto type = typeid(T).name();
		auto index = _componentsByClassName[type].begin()+ id;
		_componentsByClassName[type].erase(index);
	}
	template<class T>
	T& get_component(uint32_t id)
	{
		std::string type = typeid(T).name();
		return *static_cast<T*>(_componentsByClassName[type][id]);
	}
	template<class T>
	std::vector<uint32_t> get_all_entities()
	{
		std::vector<uint32_t> list;
		const auto type = typeid(T).name();
		for (std::map<std::string, std::vector<component*>>::iterator it = _componentsByClassName.begin(); it != _componentsByClassName.end(); ++it)
		{
			if(type == it->first)
			{
				for(auto& c : it->second)
				{
					list.push_back(static_cast<int32_t>(&c - &it->second[0]));
				}
			}
		}
		return list;
	}

};
