#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include <sys/types.h>
#include <dirent.h>

#include <TuxStrings.h>
#include <TuxPlugin.h>
#include <TuxLib.h> /* IMPORT_FUNC() */

#ifdef _WIN32
	#include <windows.h> /* DLL management */
#else
	#include <dlfcn.h> /* SO management */
#endif


#define PLUGINS_DIRECTORY "./plugins/" /* répertoire où sont installés les plugins */


#ifdef _WIN32
	#define PLUGIN_EXT ".dll"
#else
	#define PLUGIN_EXT ".so"
#endif

Plugin plg[100]; /* maximum de 100 plugin pour le moment (par la suite il faudra faire une allocation automatique) */
int plg_count;




//fonction de chargement des plugins
Plugin loadPlugin(char *file)
{
	void* DLLHANDLE;

	#ifdef _WIN32
	DLLHANDLE = LoadLibrary(file);
	#else
	DLLHANDLE = dlopen(file, RTLD_NOW);
	#endif
	
	Plugin plg = (Plugin)malloc(sizeof(Plugin_t));
	
	plg->getName = (getName_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"getName");
	plg->getVersion = (getVersion_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"getVersion");
	plg->getAuthor = (getAuthor_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"getAuthor");
	plg->setCallback = (setCallback_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setCallback");
	plg->processesData = (processesData_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"processesData");
	plg->Initialize = (Initialize_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"Initialize");
	
	return plg;
}

char *getExtension(char *file)
{
	int size = strlen(file);
	
	#ifdef _WIN32
		char *ext = (char *)malloc(sizeof(char)*4);
		sprintf(ext,"%c%c%c%c",file[size-4],file[size-3],file[size-2],file[size-1]);	
	#else
		char *ext = (char *)malloc(sizeof(char)*3);
		sprintf(ext,"%c%c%c",file[size-3],file[size-2],file[size-1]);	
	#endif
	
	return ext;
}

/* fonction de callback qui sera appellée par tous les plugins */
void PluginsCallback(void *data)
{
	printf("callback => %s\n",(char *)data);
}

/* charge tous les plugins */
int loadAllPlugin(Plugin plugins[])
{
	DIR *dp;
	DIR *dp2;
	
	struct dirent *ep;
	struct dirent *ep2;
	
	int plg_count=0;

	FILE *fp;
	char *dir;
	
	char *file;
	
	dp = opendir (PLUGINS_DIRECTORY);
	if (dp != NULL)
	{
		while (ep = readdir (dp))
		{
			if(strcmp(ep->d_name,".") && strcmp(ep->d_name,".."))
			{
				dir = (char *)malloc(sizeof(char)*strlen(PLUGINS_DIRECTORY)+strlen(ep->d_name)+2);
				sprintf(dir,"%s%s/",PLUGINS_DIRECTORY,ep->d_name);
				
				dp2 = opendir(dir);
				
				if(dp2 != NULL)
				{
					while(ep2 = readdir(dp2))
					{
						file = (char *)malloc(sizeof(char)*strlen(PLUGINS_DIRECTORY)+strlen(ep->d_name)+strlen(ep2->d_name)+2);
						sprintf(file,"%s%s/%s",PLUGINS_DIRECTORY,ep->d_name,ep2->d_name);
	
						if(fp = fopen(file,"r")) //vérifie que c'est bien un fichier et non un répertoire
						{
							fclose(fp);
					
							if(!strcmp(getExtension(ep2->d_name),PLUGIN_EXT))
							{
								plugins[plg_count] = loadPlugin(replace(file,PLUGIN_EXT,""));
								plugins[plg_count]->setCallback(PluginsCallback); // défini le callback pour chacun des plugins 
								plugins[plg_count]->Initialize();
						
								plg_count++;
							}
						}			
				
					}
				}
				(void)closedir(dp2);
			}
		}
		
		(void) closedir (dp);
	}
	else
		perror ("Couldn't open the directory");

	return plg_count;
}


