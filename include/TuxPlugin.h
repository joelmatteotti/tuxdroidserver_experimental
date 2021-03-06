/* =============== GPL HEADER =====================
 * TuxPlugin.h is part of TuxDroidServer
 * Copyleft (C) 2014 - Joel Matteotti <joel _DOT_ matteotti _AT_ free _DOT_ fr>
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

#ifndef __TUXPLUGIN_H__
#define __TUXPLUGIN_H__

#include <stdio.h>
#include <stdbool.h>
#include <libxml/xmlreader.h>
#include <TuxTypes.h>

//----------------------
//Structure d'un plugin:
//----------------------
typedef void (*Initialize_t)(void);
typedef void (*onCommand_t)(char *cmd, char **data); //fonction du plugin
typedef void (*callback_t)(void *data);
typedef char *(*setCallback_t)(callback_t funct);

typedef void (*Tux_TTS_t)(char **argv, int argc);
typedef void (*setTux_TTS_t)(Tux_TTS_t);

typedef int (*isServerStarted_t)(void);
typedef void (*setIsServerStarted_t)(isServerStarted_t);

typedef void (*Tux_Open_t)(char *motor);
typedef void (*setTux_Open_t)(Tux_Open_t);

typedef void (*Tux_Close_t)(char *motor);
typedef void (*setTux_Close_t)(Tux_Close_t);

typedef void (*Tux_OpenClose_t)(char *motor, int count);
typedef void (*setTux_OpenClose_t)(Tux_OpenClose_t);

typedef void (*Tux_Leds_OnOff_t)(char *led, char *action);
typedef void (*setTux_Leds_OnOff_t)(Tux_Leds_OnOff_t);

typedef void (*Tux_Leds_Blink_t)(char *led, char *count, char *delay);
typedef void (*setTux_Leds_Blink_t)(Tux_Leds_Blink_t);

typedef void (*Tux_Leds_Pulse_t)(char *led, char *min_intensity, char *max_intensity, char *count, char *period, char *effect, char *speed, char *step);
typedef void (*setTux_Leds_Pulse_t)(Tux_Leds_Pulse_t);

typedef void (*Tux_Micro_t)(char *action, char *file);
typedef void (*setTux_Micro_t)(Tux_Micro_t);

typedef void (*Tux_Flippers_t)(char *action,char *count);
typedef void (*setTux_Flippers_t)(Tux_Flippers_t);

typedef void (*Tux_Rotate_t)(char *action, char *count);
typedef void (*setTux_Rotate_t)(Tux_Rotate_t);

typedef void (*Tux_Flash_t)(char *sound, char *amplitude);
typedef void (*setTux_Flash_t)(Tux_Flash_t);

typedef void (*Tux_Audio_t)(char *action, char *rawcmd);
typedef void (*setTux_Audio_t)(Tux_Audio_t);

typedef void (*Tux_Sleep_t)(void);
typedef void (*setTux_Sleep_t)(Tux_Sleep_t);

typedef void (*Tux_Wakeup_t)(void);
typedef void (*setTux_Wakeup_t)(Tux_Wakeup_t);

typedef void (*Tux_Off_t)(char *motor);
typedef void (*setTux_Off_t)(Tux_Off_t);

typedef void (*Tux_Reset_t)(void);
typedef void (*setTux_Reset_t)(Tux_Reset_t);

typedef char *(*Tux_State_t)(char *sw_id);
typedef void (*setTux_State_t)(Tux_State_t);


typedef void (*onButtonPressed_t)(char *button);
typedef void (*onButtonReleased_t)(char *button);
typedef void (*onDongleConnected_t)(void);
typedef void (*onDongleDisconnected_t)(void);
typedef void (*onChargerPlugged_t)(void);
typedef void (*onChargerUnPlugged_t)(void);

typedef void (*addClient_t)(tux_client client);
typedef void (*delClient_t)(tux_client client);

typedef void (*setPriority_t)(tux_client client);
typedef void (*removePriority_t)(tux_client client);

typedef struct
{
	int loaded; //load state
	
	char *name;
	char *author;
	char *version;
	
	Initialize_t Initialize;
	setCallback_t setCallback;		//définission du callback
	
	
	setIsServerStarted_t setIsServerStarted;
	setTux_Open_t setTux_Open;
	setTux_Close_t setTux_Close;
	setTux_OpenClose_t setTux_OpenClose;
	setTux_Leds_OnOff_t setTux_Leds_OnOff;
	setTux_Leds_Blink_t setTux_Leds_Blink;
	setTux_Leds_Pulse_t setTux_Leds_Pulse;
	setTux_Micro_t setTux_Micro;
	setTux_Flippers_t setTux_Flippers;
	setTux_Rotate_t setTux_Rotate;
	setTux_Flash_t setTux_Flash;
	setTux_Audio_t setTux_Audio;
	setTux_Sleep_t setTux_Sleep;
	setTux_Wakeup_t setTux_Wakeup;
	setTux_Off_t setTux_Off;
	setTux_Reset_t setTux_Reset;
	setTux_TTS_t setTux_TTS;
	setTux_State_t setTux_State;
	
	addClient_t addClient;
	delClient_t delClient;
	
	setPriority_t setPriority;
	removePriority_t removePriority;
	
	onCommand_t onCommand;
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
	Plugin *plugins;
	int count;
	int error;
	
} tuxplugins_t;
typedef tuxplugins_t *tuxplugins;

void loadAllPlugin(void);
void PluginsCallback(void *data);
char *getExtension(char *file);
Plugin loadPlugin(char *file);
bool TuxPluin_ParseXMLFile(const char *xmlfile); 
void TuxPluin_processNode(xmlTextReaderPtr reader); 

#endif

