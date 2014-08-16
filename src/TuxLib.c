
#include <TuxLib.h>

//importation de fonctions depuis une lib (.so/.dll)
void *IMPORT_FUNC(void *HANDLE, const char *func)
{
	#ifdef _WIN32
	return GetProcAddress(HANDLE,func);
	#else
	return dlsym(HANDLE,func);
	#endif
}
