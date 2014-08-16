
//----------------------
//Structure d'un plugin:
//----------------------
typedef void (*Initialize_t)(void);
typedef void (*processesData_t)(char *cmd, void *data); //fonction du plugin
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



//------------
//déclaration du tableau de plugins
extern Plugin plg[100]; /* maximum de 100 plugin pour le moment (par la suite il faudra faire une allocation automatique) */
extern int plg_count;
//--------

