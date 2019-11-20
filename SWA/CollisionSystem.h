#include "BaseSystem.h"
#include "QuadTree.h"
#include "Core.h"

class CollisionSystem :
	public BaseSystem
{
public:
	CollisionSystem(EntityManager* manager, Core& core);
	void update(double dt) override;
	void update_velocity(Node* first_node, Node* second_node);
private:
	Core* core;
};

