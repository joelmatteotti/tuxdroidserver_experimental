#include <stdio.h>
#include "plugin.h"
#include "../../../include/TuxStrings.h"

/* Network part */
#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
	#ifndef _WS2TCPIP_H
	typedef size_t socklen_t;
	#endif
#else
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
typedef unsigned short u_short;
#endif
/* -- //network -- */


/* Fonction appellée lors de l'apuie sur un bouton */
/* button contient le nom du bouton pressé */
LIBEXPORT void onButtonPressed(char *button)
{
	//
}

/* Fonction appellée lors de la relache d'un bouton */
/* button contient le nom du bouton relaché */
LIBEXPORT void onButtonReleased(char *button)
{
	//
}

/* Fonction appellée lorsque le dongle est connecté */
LIBEXPORT void onDongleConnected(void)
{
	//
}

/* Fonction appellée lorsque le dongle est déconnecté */
LIBEXPORT void onDongleDisconnect(void)
{
	//
}

/* Fonction appellée lorsque le chargeur est branché */
LIBEXPORT void onChargerPlugged(void)
{
	//
}

/* Fonction appellée lorsqu'on débranche le chargeur */
LIBEXPORT void onChargerUnPlugged(void)
{
	//
}

/* Fonction appellée dès qu'un client est connecté ET identifié (via Tux_Key) à TuxDroidServer */
LIBEXPORT void addClient(tux_client client)
{
	//
}

/* Fonction appellée dès d'un client est déconnecté pour une raison ou une autre */
LIBEXPORT void delClient(tux_client client)
{
	//
}

/* Fonction appellée lorsqu'un client demande et obtiens la priorité */
LIBEXPORT void setPriority(tux_client client)
{
	//	
}

/* Fonction appellée lorsqu'un client relache la priorité */
LIBEXPORT void removePriority(tux_client client)
{
	//
}

/* Fonction appellée dès qu'une commande est reçus par le server */
LIBEXPORT void onCommand(char *cmd, char **parameters)
{
	if(!strcmp(strtolower(cmd),"tux_open"))
	{
		if(parameters != NULL)
		{
			if(parameters[0] != NULL)
			{
				
				char **phrases = (char **)malloc(sizeof(char *));
				phrases[0] = (char *)malloc(sizeof(char)*28);
				sprintf(phrases[0],"\"Commande reçue je m'exécute\"");
				
				phrases[1] = (char *)malloc(sizeof(char)*6);
				sprintf(phrases[1],"mb-fr1");
				
				phrases[2] = (char *)malloc(sizeof(char)*2);
				sprintf(phrases[2],"50");
				
				phrases[3] = (char *)malloc(sizeof(char)*3);
				sprintf(phrases[3],"115");
				
				phrases[4] = (char *)malloc(sizeof(char)*1);
				sprintf(phrases[4],"1");
				
				phrases[5] = (char *)malloc(sizeof(char)*1);
				sprintf(phrases[5],"0");
				
				Tux_TTS(phrases,6);
				
			
				//Autre exemple de commande:
				Tux_Flippers("Up",NULL);
			}
		}
	}
}

/* Fonction appeller au chargement du plugin (c'est l'equivalent du main() pour le plugin) */
LIBEXPORT void Initialize(void)
{
	//A ce stade le server n'est pas lancé il faut donc éviter d'envoyer des messages !!
	printf("Plugin de test prêt !\n");
}

