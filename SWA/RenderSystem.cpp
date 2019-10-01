#include "RenderSystem.h"
#include "Renderer.h"
#include "AnimationComponent.h"
RenderSystem::RenderSystem(EntityManager* manager) : BaseSystem(manager) {

}

void RenderSystem::update(double dt)
{
	for (auto entityid : manager_->get_all_entities<AnimationComponent>()) {
		auto animation_component = manager_->get_component<AnimationComponent>(entityid);
		if (!animation_component.is_active) {
			//animation_component.animation = Engine::LoadAnimation(animation_component.filename);
			animation_component.is_active = true;
		}
		Engine::UpdateAnimation(&animation_component.animation);
	}
}