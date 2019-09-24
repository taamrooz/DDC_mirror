#include "Core.h"
#include "EntityManager.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#undef main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char* argv[])
{
	Core::get_instance()->execute(argc, argv);

	//Testing ECS
	auto manager = EntityManager();
	auto c = position_component(50, 25);
	auto v = velocity_component(25.14, -51);
	auto v2 = velocity_component(10.99, 0);
	std::vector<component*> components;
	components.push_back(&c);
	int id = manager.create_entity(components);
	std::vector<component*> components2;
	int id2 = manager.create_entity(components2);
	
	manager.add_component_to_entity(id, v);
	manager.add_component_to_entity(id2, v2);


	auto createdComponent = manager.get_component<position_component>(id);
	std::cout << createdComponent.x << std::endl;
	std::cout << createdComponent.y << std::endl;
	auto createdComponent2 = manager.get_component<velocity_component>(id);
	std::cout << createdComponent2.dx << std::endl;
	std::cout << createdComponent2.dy << std::endl;
	auto list = manager.get_all_entities<velocity_component>();
	for(auto l : list)
	{
		std::cout << l << std::endl;
	}
	return 0;
}