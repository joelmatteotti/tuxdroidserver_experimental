
#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#ifdef _WIN32
	#include <windows.h>
	#define LIBEXPORT    __declspec(dllexport)
#else
	#define LIBEXPORT    __attribute__ ((visibility ("default")))
#endif

typedef void(*callback_t)(void *data);
static callback_t callback_funct;

extern void Initialize(void);
extern void setCallback(callback_t funct);
extern char *getName(void);
extern char *getAuthor(void);
extern char *getVersion(void);
extern void onButtonPressed(char *button);
extern void onButtonReleased(char *button);
extern void onDongleConnected(void);
extern void onDongleDisconnected(void);
extern void onChargerPlugged(void);
extern void onChargerUnPlugged(void);


typedef int (*isServerStarted_t)(void);
isServerStarted_t isServerStarted;

typedef void (*Tux_Open_t)(char *motor);
Tux_Open_t Tux_Open;

typedef void (*Tux_Close_t)(char *motor);
Tux_Close_t Tux_Close;

typedef void (*Tux_OpenClose_t)(char *motor, int count);
Tux_OpenClose_t Tux_OpenClose;

typedef void (*Tux_Leds_OnOff_t)(char *led, char *action);
Tux_Leds_OnOff_t Tux_Leds_OnOff;

typedef void (*Tux_Leds_Blink_t)(char *led, char *count, char *delay);
Tux_Leds_Blink_t Tux_Leds_Blink;

typedef void (*Tux_Leds_Pulse_t)(char *led, char *min_intensity, char *max_intensity, char *count, char *period, char *effect, char *speed, char *step);
Tux_Leds_Pulse_t Tux_Leds_Pulse;

typedef void (*Tux_Micro_t)(char *action, char *file);
Tux_Micro_t Tux_Micro;

typedef void (*Tux_Flippers_t)(char *action,char *count);
Tux_Flippers_t Tux_Flippers;

typedef void (*Tux_Rotate_t)(char *action, char *count);
Tux_Rotate_t Tux_Rotate;

typedef void (*Tux_Flash_t)(char *sound, char *amplitude);
Tux_Flash_t Tux_Flash;

typedef void (*Tux_Audio_t)(char *action, char *rawcmd);
Tux_Audio_t Tux_Audio;

typedef void (*Tux_Sleep_t)(void);
Tux_Sleep_t Tux_Sleep;

typedef void (*Tux_Wakeup_t)(void);
Tux_Wakeup_t Tux_Wakeup;

typedef void (*Tux_Off_t)(char *motor);
Tux_Off_t Tux_Off;

typedef void (*Tux_Reset_t)(void);
Tux_Reset_t Tux_Reset;

typedef void (*Tux_TTS_t)(char **argv, int argc);
Tux_TTS_t Tux_TTS;


/* Client structure */
typedef struct
{
	int id;
	char *username;  /* user name */
	char *uKey;  /* user key */
	char *pID;  /* client application's ID */

	#ifdef _WIN32
	SOCKET sock;
	#else
	int sock;
	#endif
} tux_client_t;
typedef tux_client_t *tux_client;

typedef void (*SendMsgToAll_t)(char *msg, tux_client except_client);
SendMsgToAll_t SendMsgToAll;



#endif

