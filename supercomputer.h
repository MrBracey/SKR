DWORD WINAPI SuperComputer(LPVOID lpParameter);

extern char gFILE_VOCABOLARIO[32];
extern struct saccoSTR sacco[];
extern struct saccoSTR Info_Lettera[26+1];
extern struct tesseraSTR tessera[2][8];
extern struct casaSTR casa[15][15];
extern struct lemmaSTR lemma[NUM_LEMMI];// per il controllo e assegnazione punti
extern struct playerSTR iplayer[2];
extern unsigned short psacco;//punta alla prossima lettera nel sacco;
extern struct lemmaSTR zona_appoggio[LZA];
extern int	flag_mostra_idee;
extern int flag_check_validita;
extern int flag_mostra_tessere;
extern BYTE Global_Demox;
extern BYTE			turn;// se gioca player 0 oppure 1
extern BYTE			totalturn;//turno totale
extern BYTE			player;
extern BYTE			gselection;
extern BYTE			value[15][15];
extern int gMaxPuntiHelp;
extern HINSTANCE		ghInst;
extern HWND			ghWndToolbarDlg;
extern HWND			ghwndMain;
extern int iBASEX,iBASEY,iDIMBOARD,iDIMTESSERA,iXTESSERA,iYTESSERA;//cefalu
extern int iXMAN1,iXMAC1,iYPUNTO,iDIMXCIFRA,iDIMYCIFRA,iDISTACCO,iXMAS1,iYSUNTO;//cefalu
extern int iINTV,iLIMX,iLIMY,iMAG1,iMAG2;//cefalu
extern char parola_originale[];
extern float rapportoy,rapportox;
extern int flag_passo_cpu;
extern int flag_passo_human;
extern BYTE		gFaseHelp;//VENEZIA2
extern int	sflag_mostra_tessere;//santiago cambia
extern int	sflag_mostra_idee;//santiago cambia
extern BYTE flag_prima_tessera;
extern BYTE salva_flag_1t;
extern BYTE salva_flag_77;
extern char szMsg[4092];
extern int Machine_Thinking; //okinawa
extern HANDLE hThreadSC;
							 /*
	DICHIARAZIONI
	*/

void Logga(char* msg);
