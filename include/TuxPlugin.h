
//----------------------
//Structure d'un plugin:
//----------------------
typedef void (*Initialize_t)(void);
typedef void (*processesData_t)(char *cmd, void *data); //fonction du plugin
typedef char *(*getName_t)(void);
typedef char *(*getVersion_t)(void);
typedef char *(*getAuthor_t)(void);
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
	Initialize_t Initialize;
	getName_t getName;				//nom du plugin
	getAuthor_t getAuthor;			//nom de l'auteur
	getVersion_t getVersion;		//version du plugin
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

