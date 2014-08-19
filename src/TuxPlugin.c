/* =============== GPL HEADER =====================
 * TuxPlugin.c is part of TuxDroidServer
 * Copyleft (C) 2012 - Joel Matteotti <joel _DOT_ matteotti _AT_ free _DOT_ fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 * ====================================================
*/

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
#include <TuxCommands.h>
#include <TuxServer.h>

#ifdef _WIN32
	#include <windows.h> /* DLL management */
#else
	#include <dlfcn.h> /* SO management */
#endif


#define PLUGINS_DIRECTORY "./plugins/" /* répertoire où sont installés les plugins */


const xmlChar *name, *value;
char current_element[1024];

tuxplugins plugins;

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
	
	plg->setIsServerStarted = (setIsServerStarted_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setIsServerStarted");
	plg->setCallback = (setCallback_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setCallback");
	plg->setTux_Open = (setTux_Open_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Open");
	plg->setTux_Close = (setTux_Close_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Close");
	plg->setTux_OpenClose = (setTux_OpenClose_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_OpenClose");
	plg->setTux_Leds_OnOff = (setTux_Leds_OnOff_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Leds_OnOff");
	plg->setTux_Leds_Blink = (setTux_Leds_Blink_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Leds_Blink");
	plg->setTux_Leds_Pulse = (setTux_Leds_Pulse_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Leds_Pulse");
	plg->setTux_Micro = (setTux_Micro_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Micro");
	plg->setTux_Audio = (setTux_Audio_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Audio");
	plg->setTux_Flippers = (setTux_Flippers_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Flippers");
	plg->setTux_Rotate = (setTux_Rotate_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Rotate");
	plg->setTux_Flash = (setTux_Flash_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Flash");
	plg->setTux_Sleep = (setTux_Sleep_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Sleep");
	plg->setTux_Wakeup = (setTux_Wakeup_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Wakeup");
	plg->setTux_Off = (setTux_Off_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Off");
	plg->setTux_Reset = (setTux_Reset_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_Reset");
	plg->setTux_TTS = (setTux_TTS_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_TTS");
	plg->setTux_State = (setTux_State_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"setTux_State");
	plg->onCommand = (onCommand_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"onCommand");
	plg->Initialize = (Initialize_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"Initialize");
	plg->onButtonPressed = (onButtonPressed_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"onButtonPressed");
	plg->onButtonReleased = (onButtonReleased_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"onButtonReleased");
	plg->onDongleConnected = (onDongleConnected_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"onDongleConnected");
	plg->onDongleDisconnected = (onDongleDisconnected_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"onDongleDisconnected");
	plg->onChargerPlugged = (onChargerPlugged_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"onChargerPlugged");
	plg->onChargerUnPlugged = (onChargerUnPlugged_t)(uintptr_t)IMPORT_FUNC(DLLHANDLE,"onChargerUnPlugged");
	
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
void loadAllPlugin()
{
	DIR *dp;
	DIR *dp2;
	
	struct dirent *ep;
	struct dirent *ep2;
	
	FILE *fp;
	char *dir;
	
	char *file;
	
	
	plugins = (tuxplugins)malloc(sizeof(tuxplugins_t));
	
	plugins->count=0;
	plugins->error=0;
	
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
									#ifdef _WIN32
									file = (char *)malloc(sizeof(char *)*strlen(win32_file)+strlen(PLUGINS_DIRECTORY)+strlen(ep->d_name));
									sprintf(file,"%s%s/%s",PLUGINS_DIRECTORY,ep->d_name,win32_file);
									#else
									file = (char *)malloc(sizeof(char *)*strlen(linux_file)+strlen(PLUGINS_DIRECTORY)+strlen(ep->d_name));
									sprintf(file,"%s%s/%s",PLUGINS_DIRECTORY,ep->d_name,linux_file);
									#endif
									
									if(file_exists(file))
									{
										plugins->plugins = (Plugin *)realloc(plugins->plugins, sizeof(Plugin_t)*plugins->count+1);
										plugins->plugins[plugins->count] = loadPlugin(file);
										plugins->plugins[plugins->count]->name = plugin_name;
										plugins->plugins[plugins->count]->author = plugin_author;
										plugins->plugins[plugins->count]->version = plugin_version;
										plugins->plugins[plugins->count]->setIsServerStarted(isServerStarted);
										plugins->plugins[plugins->count]->setTux_Open(Tux_Open);
										plugins->plugins[plugins->count]->setTux_Close(Tux_Close);
										plugins->plugins[plugins->count]->setTux_OpenClose(Tux_OpenClose);
										plugins->plugins[plugins->count]->setTux_Leds_OnOff(Tux_Leds_OnOff);
										plugins->plugins[plugins->count]->setTux_Leds_Blink(Tux_Leds_Blink);
										plugins->plugins[plugins->count]->setTux_Leds_Pulse(Tux_Leds_Pulse);
										plugins->plugins[plugins->count]->setTux_Micro(Tux_Micro);
										plugins->plugins[plugins->count]->setTux_Audio(Tux_Audio);
										plugins->plugins[plugins->count]->setTux_Flippers(Tux_Flippers);
										plugins->plugins[plugins->count]->setTux_Rotate(Tux_Rotate);
										plugins->plugins[plugins->count]->setTux_Flash(Tux_Flash);
										plugins->plugins[plugins->count]->setTux_Sleep(Tux_Sleep);
										plugins->plugins[plugins->count]->setTux_Wakeup(Tux_Wakeup);
										plugins->plugins[plugins->count]->setTux_Off(Tux_Off);
										plugins->plugins[plugins->count]->setTux_Reset(Tux_Reset);
										plugins->plugins[plugins->count]->setTux_TTS(Tux_TTS);
										plugins->plugins[plugins->count]->setTux_State(pTux_State);
										plugins->plugins[plugins->count]->setCallback(PluginsCallback);
										
										if(plugins->plugins[plugins->count]->Initialize != NULL)
											plugins->plugins[plugins->count]->Initialize();
										else
											TuxLogger_Error("Plugin \"%s\" have not Initialize() method !!",plugins->plugins[plugins->count]->name);
									
										plugins->count++;
									}
									else
									{
										plugins->error++;
										TuxLogger_Error("Unable to load plugin \"%s\"",plugin_name);
									}
								
									free(plugin_name);
									free(plugin_author);
									free(plugin_version);
									
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

}


