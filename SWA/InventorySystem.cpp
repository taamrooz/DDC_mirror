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
		if (i->second) {
			if (i->first == "1") {
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

			if (i->first == "2") {
				inv->selected = 2;
				i->second = false;
			}
			if (i->first == "3") {

				inv->selected = 3;
				i->second = false;

			}
			if (i->first == "4") {

				inv->selected = 4;
				i->second = false;

			}
			if (i->first == "5") {

				inv->selected = 5;
				i->second = false;

			}
			if (i->first == "6") {

				inv->selected = 6;
				i->second = false;

			}
			if (i->first == "7") {

				inv->selected = 7;
				i->second = false;

			}
			if (i->first == "8") {

				inv->selected = 8;
				i->second = false;

			}
			if (i->first == "9") {

				inv->selected = 9;
				i->second = false;

			}
			if (i->first == "10") {

				inv->selected = 10;
				i->second = false;

			}
		}
	}
}