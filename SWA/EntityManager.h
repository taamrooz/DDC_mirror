#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include "Component.h"
#include <memory>
#include <iostream>

class EntityManager
{
private:
	uint32_t _id = 0;
	std::vector<uint32_t> _entities;
	std::map < std::string, std::map<uint32_t, component*>> _componentsByClassName;

public:
	uint32_t create_entity(const std::vector<component*>&);
	void add_component_to_entity(uint32_t, component&);
	void remove_entity(uint32_t id);

	
	template<class T>
	void remove_component_from_entity(const uint32_t id)
	{
		const auto type = typeid(T).name();
		//auto index = _componentsByClassName[type].begin()+ id;
		_componentsByClassName[type].erase(id);
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
		if(_componentsByClassName.find(type) != _componentsByClassName.end())
		{
			for (auto i = _componentsByClassName[type].begin(); i != _componentsByClassName[type].end(); ++i)
			{
				list.push_back(i->first);
			}
		}
		
		return list;
	}

};
