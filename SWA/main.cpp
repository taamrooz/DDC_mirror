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
}