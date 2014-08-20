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


/* Fonction appell�e lors de l'apuie sur un bouton */
/* button contient le nom du bouton press� */
LIBEXPORT void onButtonPressed(char *button)
{
	//
}

/* Fonction appell�e lors de la relache d'un bouton */
/* button contient le nom du bouton relach� */
LIBEXPORT void onButtonReleased(char *button)
{
	//
}

/* Fonction appell�e lorsque le dongle est connect� */
LIBEXPORT void onDongleConnected(void)
{
	//
}

/* Fonction appell�e lorsque le dongle est d�connect� */
LIBEXPORT void onDongleDisconnect(void)
{
	//
}

/* Fonction appell�e lorsque le chargeur est branch� */
LIBEXPORT void onChargerPlugged(void)
{
	//
}

/* Fonction appell�e lorsqu'on d�branche le chargeur */
LIBEXPORT void onChargerUnPlugged(void)
{
	//
}

/* Fonction appell�e d�s qu'un client est connect� ET identifi� (via Tux_Key) � TuxDroidServer */
LIBEXPORT void addClient(tux_client client)
{
	//
}

/* Fonction appell�e d�s d'un client est d�connect� pour une raison ou une autre */
LIBEXPORT void delClient(tux_client client)
{
	//
}

/* Fonction appell�e lorsqu'un client demande et obtiens la priorit� */
LIBEXPORT void setPriority(tux_client client)
{
	//	
}

/* Fonction appell�e lorsqu'un client relache la priorit� */
LIBEXPORT void removePriority(tux_client client)
{
	//
}

/* Fonction appell�e d�s qu'une commande est re�us par le server */
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
				sprintf(phrases[0],"\"Commande re�ue je m'ex�cute\"");
				
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
	//A ce stade le server n'est pas lanc� il faut donc �viter d'envoyer des messages !!
	printf("Plugin de test pr�t !\n");
}

