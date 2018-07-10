#include "scarabeo.h"


struct saccoSTR sacco[NUM_TESSERE+1];//2013 aggiunge safety
struct tesseraSTR tessera[2][8];
struct casaSTR casa[15][15];
struct lemmaSTR lemma[NUM_LEMMI];// per il controllo e assegnazione punti
struct playerSTR iplayer[2];
struct lemmaSTR zona_appoggio[LZA];

char gFILE_VOCABOLARIO[MAX_PATH];
char gFILE_BILETT[32];//oslo
char szMsg[4092];
char parola_originale[36];
unsigned short psacco;//punta alla prossima lettera nel sacco;

BYTE			turn;// se gioca player 0 oppure 1
BYTE			totalturn;//turno totale
BYTE			player;
BYTE			gselection;
BYTE			gFaseHelp;
BYTE			Global_Demox;//HAMMERFEST
HDC				ghdc;
HANDLE			hDataHeap;
HINSTANCE		ghInst;
HWND			ghWndToolbarDlg;
HWND			ghwndMain;
HWND			gHwndMoDiz;//venezia
void *			hBaseHeap;
int	flag_mostra_tessere=FALSE;//santiago cambia
int	flag_mostra_idee=FALSE;//santiago cambia
//int Flag_edit_diz=TRUE;//FALSE;
int Flag_edit_in_corso=FALSE;
int	sflag_mostra_tessere=FALSE;//santiago cambia
int	sflag_mostra_idee=FALSE;//santiago cambia
int flag_passo_cpu=FALSE;
int flag_passo_human=FALSE;
int flag_dizionario;
int flag_check_validita;
int Flag_help_computer;
int flag_FAI_SILENZIO;
int gMaxPuntiHelp;//verona
int f_1st_help=FALSE;
int f_1st_refuse=FALSE;
float rapportox,rapportoy;
int maxlen;
//int gIndexBoard;
struct saccoSTR Info_Lettera[Q_LETTERE_ALFABETO_COMPLETE+Q_TIPI_JOLLY]; 
int scarselect;

BYTE value[15][15]={
5,1,1,2,1,1,1,5,1,1,1,2,1,1,5,
1,4,1,1,1,3,1,1,1,3,1,1,1,4,1,
1,1,4,1,1,1,2,1,2,1,1,1,4,1,1,
2,1,1,4,1,1,1,2,1,1,1,4,1,1,2,
1,1,1,1,4,1,1,1,1,1,4,1,1,1,1,
1,3,1,1,1,3,1,1,1,3,1,1,1,3,1,
1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,
5,1,1,2,1,1,1,4,1,1,1,2,1,1,5,//memphis raddoppia prima lettera
1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,
1,3,1,1,1,3,1,1,1,3,1,1,1,3,1,
1,1,1,1,4,1,1,1,1,1,4,1,1,1,1,
2,1,1,4,1,1,1,2,1,1,1,4,1,1,2,
1,1,4,1,1,1,2,1,2,1,1,1,4,1,1,
1,4,1,1,1,3,1,1,1,3,1,1,1,4,1,
5,1,1,2,1,1,1,5,1,1,1,2,1,1,5};
/*
1= valore semplice
2= x2 lettera
3= x3 lettera
4= x2 parola
5= x3 parola
*/
int 	timercount;
UINT_PTR	timer;
unsigned long crcTable[256];

BYTE flag_prima_tessera=TRUE;//kyoto poi va messa false: ma quando
BYTE salva_flag_1t;
BYTE salva_flag_77;
int punticalc;//falluja
//BYTE flag_abil_Grect;ankara
//RECT Grect;ankara


int iBASEX,iBASEY,iDIMBOARD,iDIMTESSERA,iXTESSERA,iYTESSERA;//cefalu
int iXMAN1,iXMAC1,iYPUNTO,iDIMXCIFRA,iDIMYCIFRA,iDISTACCO,iXMAS1,iYSUNTO;//cefalu
int iINTV,iLIMX,iLIMY,iMAG1,iMAG2;

int Machine_Thinking; //okinawa
HANDLE hThreadSC;
HCURSOR hCurs1;     // cursor handles 
char old_parola[80];//canicatti
char oldvalue=0;
int eliminate[6]={0,0,0,0,0,0};

HBRUSH hdialogbrush;//SFONDO DEL DIALOGO
BOOL flag_salvato=TRUE;
#ifndef TROMSOE
char MemoriaBiletterali[16000];
#endif
struct gperpend gperp;