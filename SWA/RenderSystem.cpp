#include "RenderSystem.h"
#include "Renderer.h"
#include "AnimationComponent.h"
RenderSystem::RenderSystem(EntityManager* manager) : BaseSystem(manager) {

}

void RenderSystem::update(double dt)
{
	auto e = manager->get_all_entities<AnimationComponent>();
	for (const auto& entityid : e) {
		auto animation_component = manager->get_component<AnimationComponent>(entityid);
		if (!animation_component.is_active) {
			//animation_component.animation = Engine::LoadAnimation(animation_component.filename);
			animation_component.is_active = true;
		}
		Engine::UpdateAnimation(&animation_component.animation);
	}	
}