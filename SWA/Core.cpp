#include "Core.h"
#include "MoveSystem.h"
#include "InputSystem.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "RoomSystem.h"
#include <Windows.h>
#include "UserInput.h"
#include "AudioSystem.h"
#include <Renderer.h>
#include "RenderSystem.h"
#include "AnimationComponent.h"
#include "TileComponent.h"
#include "CollisionSystem.h"
#include "CharacterComponent.h"
#include "MoveCharacterSystem.h"
#include "CollisionComponent.h"

Core Core::instance_;
Core::Core() = default;

bool Core::init(const char* title, int width, int height, bool fullscreen)
{
	if (!Engine::InitRenderer(title, fullscreen, width, height)) {
		return false;
	}
	if (!Engine::InitAudio()) {
		return false;
	}

	manager_ = std::make_unique<EntityManager>();

	systems_.push_back(std::make_unique<RoomSystem>(manager_.get()));
	systems_.push_back(std::make_unique<InputSystem>(manager_.get(), *this));
	systems_.push_back(std::make_unique<MoveCharacterSystem>(manager_.get()));
	systems_.push_back(std::make_unique<AudioSystem>(manager_.get()));
	systems_.push_back(std::make_unique<MoveSystem>(manager_.get()));
	systems_.push_back(std::make_unique<RenderSystem>(manager_.get()));
	systems_.push_back(std::make_unique<CollisionSystem>(manager_.get()));


	//// <----- PLACEHOLDER FOR ENTITY FACTORY - ENTITIES TO TEST WITH ----->  ////
	const auto id = manager_->create_entity();
	const auto id2 = manager_->create_entity();	
	auto v1 = std::make_shared<VelocityComponent>(0, 0);
	auto p1 = std::make_shared<PositionComponent>(50, 600);
	auto v2 = std::make_shared<VelocityComponent>(0, 0);
	auto p2 = std::make_shared<PositionComponent>(100, 250);
	auto a1 = std::make_shared<AnimationComponent>("Animations/wizard_m_run.png", 4, 4);
	auto a2 = std::make_shared<AnimationComponent>("Animations/wizard_m_run.png", 4, 4);
	auto c1 = std::make_shared<CharacterComponent>();
	auto q1 = std::make_shared<CollisionComponent>(200, 200);
	auto q2 = std::make_shared<CollisionComponent>(200, 200);
	manager_->add_component_to_entity(id, v1);
	manager_->add_component_to_entity(id, p1);
	manager_->add_component_to_entity(id2, v2);
	manager_->add_component_to_entity(id2, p2);
	manager_->add_component_to_entity(id2, a2);
	manager_->add_component_to_entity(id2, q2);
	manager_->add_component_to_entity(id, a1);
	manager_->add_component_to_entity(id, c1);
	manager_->add_component_to_entity(id, q1);
	//// <----- PLACEHOLDER FOR ENTITY FACTORY - ENTITIES TO TEST WITH ----->  ////

	return true;
}

void Core::update()
{
	for (auto& system : systems_)
	{
		system->update(1);
	}
}

int Core::execute(int argc, char* argv[])
{
	if (!init("Demonic Dungeon Castle", 1280, 960, false))
	{
		return 0;
	}

	while (is_running_)
	{
		auto timer = Engine::PreUpdate();
		update();
		Engine::Render(timer);
	}

	cleanup();

	return 1;
}

Core* Core::get_instance()
{
	return &Core::instance_;
}

void Core::cleanup()
{
	Engine::DestroyRenderer();
	if (manager_)
	{
		manager_ = nullptr;
	}
	systems_.clear();

	Engine::CloseAudio();
}

void Core::StopGameLoop() {
	is_running_ = false;
}
