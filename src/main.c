#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
	#include <windows.h> /* DLL management */
#else
	#include <dlfcn.h> /* SO management */
#endif

//importation de fonctions depuis une lib (.so/.dll)
void *IMPORT_FUNC(void *HANDLE, const char *func)
{
	#ifdef _WIN32
	return GetProcAddress(HANDLE,func);
	#else
	return dlsym(HANDLE,func);
	#endif
}

int main(int argc, char *argv[]) 
{
	//typedef char *(*getName_t)(void);
	//	plg->getName = (getName_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"getName");
	
	void* DLLHANDLE;

	#ifdef _WIN32
	DLLHANDLE = LoadLibrary("./TuxDroidServer.dll");
	#else
	DLLHANDLE = dlopen("./TuxDroidServer.so", RTLD_NOW);
	#endif
	
	typedef void (*InitServer_t)(void);
	InitServer_t InitServer = (InitServer_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"InitServer");
	InitServer();

	return 0;
}
