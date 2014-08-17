
#ifndef __TUXPLUGIN_H__
#define __TUXPLUGIN_H__

#include <stdio.h>
#include <stdbool.h>
#include <libxml/xmlreader.h>

//----------------------
//Structure d'un plugin:
//----------------------
typedef void (*Initialize_t)(void);
typedef void (*processesData_t)(char *cmd, char **data); //fonction du plugin
typedef void (*callback_t)(void *data);
typedef char *(*setCallback_t)(callback_t funct);
typedef void (*onButtonPressed_t)(char *button);
typedef void (*onButtonReleased_t)(char *button);
typedef void (*onDongleConnected_t)(void);
typedef void (*onDongleDisconnected_t)(void);
typedef void (*onChargerPlugged_t)(void);
typedef void (*onChargerUnPlugged_t)(void);

typedef struct
{
	char *name;
	char *author;
	char *version;
	
	Initialize_t Initialize;
	setCallback_t setCallback;		//définission du callback
	processesData_t processesData;	//fonction de traitément des données
	onButtonPressed_t onButtonPressed;
	onButtonReleased_t onButtonReleased;
	onDongleConnected_t onDongleConnected;
	onDongleDisconnected_t onDongleDisconnected;
	onChargerPlugged_t onChargerPlugged;
	onChargerUnPlugged_t onChargerUnPlugged;
	
} Plugin_t;
typedef Plugin_t *Plugin;
//--------------------------


typedef struct
{
	Plugin plugins[100];
	int count;
	
} tuxplugins_t;
typedef tuxplugins_t *tuxplugins;

void loadAllPlugin(void);
void PluginsCallback(void *data);
char *getExtension(char *file);
Plugin loadPlugin(char *file);
bool TuxPluin_ParseXMLFile(const char *xmlfile); 
void TuxPluin_processNode(xmlTextReaderPtr reader); 

#endif

