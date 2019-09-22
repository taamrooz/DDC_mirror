#include "Core.h"
#undef main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char* argv[])
{
	Core::getInstance()->execute(argc, argv);
	return 0;
}