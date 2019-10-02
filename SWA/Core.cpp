#include "Core.h"
#include "MoveSystem.h"
#include "InputSystem.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include <Windows.h>
#include "UserInput.h"
#include "AudioSystem.h"
#include <Renderer.h>
#include "RenderSystem.h"
#include "AnimationComponent.h"

Core Core::instance_;
Core::Core() = default;

bool Core::init(const char* title, int width, int height, bool fullscreen)
{
	if (!Engine::InitRenderer("PoC", false, 800, 600)) {
		return false;
	}
	if (!Engine::InitAudio()) {
		return false;
	}

	manager_ = std::make_unique<EntityManager>();
	input_component_ = std::make_unique<InputComponent>();
	systems_.push_back(std::make_unique<InputSystem>(manager_.get(), input_component_.get(), *this));
	systems_.push_back(std::make_unique<AudioSystem>(manager_.get(), input_component_.get()));
	systems_.push_back(std::make_unique<RenderSystem>(manager_.get()));
	systems_.push_back(std::make_unique<MoveSystem>(manager_.get()));

	std::vector<Component*> components;
	//components.push_back();
	const auto id = manager_->create_entity(components);
	const auto id2 = manager_->create_entity();
	
	auto v1 = std::make_unique<VelocityComponent>(14, -51);
	auto p1 = std::make_unique<PositionComponent>(50, 25);
	auto v2 = std::make_unique<VelocityComponent>(10.99, 0);
	auto p2 = std::make_unique<PositionComponent>(100, 250);
	auto a1 = std::make_unique<AnimationComponent>("wizard_move_m.png", 4);
	manager_->add_component_to_entity(id, std::move(v1));
	manager_->add_component_to_entity(id, std::move(p1));
	manager_->add_component_to_entity(id2, std::move(v2));
	manager_->add_component_to_entity(id2, std::move(p2));
	manager_->add_component_to_entity(id, std::move(a1));

	const auto createdComponent = manager_->get_component<PositionComponent>(id2);
	std::cout << createdComponent->x << std::endl;
	std::cout << createdComponent->y << std::endl;
	const auto createdComponent2 = manager_->get_component<VelocityComponent>(id2);
	std::cout << createdComponent2->dx << std::endl;
	std::cout << createdComponent2->dy << std::endl;
	auto list = manager_->get_all_entities<VelocityComponent>();
	for (auto l : list)
	{
		std::cout << l << std::endl;
	}
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
	if (!init("Playground", 800, 600, false))
	{
		return 0;
	}

	while (is_running_)
	{
		Engine::RenderClear();
		update();
		Engine::Render();
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
