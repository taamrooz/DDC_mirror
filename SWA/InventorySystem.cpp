#include "InventorySystem.h"
#include "UserInput.h"
#include "KeyBindingSingleton.h"
#include "InventoryComponent.h"
#include "CharacterComponent.h"
#include "CollectableComponent.h"

InventorySystem::InventorySystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager)
{}

void InventorySystem::update(double dt)
{
	auto entity = manager_->get_all_entities<CharacterComponent>().front();
	auto inv = manager_->get_component<InventoryComponent>(entity);
	for (auto i = KeyBindingSingleton::get_instance()->keys_down.begin(); i != KeyBindingSingleton::get_instance()->keys_down.end(); ++i)
	{
		if (i->first.compare("1") == 0) {
			if (i->second) {
				if (inv->selected == 1) {
					// use this inventory item
					if (inv->items.size() > 0) {
						auto collectable_entity_id = inv->items[0];
						auto collectable = manager_->get_component<CollectableComponent>(collectable_entity_id);
						collectable->utilizeHandler(entity, collectable_entity_id, manager_);
					}
				}

				inv->selected = 1;
				i->second = false;

			}
		}
		if (i->first.compare("2") == 0) {
			if (i->second) {
				inv->selected = 2;
				i->second = false;
			}
		}
		if (i->first.compare("3") == 0) {
			if (i->second) {
				inv->selected = 3;
				i->second = false;
			}
		}
		if (i->first.compare("4") == 0) {
			if (i->second) {
				inv->selected = 4;
				i->second = false;
			}
		}
		if (i->first.compare("5") == 0) {
			if (i->second) {
				inv->selected = 5;
				i->second = false;
			}
		}
		if (i->first.compare("6") == 0) {
			if (i->second) {
				inv->selected = 6;
				i->second = false;
			}
		}
		if (i->first.compare("7") == 0) {
			if (i->second) {
				inv->selected = 7;
				i->second = false;
			}
		}
		if (i->first.compare("8") == 0) {
			if (i->second) {
				inv->selected = 8;
				i->second = false;
			}
		}
		if (i->first.compare("9") == 0) {
			if (i->second) {
				inv->selected = 9;
				i->second = false;
			}
		}
		if (i->first.compare("10") == 0) {
			if (i->second) {
				inv->selected = 10;
				i->second = false;
			}
		}
	}
}