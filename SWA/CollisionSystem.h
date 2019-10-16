#include "BaseSystem.h"

class CollisionSystem :
	public BaseSystem
{
public:
	CollisionSystem(EntityManager* manager);
	void update(double dt) override;
};

