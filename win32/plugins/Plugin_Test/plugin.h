/* =============== GPL HEADER =====================
 * plugin.h is part of TuxDroidServer's Plugin API
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


#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#ifdef _WIN32
	#include <windows.h>
	#define LIBEXPORT    __declspec(dllexport)
#else
	#define LIBEXPORT    __attribute__ ((visibility ("default")))
#endif

extern void onButtonPressed(char *button);
extern void onButtonReleased(char *button);
extern void onDongleConnected(void);
extern void onDongleDisconnected(void);
extern void onChargerPlugged(void);
extern void onChargerUnPlugged(void);

typedef void(*callback_t)(void *data);
static callback_t callback_funct;
extern void Initialize(void);
extern void setCallback(callback_t funct);

typedef int (*isServerStarted_t)(void);
static isServerStarted_t isServerStarted;
extern void setIsServerStarted(isServerStarted_t funct);

typedef void (*Tux_Open_t)(char *motor);
static Tux_Open_t Tux_Open;
extern void setTux_Open(Tux_Open_t funct);

typedef void (*Tux_Close_t)(char *motor);
static Tux_Close_t Tux_Close;
extern void setTux_Close(Tux_Close_t funct);

typedef void (*Tux_OpenClose_t)(char *motor, int count);
static Tux_OpenClose_t Tux_OpenClose;
extern void setTuxOpenClose(Tux_OpenClose_t funct);

typedef void (*Tux_Leds_OnOff_t)(char *led, char *action);
static Tux_Leds_OnOff_t Tux_Leds_OnOff;
extern void setTux_Leds_OnOff(Tux_Leds_OnOff_t funct);

typedef void (*Tux_Leds_Blink_t)(char *led, char *count, char *delay);
static Tux_Leds_Blink_t Tux_Leds_Blink;
extern void setTux_Leds_Blink(Tux_Leds_Blink_t funct);

typedef void (*Tux_Leds_Pulse_t)(char *led, char *min_intensity, char *max_intensity, char *count, char *period, char *effect, char *speed, char *step);
static Tux_Leds_Pulse_t Tux_Leds_Pulse;
extern void setTux_Leds_Pulse(Tux_Leds_Pulse_t funct);

typedef void (*Tux_Micro_t)(char *action, char *file);
static Tux_Micro_t Tux_Micro;
extern void setTux_Micro(Tux_Micro_t funct);

typedef void (*Tux_Flippers_t)(char *action,char *count);
static Tux_Flippers_t Tux_Flippers;
extern void setTux_Flippers(Tux_Flippers_t funct);

typedef void (*Tux_Rotate_t)(char *action, char *count);
static Tux_Rotate_t Tux_Rotate;
extern void setTux_Rotate(Tux_Rotate_t funct);

typedef void (*Tux_Flash_t)(char *sound, char *amplitude);
static Tux_Flash_t Tux_Flash;
extern void setTux_Flash(Tux_Flash_t funct);

typedef void (*Tux_Audio_t)(char *action, char *rawcmd);
static Tux_Audio_t Tux_Audio;
extern void setTux_Audio(Tux_Audio_t funct);

typedef void (*Tux_Sleep_t)(void);
static Tux_Sleep_t Tux_Sleep;
extern void setTux_Sleep(Tux_Sleep_t funct);

typedef void (*Tux_Wakeup_t)(void);
static Tux_Wakeup_t Tux_Wakeup;
extern void setTux_Wakeup(Tux_Wakeup_t funct);

typedef void (*Tux_Off_t)(char *motor);
static Tux_Off_t Tux_Off;
extern void setTux_Off(Tux_Off_t funct);

typedef void (*Tux_Reset_t)(void);
static Tux_Reset_t Tux_Reset;
extern void setTux_Reset(Tux_Reset_t funct);

typedef void(*Tux_TTS_t)(char **argv,int argc);
static Tux_TTS_t Tux_TTS;
extern void setTux_TTS(Tux_TTS_t funct);

typedef char *(*Tux_State_t)(char *sw_id);
static Tux_State_t Tux_State;
extern void setTux_State(Tux_State_t funct);

/* Fake Client structure */
typedef struct {} tux_client_t;
typedef tux_client_t *tux_client;

typedef void (*_SendMsgToAll_t)(char *msg, tux_client except_client);
static _SendMsgToAll_t _SendMsgToAll;
extern void setSendMsgToAll(_SendMsgToAll_t funct);

LIBEXPORT void setSendMsgToAll(_SendMsgToAll_t funct) { _SendMsgToAll = funct; }
LIBEXPORT void setIsServerStarted(isServerStarted_t funct) { isServerStarted = funct; }
LIBEXPORT void setTux_Open(Tux_Open_t funct) { Tux_Open = funct; }
LIBEXPORT void setTux_Close(Tux_Close_t funct) {Tux_Close = funct;}
LIBEXPORT void setTux_OpenClose(Tux_OpenClose_t funct){	Tux_OpenClose = funct;}
LIBEXPORT void setTux_Leds_OnOff(Tux_Leds_OnOff_t funct){Tux_Leds_OnOff = funct;}
LIBEXPORT void setTux_Leds_Blink(Tux_Leds_Blink_t funct){	Tux_Leds_Blink = funct;}
LIBEXPORT void setTux_Leds_Pulse(Tux_Leds_Pulse_t funct){	Tux_Leds_Pulse = funct;}
LIBEXPORT void setTux_Micro(Tux_Micro_t funct){	Tux_Micro = funct;}
LIBEXPORT void setTux_Flippers(Tux_Flippers_t funct){	Tux_Flippers = funct;}
LIBEXPORT void setTux_Rotate(Tux_Rotate_t funct){	Tux_Rotate = funct;}
LIBEXPORT void setTux_Flash(Tux_Flash_t funct){	Tux_Flash = funct;}
LIBEXPORT void setTux_Audio(Tux_Audio_t funct){	Tux_Audio = funct;}
LIBEXPORT void setTux_Sleep(Tux_Sleep_t funct){	Tux_Sleep = funct;}
LIBEXPORT void setTux_Wakeup(Tux_Wakeup_t funct){	Tux_Wakeup = funct;}
LIBEXPORT void setTux_Off(Tux_Off_t funct){	Tux_Off = funct;}
LIBEXPORT void setTux_Reset(Tux_Reset_t funct){	Tux_Reset = funct;}
LIBEXPORT void setTux_TTS(Tux_TTS_t funct){	Tux_TTS = funct;}
LIBEXPORT void setTux_State(Tux_State_t funct) { Tux_State = funct; }
LIBEXPORT void setCallback(callback_t funct){	callback_funct = funct;}
void SendMsgToAll(char *msg) { _SendMsgToAll(msg,NULL); }



#endif

