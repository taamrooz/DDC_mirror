#include "Core.h"
#include "crtdbg.h"
#ifdef _DEBUG
#undef main
#endif
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char* argv[])
{
	Core::get_instance()->execute(argc, argv);
	//_CrtDumpMemoryLeaks();
	return 0;
}