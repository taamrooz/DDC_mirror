#include "RenderSystem.h"
#include "Renderer.h"
#include "AnimationComponent.h"
#include "CharacterComponent.h"
#include "VelocityComponent.h"
RenderSystem::RenderSystem(EntityManager* manager) : BaseSystem(manager) {

}

void RenderSystem::update(double dt)
{
	auto character_entity = manager_->get_all_entities<CharacterComponent>().front();
	auto character_velocity_component = manager_->get_component<VelocityComponent>(character_entity);

	for (auto entityid : manager_->get_all_entities<AnimationComponent>()) {

		auto animation_component = manager_->get_component<AnimationComponent>(entityid);
		if (!animation_component.is_active) {
			//animation_component.animation = Engine::LoadAnimation(animation_component.filename);
			animation_component.is_active = true;
		}
		if (entityid == character_entity) {
			if (character_velocity_component.dx < 0) {
				// is moving left
			} else if (character_velocity_component.dx > 0) {
				// is moving right
			}
			else if (character_velocity_component.dy < 0) {
				// is moving up
			}
			else if (character_velocity_component.dx > 0) {
				// is moving down
			}

			Engine::UpdateAnimation(&animation_component.animation);

		}
		else {
			Engine::UpdateAnimation(&animation_component.animation);
		}
	}
}