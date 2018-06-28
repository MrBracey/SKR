//supercomputer.cpp created by okinawa

#include "windows.h"
#include "resource.h"
#include "scarabeo.h"
#include <stdio.h>

#include "supercomputer.h"

extern char old_parola[];//canicatti
DWORD WINAPI SuperComputer(LPVOID lpParameter)
{
		 int n;
//	 int lengz;

int parole_trovate;
HWND hdlg=(HWND)&lpParameter;


Machine_Thinking=TRUE; //okinawa

				flag_passo_cpu=FALSE;
				player=PLAYER2;
			//	n=0;
			//	lengz=1;
				SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_RESETCONTENT,0,0);
//				SetDlgItemText(ghWndToolbarDlg,IDC_EDIT2,"");
				
				

				OutputDebugString("NO OKINAWA/n");
				//AggiornaFinestra();//okinawa
				
				
//Sleep(1000);//2012 risolve baco che non mostra la tabella? no

				CPUchkScarab();

//label_test_ciclo_ripetuto:;
				

				while(!(n=SuperEngine(0)))
				{
					AggiornaFinestra();//okinawa

					n=MettiUnaLetteraACaso();
					if(!n)
					{
						AggiornaFinestra();//lettere temporanee
						SetWindowText(ghWndToolbarDlg,"La macchina passa la mano");
						flag_passo_cpu=TRUE;
						break;
					}
					if(gFaseHelp==HELP_IS_ON)
					{
						flag_mostra_idee=sflag_mostra_idee;
						flag_mostra_tessere=sflag_mostra_tessere;
						ScambiaTessere();
						//zara mi dice qual'è l'indice tessera
						//per la quale l'attributo da assente deve tornare
						//presente
						if(flag_prima_tessera)
						{
							tessera[PLAYER2][flag_prima_tessera-1].flag=salva_flag_1t;
							casa[7][7].flag=salva_flag_77;
							gFaseHelp=HELP_IS_OFF;
							flag_prima_tessera=0;
						}
					}
					goto alhoa;
				
				}
				
				if(gFaseHelp==HELP_IS_ON)
				{
					flag_mostra_idee=sflag_mostra_idee;
					flag_mostra_tessere=sflag_mostra_tessere;
					if(flag_prima_tessera)//zara
					{
						tessera[PLAYER2][flag_prima_tessera-1].flag=salva_flag_1t;
						casa[7][7].flag=salva_flag_77;
						gFaseHelp=HELP_IS_OFF;
						flag_prima_tessera=0;
					}

					ScambiaTessere();
					gFaseHelp=HELP_IS_OFF;
					goto alhoa;
				}
				
				parole_trovate=n;
				
				if(parole_trovate)
				{
				OutputDebugString("MOSTRA_LEMMI iniZIO /n");
					n=Mostra_Lemmi(n,ghWndToolbarDlg);
					OutputDebugString("MOSTRA_LEMMI FINE /n");

				
					
					
					if(n>=0)
					{
						Assegna_punti(player,zona_appoggio[n].value);//efeso
					}
					else{
						n=MettiUnaLetteraACaso();
						if(!n)
						{
							AggiornaFinestra();//lettere temporanee
							SetWindowText(ghWndToolbarDlg,"Passo la mano");
							flag_passo_cpu=TRUE;
						}
					}
alhoa:;									
					old_parola[0]=0;// antibaco 2012	
					Annulla_flag_temporanei(PERMANENTE);					
					OutputDebugString("NO REVERSE ATTIVATO/n");
					AggiornaFinestra();//toglie il reverse bergamo
					
					if(zona_appoggio[n].parola[0])
					{
						char ch[32];
						strcpy(ch,zona_appoggio[n].parola);
						ch[strlen(ch)-1]=0;
						strcat(ch,"*");
						SetDlgItemText(ghWndToolbarDlg,IDC_COMBO_SEARCH,ch);//nervi
					}

				}
				
					char msg[80];
					sprintf(msg,SEPARATURNI);//_U
					AggiungiMessaggio(ghWndToolbarDlg,msg);

				
				Machine_Thinking=FALSE; //okinawa
					player=player==PLAYER1?PLAYER2:PLAYER1;

					
					if(Global_Demox==1)
					{

						if(parole_trovate)
						{
								BOOL b=PlaySound(
							  "btnup.wav",  
							  NULL,     
							 SND_FILENAME|SND_NODEFAULT    
							);
							ShowWindow(GetDlgItem(ghWndToolbarDlg,IDC_DEMOX),SW_SHOW);
							SetWindowText(ghWndToolbarDlg,"Accetto comando");//okinawa
							Sleep(3000);//da  tempo di leggere eventuali tasti..//okinawa
							if(Global_Demox==1)//verifica ancora..
								{
								player=PLAYER2;
								BOOL b=PlaySound(
							  "btnup.wav",  
							  NULL,     
							 SND_FILENAME|SND_NODEFAULT    
							);
ShowWindow(GetDlgItem(ghWndToolbarDlg,IDC_DEMOX),SW_HIDE);
														
							}
							else
							{
								SetWindowText(ghWndToolbarDlg,"Demo - pausa");//okinawa
								while(!Global_Demox) Sleep(500);
								player=PLAYER2;
							}
							//	player=PLAYER1;
						}
						else //fine
							goto hammerfest;
					}

					

					if(Assegna_tessere(player)==-1)
					{
					/*	
						AssegnaiPuntiDellAltro();//tunisi
						{
								
						da fare
						}
						*/
hammerfest:;

						AggiornaFinestra();//LUCCA SCOMM
						
						if(iplayer[PLAYER1].punti){
						sprintf(zona_appoggio[0].parola,"Giocatore 1: punti");
						zona_appoggio[0].value=iplayer[PLAYER1].punti;
						Parla(&zona_appoggio[0]);						
						}
					//	Sleep(4000);
						if(iplayer[PLAYER2].punti){
						sprintf(zona_appoggio[0].parola,"Giocatore 2: punti");
						zona_appoggio[0].value=iplayer[PLAYER2].punti;
						Parla(&zona_appoggio[0]);						
						}
						MessaggioFinale();
						//PlaySound("space alarm.wav",NULL,NULL);
//						n=MessageBox(ghWndToolbarDlg,"Salvare?","ScarabIT 2002",MB_YESNO|MB_ICONINFORMATION);//ENNA 2CHK
//						if(n==IDYES)
						//salva();
					SendMessage(ghwndMain,WM_CLOSE,NULL,NULL);// BAHIA COMM//LAPAZ tunisi
					EndDialog(hdlg, 0);//LOWORD(wParam));// BAHIA COMM//LAPAZ tunisi
					return TRUE;
					}
					
					OutputDebugString("LUCCA DISATTIVATO.. /n");
					//AggiornaFinestra();//LUCCA SCOMM
		
			if (
				hThreadSC != NULL
				&&
				hThreadSC !=INVALID_HANDLE_VALUE
				) 
					CloseHandle(hThreadSC);				//VIAREGGIO
				
				hThreadSC=INVALID_HANDLE_VALUE;
				
				if(Global_Demox==1)
				{
					salva(1);
					SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,777L);
				}
				else
				{
OutputDebugString("CORINTO /n");
					AggiornaFinestra();// corinto
					SetWindowText(ghWndToolbarDlg,"Prego, è il suo turno");

				}
				

				return 0;
}
