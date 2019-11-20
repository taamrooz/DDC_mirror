#include "Core.h"
#include "MoveSystem.h"
#include "InputSystem.h"
#include "RoomSystem.h"
#include "UserInput.h"
#include "AudioSystem.h"
#include <Renderer.h>
#include "RenderSystem.h"
#include "ShootSystem.h"
#include "CollisionSystem.h"
#include "MoveCharacterSystem.h"
#include "CollisionComponent.h"
#include "SceneManager.h"
#include "ComponentFactory.h"
#include "InventorySystem.h"

Core::Core(SceneManager* manager) : BaseScene(manager) {}
Core::~Core() = default;


bool Core::init()
{
	manager_ = std::make_unique<EntityManager>();

	systems_.push_back(std::make_unique<RoomSystem>(manager_.get()));
	systems_.push_back(std::make_unique<InputSystem>(manager_.get(), *this));
	systems_.push_back(std::make_unique<MoveCharacterSystem>(manager_.get()));
	systems_.push_back(std::make_unique<CollisionSystem>(manager_.get()));
	systems_.push_back(std::make_unique<AudioSystem>(manager_.get()));
	systems_.push_back(std::make_unique<ShootSystem>(manager_.get()));
	systems_.push_back(std::make_unique<MoveSystem>(manager_.get()));
	systems_.push_back(std::make_unique<RenderSystem>(manager_.get()));
	systems_.push_back(std::make_unique<InventorySystem>(manager_.get()));

	//const auto id = manager_->create_entity();
	//const auto id2 = manager_->create_entity();
	//
	//auto v1 = std::make_unique<VelocityComponent>(8, 8);
	//auto p1 = std::make_unique<PositionComponent>(50, 600);
	//auto v2 = std::make_unique<VelocityComponent>(0, 0);
	//auto p2 = std::make_unique<PositionComponent>(100, 250);
	//auto a1 = std::make_unique<AnimationComponent>("Animations/wizard_m_run.png", 4, 3);
	//auto a2 = std::make_unique<AnimationComponent>("Animations/wizard_m_run.png", 4, 3);
	//auto q1 = std::make_unique<CollisionComponent>(48, 60, PlayerCollisionHandler);
	//auto q2 = std::make_unique<CollisionComponent>(48, 60, PlayerCollisionHandler);
	//auto s1 = std::make_unique<ShootingComponent>(7, 200);
	//
	//manager_->add_component_to_entity(id, std::move(v1));
	//manager_->add_component_to_entity(id, std::move(p1));
	//manager_->add_component_to_entity(id2, std::move(v2));
	//manager_->add_component_to_entity(id2, std::move(p2));
	//manager_->add_component_to_entity(id2, std::move(a2));
	//manager_->add_component_to_entity(id2, std::move(q2));
	//manager_->add_component_to_entity(id, std::move(a1));
	//manager_->add_component_to_entity(id, std::move(q1));
	//manager_->add_component_to_entity(id, std::move(s1));

	return true;
}

void Core::update()
{
	for (auto& system : systems_)
	{
		if(is_running)
		{
			system->update(1);

			if (is_paused) {
				Engine::StopMusic();
				is_paused = false;
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				scene_manager_->render();
			}
		}else
		{
			break;
		}
		
	}
}

void Core::render()
{
	auto timer = Engine::PreUpdate();
	update();
	Engine::Render(timer);
}

void Core::cleanup()
{
	if (manager_)
	{
		manager_ = nullptr;
	}
	systems_.clear();
}

void Core::StopGameLoop() {
	is_running = false;
}
