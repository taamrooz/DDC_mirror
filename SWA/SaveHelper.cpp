#include "SaveHelper.h"

void SaveHelper::SaveGameToFile(Engine::EntityManager<Component>* manager_)
{
	auto json = Engine::get_json();
	auto entities = manager_->get_all_entities();

	for (auto entity : entities)
	{
		auto components = manager_->get_all_components_from_entity(entity);
		for (auto c : components)
		{
			c->ToJson(json, entity);
		}
	}

	Engine::write_to_file(json, "assets/json/test_save");
}
