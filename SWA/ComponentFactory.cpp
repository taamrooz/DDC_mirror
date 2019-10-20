#include "ComponentFactory.h"
#include <iostream>
#include "PositionComponent.h"
#include "ControllableComponent.h"
#include "ShootingComponent.h"
#include "VelocityComponent.h"
#include "AnimationComponent.h"
#include "CharacterComponent.h"
#include "HealthComponent.h"

ComponentFactory::ComponentFactory() {

}

ComponentFactory* ComponentFactory::instance_ = 0;

enum string_code {
	cPlayer,
	cWall
};

string_code Convert(std::string const& inString) {
	if (inString == "player") return cPlayer;
	if (inString == "wall") return cWall;

	return cWall;
}

ComponentFactory* ComponentFactory::get_instance() {
	if (instance_ == 0)
	{
		instance_ = new ComponentFactory();
	}
	return instance_;
}

int ComponentFactory::CreateEntity(std::string name, int id, EntityManager* em) {
	switch (Convert(name)) {
	case cPlayer: {
		AddPlayerComponents(id, em);
		break;
	}
	case cWall: {

	}
	default: {
		//std::cout << "Error, entity name not found" << std::endl;
	}
	}
	return -1;
}

void ComponentFactory::AddPlayerComponents(int id, EntityManager* em) {
	//auto hea = std::make_unique<HealthComponent>();

	auto vel = std::make_unique<VelocityComponent>();
	auto ani = std::make_unique<AnimationComponent>("Animations/wizard_m_run.png", 4, 3);
	auto cha = std::make_unique<CharacterComponent>();
	em->add_component_to_entity(id, std::move(vel));
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(cha));
}