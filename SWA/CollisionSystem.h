#include "BaseSystem.h"
#include "QuadTree.h"

class CollisionSystem :
	public BaseSystem
{
public:
	CollisionSystem(EntityManager* manager);
	void update(double dt) override;
	void update_velocity(Node* first_node, Node* second_node);
};

