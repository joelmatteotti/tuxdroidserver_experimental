#include <stdio.h>
#include "plugin.h"

LIBEXPORT void setCallback(callback_t funct)
{
	callback_funct = funct;
}

LIBEXPORT char *getName()
{
	return "Plugin Test";
}      

LIBEXPORT char *getAuthor()
{
	return "Joel Matteotti";
}

LIBEXPORT char *getVersion()
{
	return "1.0.0";
}

/* Fonction appeller au chargement du plugin (c'est l'equivalent du main() pour le plugin) */
LIBEXPORT void Initialize(void)
{
	//A ce stade le server n'est pas lancé il faut donc éviter d'envoyer des messages !!
	printf("Plugin de test prêt !\n");
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
	//
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

LIBEXPORT void processesData(char *cmd, void *data)
{
	//
}


