#include <stdio.h>
#include "plugin.h"
#include "../../../include/TuxStrings.h"

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

