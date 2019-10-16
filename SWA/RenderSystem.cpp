#include "RenderSystem.h"
#include "Renderer.h"
#include "AnimationComponent.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
RenderSystem::RenderSystem(EntityManager* manager) : BaseSystem(manager) {

}

void RenderSystem::update(double dt)
{
	for (auto entityid : manager_->get_all_entities<AnimationComponent>()) {
		auto animation_component = manager_->get_component<AnimationComponent>(entityid);
		auto position_component = manager_->get_component<PositionComponent>(entityid);
		if (!animation_component.is_active) {
			//animation_component.animation = Engine::LoadAnimation(animation_component.filename);
			animation_component.is_active = true;
		}

		// TO-DO: fix the booleans
		bool should_flip_horizontally = false;
		bool should_flip_vertically = false;
		Engine::UpdateAnimation(&animation_component.animation, position_component.x, position_component.y, should_flip_horizontally, should_flip_vertically);
	}
}