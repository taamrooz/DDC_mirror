#include "Core.h"
#include "crtdbg.h"
#undef main

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char* argv[])
{
	Core::get_instance()->execute(argc, argv);
	_CrtDumpMemoryLeaks();
	return 0;
}