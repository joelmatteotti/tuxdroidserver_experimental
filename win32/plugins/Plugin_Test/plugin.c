#include <stdio.h>
#include "plugin.h"

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

/* Fonction appellée dès qu'une commande est reçus par le server */
LIBEXPORT void processesData(char *cmd, char **data)
{
	printf("cmd => %s\n",cmd);
	
	if(!strcmp(cmd,"tux_open"))
	{
		printf("open mouth");
		if(data != NULL)
		{
			if(data[0] != NULL)
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

			}
			else
				printf("data[0] est null");
		}
		else
			printf("data est null");
	}
}

/* Fonction appeller au chargement du plugin (c'est l'equivalent du main() pour le plugin) */
LIBEXPORT void Initialize(void)
{
//	importFunctions(); //à ne pas oublier :)
	
	//A ce stade le server n'est pas lancé il faut donc éviter d'envoyer des messages !!
	printf("Plugin de test prêt !\n");
}

