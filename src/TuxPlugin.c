#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include <sys/types.h>
#include <dirent.h>

#include <TuxStrings.h>
#include <TuxPlugin.h>
#include <TuxLib.h> /* IMPORT_FUNC() */
#include <TuxLogger.h>

#include <libxml/xmlreader.h>
#include <stdbool.h>


#ifdef _WIN32
	#include <windows.h> /* DLL management */
#else
	#include <dlfcn.h> /* SO management */
#endif


#define PLUGINS_DIRECTORY "./plugins/" /* répertoire où sont installés les plugins */


const xmlChar *name, *value;
char current_element[1024];


Plugin plg[100]; /* maximum de 100 plugin pour le moment (par la suite il faudra faire une allocation automatique) */
int plg_count;


char *win32_file;
char *linux_file;
char *plugin_name;
char *plugin_author;
char *plugin_version;

/*
	<win32_file>Plugin.dll</win32_file>
	<linux_file>Plugin.so</linux_file>

	<name>Plugin de test</name>
	<author>Joel Matteotti</name>
	<version>1.0.0</version>
*/

/* Parsing events inXML file */
void TuxPluin_processNode(xmlTextReaderPtr reader) 
{
	name = xmlTextReaderConstName(reader);
	value = xmlTextReaderConstValue(reader);

	if (current_element != NULL && value != NULL)
	{
		if (!strcmp(current_element, "win32_file") && win32_file == NULL) 
		{
			win32_file = (char *)malloc(sizeof(char)*strlen((char *)value));
			sprintf(win32_file,"%s",(char *)value);
		}
		
		if (!strcmp(current_element, "linux_file") && linux_file == NULL) 
		{
			linux_file = (char *)malloc(sizeof(char)*strlen((char *)value));
			sprintf(linux_file,"%s",(char *)value);
		}

		if (!strcmp(current_element, "name") && plugin_name == NULL) 
		{
			plugin_name = (char *)malloc(sizeof(char)*strlen((char *)value));
			sprintf(plugin_name,"%s",(char *)value);
		}
		
		if (!strcmp(current_element, "version") && plugin_version == NULL) 
		{
			plugin_version = (char *)malloc(sizeof(char)*strlen((char *)value));
			sprintf(plugin_version,"%s",(char *)value);
		}

		if (!strcmp(current_element, "author") && plugin_author == NULL) 
		{
			plugin_author = (char *)malloc(sizeof(char)*strlen((char *)value));
			sprintf(plugin_author,"%s",(char *)value);
		}
		
		value = NULL;
	}
	
	if (name != NULL) 
	{
		if (!strcmp((char *) name, "win32_file") 
			|| !strcmp((char *) name, "linux_file")
			|| !strcmp((char *) name, "name")
			|| !strcmp((char *) name, "author")
			|| !strcmp((char *) name, "version"))
		{
			strcpy(current_element, (char *) name);
		}

		name = NULL;
	}
}

bool TuxPluin_ParseXMLFile(const char *xmlfile) 
{
	bool result = true;

	xmlTextReaderPtr reader;
	int ret;

	reader = xmlReaderForFile(xmlfile, NULL, 0);
	if (reader != NULL) 
	{
		ret = xmlTextReaderRead(reader);
		while (ret == 1) 
		{
			TuxPluin_processNode(reader);
			ret = xmlTextReaderRead(reader);
		}
		xmlFreeTextReader(reader);

		if (ret != 0) 
		{
			result = false;
			TuxLogger_Error( "Can't open xml file %s",xmlfile);
		}
	}
	else 
	{
		result = false;
		TuxLogger_Error( "Can't open xml file %s", xmlfile);
	}

	return result;
}



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
	
	
	plg->setCallback = (setCallback_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setCallback");
	plg->processesData = (processesData_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"processesData");
	plg->Initialize = (Initialize_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"Initialize");
	
	return plg;
}

char *getExtension(char *file)
{
	int size = strlen(file);

	char *ext = (char *)malloc(sizeof(char)*4);
	sprintf(ext,"%c%c%c%c",file[size-4],file[size-3],file[size-2],file[size-1]);	

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
					
							if(!strcmp(getExtension(ep2->d_name),".xml"))
							{
								if(TuxPluin_ParseXMLFile(file))
								{
									plugins[plg_count] = (Plugin)malloc(sizeof(Plugin_t));
									
									//load le plugin depuis les infos
									plugins[plg_count]->name = plugin_name;
									plugins[plg_count]->author = plugin_author;
									plugins[plg_count]->version = plugin_version;
									
									#ifdef _WIN32
									file = (char *)malloc(sizeof(char *)*strlen(win32_file)+strlen(PLUGINS_DIRECTORY)+strlen(ep->d_name));
									sprintf(file,"%s%s/%s",PLUGINS_DIRECTORY,ep->d_name,win32_file);
									#else
									file = (char *)malloc(sizeof(char *)*strlen(linux_file)+strlen(PLUGINS_DIRECTORY)+strlen(ep->d_name));
									sprintf(file,"%s%s/%s",PLUGINS_DIRECTORY,ep->d_name,linux_file);
									#endif
									
									
									free(plugin_name);
									free(plugin_author);
									free(plugin_version);
									
									
									plugins[plg_count] = loadPlugin(file);
									plugins[plg_count]->setCallback(PluginsCallback); // défini le callback pour chacun des plugins 
									plugins[plg_count]->Initialize();
									
									plg_count++;
								
								}
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


