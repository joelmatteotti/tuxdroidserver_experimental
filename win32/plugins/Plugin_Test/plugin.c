#include <stdio.h>
#include "plugin.h"

LIBEXPORT void setCallback(callback_t funct)
{
	callback_funct = funct;
}

/* Fonction appeller au chargement du plugin (c'est l'equivalent du main() pour le plugin) */
LIBEXPORT void Initialize(void)
{
	//A ce stade le server n'est pas lanc� il faut donc �viter d'envoyer des messages !!
	printf("Plugin de test pr�t !\n");
}

LIBEXPORT void onButtonPressed(char *button)
{
	//
}

LIBEXPORT void onButtonReleased(char *button)
{
	//
}

LIBEXPORT void onDongleConnected(void)
{
	printf("le dongle a �t� connect�\n"); //exemple d'utilisation basique
}

LIBEXPORT void onDongleDisconnect(void)
{
	//
}

LIBEXPORT void onChargerPlugged(void)
{
	//
}

LIBEXPORT void onChargerUnPlugged(void)
{
	//
}

/* Fonction appell�e d�s qu'une commande est re�us par le server */
LIBEXPORT void processesData(char *cmd, char **data)
{
	printf("commande recu");
}


