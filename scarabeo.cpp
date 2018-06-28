#include "windows.h"
#include "Windowsx.h"
#include "resource.h"
#include "scarabeo.h"
#include "global.h"
#include "supercomputer.h"
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)



{

	MSG msg;
   
   ghInst = hInstance;
    if (!InitializeApp(hInstance, nCmdShow)) {
        MessageBox(NULL, "Init applicazione fallita", NULL, MB_OK);
        return 0;
    }


	
	
	HMENU hmenu;
	hmenu=LoadMenu(ghInst,MAKEINTRESOURCE(IDR_MENU1));
	//		SetMenu(ghWndToolbarDlg,hmenu);
	//SetWindow

	HACCEL hcc;
	
	hcc=LoadAccelerators(ghInst,MAKEINTRESOURCE(IDR_ACCELERATOR1));
	//fine


	
 
// Create a standard hourglass cursor. 
 
	hCurs1 = LoadCursor(NULL, IDC_CROSS);
	
	
	// Get and dispatch messages until a WM_QUIT message is 
    // received. 
#ifdef PERF_TEST
//	maincrypt(DEKRYPT);    
LARGE_INTEGER liPc,liFq,liPc2;
unsigned long ulDelta;
	char deb[128];
double dbl;

	

	QueryPerformanceFrequency ( &liFq);
	unsigned long ulf=(unsigned long)liFq.QuadPart;
	
	for(int g=0;g<10;g++)
	{
	QueryPerformanceCounter(&liPc);
	//fai qualcosa di sinistra..:!
	
	//int t1=GetTickCount();
	//if((g%2))
		//int t2=GetTickCount();
		//OutputDebugString("sono nel tempo!\n");


	//ecco il tempo
	QueryPerformanceCounter(&liPc2);
	ulDelta=(unsigned long)liPc2.QuadPart-(unsigned long)liPc.QuadPart;
	dbl=(double)ulDelta/(double)ulf;

	//sprintf(deb,"t1=%d t2=%d",t1,t2);
	//OutputDebugString(deb);

	
	sprintf(deb,"Il test è durato %f msec (%lu cicli)",dbl*1000,ulDelta);
	OutputDebugString(deb);
	OutputDebugString("\n");
	}
#endif 
hdialogbrush=CreateSolidBrush(RGB(235,235,235));//SFONDO DEL DIALOGO
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
        if (!TranslateAccelerator( ghwndMain, NULL, &msg )) 
		{
            TranslateMessage( &msg ) ;
            DispatchMessage( &msg ) ;
        }
    }

		  
		  

  DeleteObject(hdialogbrush);
   if(!HeapFree(hDataHeap,NULL,NULL))
		ErrorReporter("dealloc heap");

	return(0);
}
		




BOOL CALLBACK KeyProc(HWND hdlg, UINT uMessage, WPARAM wParam, LPARAM lparam)
{

	char Kbuffer[32];
	static char Kbuffer_o[32]="";
	static char buffer[DIM_BUFFER_RICERCA];
	static char mybuffer[DIM_BUFFER_RICERCA];
	char avviso[80];
	static int ckey=0;
	

//HMENU hmenu;
//SYSTEMTIME syt;
	//	RECT rect;
	POINT punto;
	POINT Cpoint;
	int selection;
//	 HDC hdc;
	 int n;
	 int riga;
char *pc;
int i;
			HWND hwEdit;
			POINT point;
			RECT rect;
			char bufedit[4096*2];//16384];
			//char lbuf[32];
			int erro;
int w,wcnt;
int z;
struct lemmaSTR lms;

    switch(uMessage)
    {
/*
	
		lascia 16 gdi allocati, anche senza chiamare nessuna
		di queste procedure, quindi e' il dialogo stesso che
		le lascia
	*/

	case WM_CTLCOLORDLG:          //  Set background color for dialog box and
		  case WM_CTLCOLORLISTBOX:     //  listbox to the current button face color
		  case WM_CTLCOLORSTATIC:              //  Don't forget the static control!
		  //hbrush=CreateSolidBrush(RGB(240,242,238));//SFONDO DEL DIALOGO

		  return (INT_PTR)hdialogbrush;

		 break;


	
	
	case WM_CLOSE:

			break;
	case WM_PAINT:
		MostraCase();
		Mostra_tessere_davvero();
		Mostra_punti(hdlg);
		Mostra_sacco();


		break;
	case WM_INITDIALOG:     // init controls
		gselection=NOT_SELECTED;
//		gIndexBoard=IDB_TG_PASSA;
		memset(buffer,0,sizeof(buffer));
		timercount=0;
		
		
		ParlaS(
			"#v0sasasasas"
		);

		
		if(
		!
		LeggiVocabolario()
		)
			exit(180564);
		
		
		break;
		case WM_RBUTTONDOWN:
			GetCursorPos(&punto);
			ScreenToClient(ghWndToolbarDlg, &punto); 

			selection=GetIndexCasa(punto,&Cpoint);//non torna coord ma indici
		if(selection>0)
		{
			if(casa[Cpoint.y][Cpoint.x].fsc &&casa[Cpoint.y][Cpoint.x].flag!=PERMANENTE)
			{
				//si battezza lo scarabeo
				BattezzaScarabeo(Cpoint.y,Cpoint.x);
			}
			else 
				LeggiParolaInFormazione(Cpoint);

		}

		break;

		case WM_MOUSEMOVE:
			if(gselection!=NOT_SELECTED)
			{
			SetCursor(hCurs1);
				//GetCursorPos(&punto);
			//ScreenToClient(ghWndToolbarDlg, &punto); 
			
			}
			break;

	case WM_LBUTTONUP://drag and drop
			GetCursorPos(&punto);
			ScreenToClient(ghWndToolbarDlg, &punto); 
			selection=GetIndexCasa(punto,&Cpoint);//non torna coord ma indici
			if
				(
					selection > 0
					&&
					punto.y < iYTESSERA
					&&
					(
						casa[Cpoint.y][Cpoint.x].flag == LIBERA
						||
						casa[Cpoint.y][Cpoint.x].fsc
						)

					) {
							if(gselection!= NOT_SELECTED)//28/6/18 corr.bug
							goto simuladown;//questo permette di trascinare 2013
					}
				
	break;//2013 con questo permette di alzare il mouse
	//#define BOMB

	case WM_LBUTTONDOWN:
		GetCursorPos(&punto);
		ScreenToClient(ghWndToolbarDlg, &punto);

simuladown:;
			if(!psacco)
				break;
			if(player==PLAYER2)
				break;
			
			if(punto.y>iYTESSERA)
			{
				selection=GetIndexTessera(player,turn,punto);
				if(selection>=0)
					SelezionaTessera(player,selection);
			}

			else if(gselection!=NOT_SELECTED)
			{
				//seleziona una casa e ci mette la lettera selezionata
				//poi cancella la tessera dal portatessere
				//se nella casa c'è già una tessera provvisoria invece
				//cancella la casa e rimette la tessera nel portatessere..
				selection=GetIndexCasa(punto,&Cpoint);//non torna coord ma indici
				if(selection>0)
				{
					//ora bisogna vedere se la casella è libera..
					switch (casa[Cpoint.y][Cpoint.x].flag)
					{
					case PERMANENTE://occupata stabile
						if(casa[Cpoint.y][Cpoint.x].fsc)
						{
							if(casa[Cpoint.y][Cpoint.x].s.lettera==tessera[player][gselection].s.lettera)
							{
								casa[Cpoint.y][Cpoint.x].fsc=0;
								memcpy(&tessera[player][gselection].s,&Info_Lettera[26],sizeof(struct saccoSTR));
								gselection=NOT_SELECTED;
								AggiornaFinestra();
							}
						}
						break;
					case LIBERA:
		
						DeponiLettera(player,Cpoint,gselection);
						CancellaTessera(player,gselection);
						if(flag_FAI_SILENZIO==BST_CHECKED)
							LeggiParolaInFormazione(Cpoint);
						tessera[player][gselection].flag=ASSENTE;
						gselection=NOT_SELECTED;

						break;
					case 1:
						if (player==PLAYER1)//è buona: sostituzione_automatica
							if(sostituzione_automatica(player,Cpoint,gselection))
								AggiornaFinestra();

					break;					
					case 2:
						if (player==PLAYER2)//è buona: sostituzione_automatica
							if(sostituzione_automatica(player,Cpoint,gselection))
								AggiornaFinestra();
					break;

					}
				}
			}
#ifndef BOMB
			else if(gselection==NOT_SELECTED && punto.y<iYTESSERA)
			{
				selection=GetIndexCasa(punto,&Cpoint);//non torna coord ma indici
				if(selection>0)
				{
					if(sostituzione_automatica(player,Cpoint,gselection))//VIENNA
						AggiornaFinestra();
				}
			}
#endif//BOMB


			break;

	


	case WM_COMMAND: 
	    switch(LOWORD(wParam))
	    {
		case IDM_ESCAPE:

			break;
		case IDCANCEL:
		case IDOK:
			if(psacco&&(!flag_salvato))
			{
				//int rsp=MessageBox(ghwndMain,"Abbandono partita. Salvare?","",MB_YESNOCANCEL);
				int rsp=IDYES;

				if(rsp==IDNO)
					SendMessage(ghwndMain,WM_CLOSE,NULL,NULL);else 
				
				
				if(rsp==IDYES)
				{
					salva(1);//SALVA IL TEMPORANEO
					SendMessage(ghwndMain,WM_CLOSE,NULL,NULL);;
				}
			}
			else
				SendMessage(ghwndMain,WM_CLOSE,NULL,NULL);
		    return TRUE;
		case IDC_DEMOX:
			if(Machine_Thinking) break;//okinawa
			Global_Demox=Global_Demox==TRUE?FALSE:TRUE;
			if(Global_Demox) 
			{
				ShowWindow(GetDlgItem(ghWndToolbarDlg,IDC_DEMOX),SW_HIDE);
				SetWindowText(ghWndToolbarDlg,"Demo in esecuzione");
				//MessageBox(ghwndMain,"Demo ON","",MB_ICONINFORMATION);
				//Beep(400,100);
				//flag_mostra_tessere =TRUE;
//				flag_mostra_idee =TRUE;
				if(hThreadSC==INVALID_HANDLE_VALUE)
					SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_START,0L);
			}
			else
				SetWindowText(ghWndToolbarDlg,"");
			//	MessageBox(ghwndMain,"Demo OFF","",MB_ICONINFORMATION);
		break;	
		case IDC_RUOTA:
			if(Machine_Thinking) break;//okinawa
			if(psacco)
				Ruota();
			break;
		case IDC_MESCOLA:
			if(Machine_Thinking) break;//okinawa
			if(psacco)
				Mescola_tessere();
			break;

		case IDC_SALVA:
			if(Machine_Thinking) break;//okinawa
			if(!psacco)
				break;
			salva();
			break;
		case IDC_RIPRISTINA:
			if(Machine_Thinking) break;//okinawa
			if(psacco)
			{
				int z=MessageBox(hdlg,"Abbandonare la partita?","",MB_YESNO);
				if(z==IDNO)
					break;
				
			}
			if(ripristina())
			{
				flag_prima_tessera=FALSE;
				AggiornaFinestra();
			}
			break;
		case IDC_CHECK_TESSERE:
			AggiornaFinestra();//LUCCA SCOMM
			if(IsDlgButtonChecked(hdlg,IDC_CHECK_TESSERE))
				flag_mostra_tessere =TRUE;
			else
				flag_mostra_tessere=FALSE;
			Mostra_tessere();

			break;
		case IDC_FAI_SILENZIO:// = PARLA!!
			/*
BST_CHECKED Button is checked. 
BST_INDETERMINATE Button is grayed, indicating an indeterminate state (applies only if the button has the BS_3STATE or BS_AUTO3STATE style). 
BST_UNCHECKED 
			*/
			flag_FAI_SILENZIO =IsDlgButtonChecked(hdlg,IDC_FAI_SILENZIO);
			
			break;

		case IDC_CHECK_IDEE:
			if(IsDlgButtonChecked(hdlg,IDC_CHECK_IDEE))
				flag_mostra_idee =TRUE;
			else
				flag_mostra_idee =FALSE;
				AggiornaFinestra();
			break;
		case IDC_CHECK_VAL:
			if(IsDlgButtonChecked(hdlg,IDC_CHECK_VAL))
				flag_check_validita =TRUE;
			else
				flag_check_validita =FALSE;
				AggiornaFinestra();//LUCCA SCOMM
			break;
		case IDC_LIST:
			{
				if(Machine_Thinking) break;//okinawa
				if (HIWORD(wParam)!=LBN_DBLCLK)
				break;
				if(gMaxPuntiHelp)
				{
					erro=SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_GETCURSEL,0,0);			
					SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_GETTEXT,(WPARAM)(erro),(LPARAM)bufedit);
					AttivaScrittura(bufedit);
				}
				break;
			if(Flag_edit_in_corso==TRUE)
				break;
			erro=SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_GETCURSEL,0,0);			
			SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_GETTEXT,(WPARAM)(erro),(LPARAM)bufedit);

				//glasgow: se la parola è "23 VELIERI [V28]" deve diventare "VELIERI"
				char *pc=bufedit;
				if(*pc<'A')
				{
					while(*pc<'A')
						pc++;
					strtok(pc," ");
					*(pc+strlen(pc)-1)='*';

					SetDlgItemText(hdlg, IDC_COMBO_SEARCH,pc);
					
					AggiornaFinestra();
					
					SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_BUTTON1,0L);
					break;
				}
			break;
			}
			
		case IDC_EDIT2:
#define RIGHE_NELLA_EDIT 8		

//			if(Flag_edit_diz==FALSE)
//				break;
			
			if(Machine_Thinking||Global_Demox)
				break;//2012
			if(Flag_edit_in_corso==TRUE)
				break;


			hwEdit=GetDlgItem(ghWndToolbarDlg,IDC_EDIT2);
			GetDlgItemText(ghWndToolbarDlg,IDC_EDIT2,bufedit,sizeof(bufedit)-1);
			GetCursorPos(&point);
			GetWindowRect(hwEdit,&rect);
			if(point.y>rect.bottom)
				break;
			if(point.x>rect.right-20)
				break;



			SCROLLINFO si;
			si.cbSize=sizeof(si); 
			si.fMask=SIF_ALL;     
			if(!GetScrollInfo(hwEdit,SB_VERT,&si))
				DWORD err=GetLastError();




			
//			sprintf(avviso,"BOX:T%d B%d L%d R%d PUNTO:x=%d,y=%d\n",rect.top,rect.bottom,rect.left,rect.right,point.x,point.y);
//			OutputDebugString(avviso);
			
			riga=(rect.bottom-rect.top)/RIGHE_NELLA_EDIT;//altezza di una riga di testo
			point.y-=rect.top;
			riga=point.y/riga;
			riga+=si.nPos;

//venezia verifica se ci sono abbastanza righe
			wcnt=0;
			n=strlen(bufedit);
			for(w=0;w<strlen(bufedit);w++)
			{
				if(bufedit[w]=='\r')
					wcnt++;
			}
//#pragma message ("<=")
			if(riga<wcnt)//venezia RIGHE_NELLA_EDIT)
			{
				strtok(bufedit,"\r\n");
				for(n=0;n<riga;n++)
				{
					char *ptr=strtok(NULL,"\r\n");
					if(ptr)
					strcpy(bufedit,ptr);
				}
			
				//glasgow: se la parola è "23 VELIERI [V28]" deve diventare "VELIERI"
				char *pc=bufedit;
				if(*pc<'A')
				{
					while(*pc<'A')
						pc++;
					strtok(pc," ");
					*(pc+strlen(pc)-1)='*';
					//SetDlgItemText(hdlg,IDC_EDIT1,pc);
					SetDlgItemText(hdlg, IDC_COMBO_SEARCH,pc);
					AggiornaFinestra();
					
					SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_BUTTON1,0L);
				//	flag_auto_edit=TRUE;
					SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_EDIT_DIZ,0L);

					break;
				}
				sprintf(avviso,"%s\n",pc);
				OutputDebugString(avviso);
				strcpy(parola_originale,pc);

				
				//SendMessage(gHwndMoDiz,WM_COMMAND,WM_USER+567,(LPARAM)parola_originale);//VENEZIA
				Flag_edit_in_corso=TRUE;
				
				//RICHIAMATA DA click su lista
				int k=DialogBoxParam(ghInst,MAKEINTRESOURCE(IDD_DIALOG5),ghWndToolbarDlg,(DLGPROC) MoDizProc,(LPARAM)parola_originale);	
				//SendMessage(gHwndMoDiz,WM_COMMAND,WM_USER+567,(LPARAM)parola_originale);//VENEZIA
				//CreateDialog(ghInst,MAKEINTRESOURCE(IDD_DIALOG5),ghWndToolbarDlg,(DLGPROC) MoDizProc);
				Flag_edit_in_corso=FALSE;
			}
			else
			{
				sprintf(avviso,"Nessuna o troppe parole in lista\n");
				OutputDebugString(avviso);
			}
			//SetDlgItemText(ghWndToolbarDlg,IDC_EDIT_DIZ,"Modifica dizionario");
			//Flag_edit_diz=FALSE;
			
//			SendDlgItemMessage(ghWndToolbarDlg,IDC_EDIT2,EM_SETREADONLY, TRUE,0);
			break;
//#endif
		case IDC_EDIT_DIZ:
///* glasgow scomm
				Flag_edit_in_corso=TRUE;
				//int k=DialogBox(ghInst,MAKEINTRESOURCE(IDD_DIALOG5),ghWndToolbarDlg,(DLGPROC) MoDizProc);	
				
				//RICHIAMATA DA MODIFICA DIZIONARIO.DEF NIENTE
				DialogBoxParam(ghInst,MAKEINTRESOURCE(IDD_DIALOG5),ghWndToolbarDlg,(DLGPROC) MoDizProc,(LPARAM)"");	
				Flag_edit_in_corso=FALSE;

			break;
/* corinto ripulitura
		case IDC_DEMO:
		//	flag_mostra_idee =flag_mostra_idee==1?0:1;
			if(IsDlgButtonChecked(hdlg,IDC_DEMO))
				Flag_help_computer=TRUE;
			else
				Flag_help_computer=FALSE;
				
			break;
*/
		case IDC_START:
	
			if(Machine_Thinking) break;//okinawa

			
			if(hThreadSC!=INVALID_HANDLE_VALUE){
				CloseHandle(hThreadSC);
				hThreadSC=INVALID_HANDLE_VALUE;
				Global_Demox=(FALSE);
		//		break;//OKINAWA
			}


			if(psacco)
			{
				
				int z;
				if(Global_Demox)
					z=IDNO;
				else
					z=MessageBox(hdlg,"Iniziare una nuova partita?","",MB_YESNO);
				if(z==IDNO)
				{
					if(Global_Demox)
					{
						Assegna_tessere(PLAYER2);
						AggiornaFinestra();

						SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,0L);
					}
					break;
				}
			}
			gMaxPuntiHelp=0;
			DeleteFile("scarabeo.tmp");//GIUSTO
			InitStructz();
			Mescola();
			if(!Global_Demox)
				Assegna_tessere(PLAYER1);
			Assegna_tessere(PLAYER2);
			AggiornaFinestra();
			salva(1);
			player=rand()%2;


reask:;	
			if(Global_Demox)
				player=PLAYER2;
//			flag_prima_tessera=TRUE; //kyoto
			if(player==PLAYER2)
			{

//santiago 
				if(!Global_Demox)//check_validita)
				{
					//char bugg[40];
					//sprintf(bugg,"#r%dHo il permesso di iniziare?",rate--);
					//ParlaS(bugg);
					//ParlaS("posso cominciare io?");
					int wen=MessageBox(ghWndToolbarDlg,"Ho il permesso di iniziare?","",MB_YESNO|MB_ICONINFORMATION);
					if(wen==IDNO) 
					{
						player=PLAYER1;
						goto reask;// :-) LOL
					}
				}
				//else 
				AggiornaFinestra();
				SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,0L);//hammerfest

				
				//else
//fine santiago
				//{
				//salva(1);
				//int z=MessageBox(hdlg,"Comincio IO","",MB_YESNO);
				//if(z==IDNO)
				//	break;
				//SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,0L);
				//}
			}
			else// if(!Global_Demox)
			{
				AggiornaFinestra();
				ParlaS("Prego, è il suo turno");
				SetWindowText(ghWndToolbarDlg,"Prego, è il suo turno");	

					char msg[80];
					sprintf(msg,SEPARATURNI);//_U);
					AggiungiMessaggio(ghWndToolbarDlg,msg);
			}
//bergamo
			break;
		case IDC_RIFIUTA:
			if(Machine_Thinking) break;//okinawa
			if(Global_Demox==1) break;
			if(!psacco)	break;
			if(f_1st_refuse==FALSE)//glasgow
			{
				f_1st_refuse=FALSE;//annulla glasgow
				z=MessageBox(hdlg,"Annullare l'ultima parola?","",MB_YESNO|MB_ICONQUESTION);
				if(z==IDNO)
					break;
			}
			if(ripristina(1))
			{
				AggiornaFinestra();
				SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,0L);
			}
			//else 
				//MessageBox(hdlg,"Niente da rifiutare","",MB_ICONINFORMATION);
			//	SetWindowText(ghWndToolbarDlg,"Niente da rifiutare");
		break;
		case IDC_ANNULLA:
			if(Machine_Thinking) break;//okinawa
			if(Global_Demox==1) break;
			if(!psacco)	break;
			Annulla_flag_temporanei(LIBERA);
			Annulla_flag_temporanei_T(ASSENTE,PRESENTE);//parigi: solo per player 1!!!!
			Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);
			AggiornaFinestra();
		break;
		case IDC_CALCOLA://parigi
			if(Machine_Thinking) break;//okinawa
			if(Global_Demox==1) break;
			if(!psacco)	break;
			//deve tornare i parametri per controll e cioè hv,y,x
				memset(&lms,0,sizeof(lms));
				n=Trovaparola(&lms);
				if(n==1||n==2)
				{
					if(n==1)
						MessageBox(ghWndToolbarDlg,
						//"La parola inserita deve essere\r\nin contatto con quelle già presenti.",
						"La disposizione delle lettere non sembra corretta, riprova!",
						NULL,
						MB_ICONSTOP
					);
					SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_ANNULLA,0L);
					break;
				}
				else if(n==3)//scarabeo
					lms.value=RITIRA_INSERIMENTO;
				else
					lms.value=ControLLN(&lms);
				if(lms.value==RITIRA_INSERIMENTO)
				{
					Annulla_flag_temporanei(ASSENTE);
					Annulla_flag_temporanei_T(ASSENTE,PRESENTE);
					AggiornaFinestra();
					break;
				}
				
				//parla uk valore calcolato
				char mm[20];
				sprintf(mm,"%d!",lms.value);
				ParlaS(mm);

			//parola_nuova[strlen(parola_nuova)-1]='*';//glasgow3
			char ch[32];
//			sprintf(ch,"%s*",lms.parola);//nervi
//			SetDlgItemText(ghWndToolbarDlg,IDC_COMBO_SEARCH,ch);//nervi
					
//			SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_BUTTON1,0L);//nervi
				
				
				if(!gMaxPuntiHelp)//falluja: non puoi fregare!
					if(lms.dizionario==IN_DIR)//nassirya
						punticalc=punticalc<lms.value?lms.value:punticalc;//falluja

				sprintf(avviso,"Punti: %d\r\n",lms.value);
				strcat(buffer,avviso);
				AggiungiMessaggio(hdlg,avviso);


				//SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,0L);

	sprintf(avviso,"%s %d\n",__FILE__,__LINE__);
	OutputDebugString(avviso);
	AggiornaFinestra();

#if 0
	{
	int n=MessageBox(ghWndToolbarDlg,"Inserire questa parola?","###",MB_YESNO|MB_ICONINFORMATION);
	if(n==IDYES)
		SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_CONFERMA,0L);//nervi
		else
			SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_ANNULLA,0L);//nervi
}
#endif



				/*				Sleep(3000);

				player=player==PLAYER1?PLAYER2:PLAYER1;
				//#if 0
				if(Assegna_tessere(player)==-1)
				{
					Mostra_tessere();
					n=MessageBox(ghWndToolbarDlg,"Fine Partita: Salvare lo schema?","###",MB_YESNO|MB_ICONINFORMATION);
					if(n==IDYES) salva();
					SendMessage(ghwndMain,WM_CLOSE,NULL,NULL);
					EndDialog(hdlg, LOWORD(wParam));
					return TRUE;
				}
				AggiornaFinestra();
//#endif//qui:;
				player=player==PLAYER1?PLAYER2:PLAYER1;


				SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,0L);
				//test!
*/
  break;

		case IDC_CONFERMA:
			if(Machine_Thinking) break;//okinawa
			if(Global_Demox==1) break;
			//deve tornare i parametri per controll e cioè hv,y,x
				if(!psacco)	break;
				memset(&lms,0,sizeof(lms));
				n=Trovaparola(&lms);
				if(n==1||n==2)
				{
					if(n==1)
						MessageBox(ghWndToolbarDlg,
						//"La parola inserita deve essere\r\nin contatto con quelle già presenti."
						"La disposizione delle lettere non sembra corretta, riprova!"
						,NULL,MB_ICONSTOP);
					SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_ANNULLA,0L);
					//goto qui;
					break;
				}
				else if(n==3)//scarabeo
					lms.value=RITIRA_INSERIMENTO;
				else
					//lms.value=ControLL(lms.hv,lms.index.y,lms.index.x);nassirya
					lms.value=ControLLN(&lms);
				
				if(lms.value==RITIRA_INSERIMENTO)
				{
					//PlaySound("barking dog.wav",NULL,NULL);
					Annulla_flag_temporanei(ASSENTE);
					Annulla_flag_temporanei_T(ASSENTE,PRESENTE);
					//AggiornaFinestra();
					break;
				}


	sprintf(avviso,"%s %d\n",__FILE__,__LINE__);
	OutputDebugString(avviso);

					AggiornaFinestra();
				//falluja lo dimezza solo se superiore al valore precedentemente calcolato
				if(gMaxPuntiHelp>=lms.value && lms.value>punticalc)//verona:dimezza punteggio se aiuto //falluja
						lms.value/=2;//DIMEZZA IL VALORE, DATO CHE SEI STATO AIUTATO
				gMaxPuntiHelp=0;
				punticalc=0;//falluja
				Parla(&lms);


				if(strlen(lms.parola)>2)
				{
				sprintf(ch,"%s*",lms.parola);//nervi
				SetDlgItemText(ghWndToolbarDlg,IDC_COMBO_SEARCH,ch);//nervi
				SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_BUTTON1,0L);//nervi
				}


				Assegna_punti(player,lms.value);
				//iplayer[player].punti+=lms.value;
				Annulla_flag_temporanei(PERMANENTE);
				
				sprintf(avviso,"Punti: %d\r\n",lms.value);
				AggiungiMessaggio(hdlg,avviso);	

	sprintf(avviso,"%s %d\n",__FILE__,__LINE__);
	OutputDebugString(avviso);
				

	sprintf(avviso,"%s %d\n",__FILE__,__LINE__);
	OutputDebugString(avviso);

				AggiornaFinestra();

				
				

				
				
				
				
				player=player==PLAYER1?PLAYER2:PLAYER1;
				
				

				
				if(Assegna_tessere(player)==-1)
				{
					AggiornaFinestra();
					MessaggioFinale();
					SendMessage(ghwndMain,WM_CLOSE,NULL,NULL);// BAHIA COMM//LAPAZ
					EndDialog(hdlg, LOWORD(wParam));// BAHIA COMM//LAPAZ
					
					return TRUE; 
				}
				player=player==PLAYER1?PLAYER2:PLAYER1;

				salva(1);
				SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,0L);
				//test!
				break;

		case WM_SUPERCOMPUTER://gestione okinawa
		//	if(hThreadSC!=INVALID_HANDLE_VALUE)//mutex
			{
				//AggiornaFinestra();
		//		ParlaS("procedura annullata..");
		//		break;
			}


			totalturn++;
				sprintf(avviso,SEPARATURNI);//_C
				strcat(buffer,avviso);
				AggiungiMessaggio(hdlg,avviso);
			


			DWORD dwThrdParam;
			DWORD dwThreadId;

			

			dwThrdParam=(DWORD)&hdlg;

			hThreadSC = CreateThread( 
			NULL,                        // no security attributes 
			0,                           // use default stack size  
			SuperComputer,                  // thread function 
			&dwThrdParam,                // argument to thread function 
			0,                           // use default creation flags 
			&dwThreadId);                // returns the thread identifier 
 
		   // Check the return value for success. 
 
		   if (hThreadSC == NULL) 
		   {
			  sprintf( szMsg, "MAIN: CreateThread failed (%d)",GetLastError() ); 
			  Logga(szMsg);
			  return -1;
		   }
			sprintf( szMsg, "MAIN: SuperComputer [0x%x] Creato",dwThreadId);
			Logga(szMsg);
			if(!Global_Demox)
				SetWindowText(ghWndToolbarDlg,"Aspetta! Ricerca in corso!");
			break;

		case IDC_HELPME:
			if(Machine_Thinking) break;//okinawa
			if(!psacco)	break;
				if(f_1st_help==FALSE)//glasgow
				{
				//f_1st_help=TRUE;//annulla effetto glasgow: voglio sempre la conferma
				
				//char s[160];
				
				//sprintf(s,"Il punteggio della tua prossima parola sarà dimezzato\r\na meno che con questa non superi il mio miglior risultato\r\noppure tu resti al di sotto del tuo ultimo CALCOLO (%d)\r\nVuoi continuare?",punticalc);//falluja
				//n=MessageBox(ghWndToolbarDlg,s,"",MB_YESNO|MB_ICONINFORMATION);
				//if(n!=IDYES)
				//	break;

				}

			gMaxPuntiHelp=0;
			Annulla_flag_temporanei(LIBERA);
			Annulla_flag_temporanei_T(ASSENTE,PRESENTE);//parigi: solo per player 1!!!!
			Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);

			
	sprintf(avviso,"%s %d\n",__FILE__,__LINE__);
	OutputDebugString(avviso);

	
			AggiornaFinestra();

			sflag_mostra_idee=flag_mostra_idee;
			sflag_mostra_tessere=flag_mostra_tessere;
			flag_mostra_idee=flag_mostra_tessere=TRUE;
//#define USTICA 031104
#ifndef USTICA			
			ScambiaTessere();
			gFaseHelp=HELP_IS_ON;
			Mostra_tessere(gFaseHelp);
#else
			ScambiaTessere();
			gFaseHelp=HELP_IS_FOREVER;
			Mostra_tessere(gFaseHelp);

#endif
			SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,777L);
		break;

		case IDC_MYHELP:
			if(Machine_Thinking) break;//okinawa
		if(!psacco)	break;
		salva(1);
			//if(Flag_help_computer)
			//{
#define tryk
#ifdef tryk
		player=PLAYER2;
//					MessageBeep(MB_OK);
					Annulla_flag_temporanei(PERMANENTE);					

	sprintf(avviso,"%s %d\n",__FILE__,__LINE__);
	OutputDebugString(avviso);
					
					AggiornaFinestra();

					if(Assegna_tessere(player)==-1||flag_passo_cpu==TRUE)
					{
						//Mostra_tessere();
						AggiornaFinestra();//LUCCA SCOMM
						
						//Mostra_punti(hdlg);
						
						MessaggioFinale();
						SendMessage(ghwndMain,WM_CLOSE,NULL,NULL);// BAHIA COMM//LAPAZ
					EndDialog(hdlg, LOWORD(wParam));// BAHIA COMM//LAPAZ
						return TRUE;
					}

					//Mostra_tessere();
					//Mostra_punti(hdlg);
					
#endif

	sprintf(avviso,"%s %d\n",__FILE__,__LINE__);
	OutputDebugString(avviso);
					
					AggiornaFinestra();//LUCCA SCOMM
			flag_passo_human=TRUE;//tunisi

				sprintf(avviso,"PASSATO TURNO\r\n");
				strcat(buffer,avviso);
				AggiungiMessaggio(hdlg,avviso);

			player=PLAYER2;
				SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,0L);
				
			//}
			
			//if(Flag_help_computer)

//			SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_SUPERCOMPUTER,0L);

			break;
		case IDC_AST:
				GetDlgItemText(hdlg, IDC_COMBO_SEARCH,Kbuffer,sizeof(Kbuffer));
				strcat(Kbuffer,"*");
				SetDlgItemText(hdlg, IDC_COMBO_SEARCH,Kbuffer);
			break;

		case IDC_PINT:
				GetDlgItemText(hdlg, IDC_COMBO_SEARCH,Kbuffer,sizeof(Kbuffer));
				strcat(Kbuffer,"?");
				SetDlgItemText(hdlg, IDC_COMBO_SEARCH,Kbuffer);
			break;
/*		case IDC_ICS:
				if(0==GetDlgItemText(hdlg, IDC_COMBO_SEARCH,Kbuffer,sizeof(Kbuffer)))
				{
				strcat(Kbuffer,"-");
				SetDlgItemText(hdlg, IDC_COMBO_SEARCH,Kbuffer);
				}
			break;
corinto*/
		case IDC_BUTTON1:
			{
		if(Machine_Thinking) break;//okinawa
			ckey=0;


			memset(mybuffer,0,sizeof(mybuffer));
			memset(buffer,0,sizeof(buffer));
//		SetDlgItemText(ghWndToolbarDlg,IDC_EDIT2,"");
		//if (0 != GetDlgItemText(hdlg, IDC_EDIT1,Kbuffer,sizeof(Kbuffer)))
		if (0 != GetDlgItemText(hdlg, IDC_COMBO_SEARCH,Kbuffer,sizeof(Kbuffer)))
		
		{
			if(SendDlgItemMessage(ghWndToolbarDlg,IDC_COMBO_SEARCH,CB_FINDSTRINGEXACT,-1,(LPARAM)Kbuffer)==CB_ERR)
				int erro=SendDlgItemMessage(ghWndToolbarDlg,IDC_COMBO_SEARCH,CB_INSERTSTRING,0,(LPARAM)Kbuffer);
//			if(strcmp(Kbuffer,Kbuffer_o)&&Kbuffer[0]!=0)
//			{


			
			pc=Kbuffer;
			*pc=tolower(*pc);//elpaso l'aveva commentata senza dire nulla vaffanculo (mazara)
			while(*pc++) *pc=tolower(*pc);


			if(Kbuffer[0]=='-')//elpaso
			{
				FiltraListBox(&Kbuffer[1]);
				return FALSE;
			}
			SendMessage(ghwndMain,WM_COMMAND,(WPARAM)WM_FINDKEYS,(LPARAM)Kbuffer);
			strcpy(Kbuffer_o,Kbuffer);
		}
		else
		{
			sprintf(mybuffer,
				"Inserire la chiave di ricerca.\r\n\r\n? qualunque carattere\r\n* serie di caratteri\r\nEs.\r\n*ar?a*    trova sbarcare,arcata,arpa\r\nar?a*  trova armata,arpa ma non sciarpa\r\n?ar?a  trova farsa ma non arpa nè ciarpame"
			);
			MessageBox(ghWndToolbarDlg,mybuffer,"Ricerca",MB_ICONINFORMATION);
		}
		}
		return FALSE;
		
		case WM_KEYFOUND:
				ckey+=strlen((char*)lparam)+2;
				if(ckey>=sizeof(mybuffer)-16)
					break;

			pc=(char*)lparam;
			i=strlen(pc);
			if(i<0)
				break;
			pc+=i-1;
			if(*pc==VOC1)//a-e
			{
				*pc++='a';
				*pc++='-';
				*pc++='e';
				*pc=0;
			}
			else if(*pc==VOC0)//i-o
			{
				*pc++='o';
				*pc++='-';
				*pc++='i';
				*pc=0;
			}
			else if(*pc==VOC2)//e-i
			{
				*pc++='e';
				*pc++='-';
				*pc++='i';
				*pc=0;
			}
			else if(*pc==VOC3)//a-e-i-o
			{
				*pc++='a';
				*pc++='-';
				*pc++='e';
				*pc++='-';
				*pc++='i';
				*pc++='-';
				*pc++='o';
				*pc=0;
			}
			else if(*pc==VOC4)//(null)-o
			{
				*pc++='-';
				*pc++='o';
				*pc=0;
			}

			else if(*pc==VOC5)//a-e-i
			{
				*pc++='a';
				*pc++='-';
				*pc++='e';
				*pc++='-';
				*pc++='i';
				*pc=0;
			}
			else if(*pc==VOC6)//a-i-o
			{
				*pc++='a';
				*pc++='-';
				*pc++='i';
				*pc++='-';
				*pc++='o';
				*pc=0;
			}
			else if(*pc==VOC7)//e-i-o
			{
				*pc++='e';
				*pc++='-';
				*pc++='i';
				*pc++='-';
				*pc++='o';
				*pc=0;
			}
			else if(*pc==VOC11)//e-i-o
			{
				*pc++='a';
				*pc++='-';
				*pc++='e';
				*pc++='-';
				*pc++='o';
				*pc=0;
			}
			else if(*pc==VOC8)//a-i
			{
				*pc++='a';
				*pc++='-';
				*pc++='i';
				*pc=0;
			}
			else if(*pc==VOC9)//a-o
			{
				*pc++='a';
				*pc++='-';
				*pc++='o';
				*pc=0;
			}
			else if(*pc==VOC10)//e-o
			{
				*pc++='e';
				*pc++='-';
				*pc++='o';
				*pc=0;
			}


			pc=(char*)lparam;
			*pc=toupper(*pc);
			while(*pc++)
				*pc=toupper(*pc);


				strcat(mybuffer,(char*)lparam);
				strcat(mybuffer,"\r\n");
				//SetDlgItemText(hdlg,IDC_LIST1,buffer);
				//SetWindowText(lista,buffer);

		break;
		
		case WM_KEYEND:
			if(!ckey)
				sprintf(mybuffer,"<%s> ?",lemma[0].parola);
			if((int)lparam)//todi
				strcat(mybuffer,"<...>");



			AggiungiMessaggio(hdlg,mybuffer);

		    break;
		}
  }
    return FALSE;
}

/*-----------------------------------------------------------------------------

FUNCTION: InitializeApp(HINSTANCE, int)

PURPOSE: GlobalInitialize, Register window classes 
         and create main window

PARAMETERS:
    hInst    - HINSTANCE of this app
    nShowCmd - code for showing this window

RETURN:
    TRUE  - successful inititialization of this app
    FALSE - failure to init app

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL InitializeApp(HINSTANCE hInst, int nShowCmd)
{

    
	
	
	WNDCLASS wc = {0};


	//    GlobalInitialize();     // get all global variables initialized to defaults
/*
	COLOR_ACTIVEBORDER
COLOR_ACTIVECAPTION
COLOR_APPWORKSPACE
COLOR_BACKGROUND
COLOR_BTNFACE
COLOR_BTNSHADOW
COLOR_BTNTEXT
COLOR_CAPTIONTEXT
COLOR_GRAYTEXT
COLOR_HIGHLIGHT
COLOR_HIGHLIGHTTEXT
COLOR_INACTIVEBORDER
COLOR_INACTIVECAPTION
COLOR_MENU
COLOR_MENUTEXT
COLOR_SCROLLBAR
COLOR_WINDOW
COLOR_WINDOWFRAME
COLOR_WINDOWTEXT 
	*/
    //
    // setup program's main window class
    //
	wc.style			= CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW ; 
	//wc.style			= CS_DBLCLKS | CS_SAVEBITS; 
    wc.lpfnWndProc      = (WNDPROC) MTTTYWndProc;
    wc.hInstance        = hInst;
    wc.hIcon            = LoadIcon(hInst,MAKEINTRESOURCE(IDI_APP));
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.lpszMenuName     = MAKEINTRESOURCE(IDR_MENU1);
    //wc.hbrBackground    = bru;//(HBRUSH) (COLOR_WINDOW + 1) ;
	wc.hbrBackground    = (HBRUSH) ( 1) ;
    wc.lpszClassName    = "ScaraClass";

    if (!RegisterClass(&wc)) {
        //GlobalCleanup();
        return FALSE;
    }


  
    //
    // create main window
    //
    ghwndMain = CreateWindow("ScaraClass", "ScaraBIT",
            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
            STARTXWINDOW, STARTYWINDOW,
            MAXXWINDOW, MAXYWINDOW,
            NULL, NULL, hInst, NULL);


    if (ghwndMain == NULL) {
        ErrorReporter("CreateWindow. Impossibile creare la finestra principale.");//GlobalCleanup();
        return FALSE;
    }

/* portorico				
				HDC hdc;
				hdc=GetWindowDC(
				  ghwndMain   // handle to window
				);

	
	SetBkColor(
  hdc,           // handle to DC
  RGB(255,255,255) );  // background color value
*/

	
	return TRUE;
}


int WINAPI MTTTYWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//LPPOINT punto;
//int a;
DWORD err;
//HCURSOR hCurs1, hCurs2;    // cursor handles 
//POINT pt;                  // cursor location  
//RECT rc;                   // client area coordinates 
static int repeat = 1;     // repeat key counter 
 char Wildcard[80];
 char Apz[80];
//HDC hdc;
    switch (message) 
    {
	case WM_CREATE:
            //
            // since main window is created, I can now open all other windows
            //

			ghWndToolbarDlg = ::CreateDialog(ghInst, 
				MAKEINTRESOURCE(IDD_DIALOG1), 
				ghwndMain, 
				KeyProc);

				if (ghWndToolbarDlg == NULL)
				{
					ErrorReporter("CreateDialog (Toolbar Dialog). Impossibile creare la finestra.");
						char gg[128];
						sprintf(gg,"ghInst:%x Res:%x Wnd:%p",ghInst,MAKEINTRESOURCE(IDD_DIALOG1),ghwndMain);
					ErrorReporter(gg);
					exit(GetLastError());
				}

				SetWindowText(ghWndToolbarDlg,"ScaraBIT");		

				GetRapportoXY(&rapportox,&rapportoy);//cefalu2
				//SendMessage(ghWndToolbarDlg,WM_COMMAND,IDC_START,NULL);


			if (
				hThreadSC != NULL
				&&
				hThreadSC !=INVALID_HANDLE_VALUE
				) 
					CloseHandle(hThreadSC);//viareggio

				hThreadSC=INVALID_HANDLE_VALUE;	//non puo stare nella initstructz xche anche ripristina() non lo deve reinizializzare okinawa
				InitStructz();


//BOMB scommenta				
					if(ripristina(1))
			flag_prima_tessera=FALSE;
				
									char msg[80];
					sprintf(msg,SEPARATURNI);
					AggiungiMessaggio(ghWndToolbarDlg,msg);


				//				MostraCase();
				AggiornaFinestra();
//				ShowBoard();
/*
				hdc=GetDC(ghWndToolbarDlg);
SetBkColor(
  hdc,           // handle to DC
  RGB(255,0,180)   // background color value
);
*/

				//portorico
				/*
				HDC hdc;
				hdc=GetWindowDC(
				  ghWndToolbarDlg   // handle to window
				);
				

					SetBkColor(
				  hdc,           // handle to DC
				  RGB(255,255,255)   // background color value
				);	
				UpdateWindow(ghWndToolbarDlg);
				
				*/
				break;
	case WM_DESTROY: 
            //
            // since main windows is being destroyed, so same to other windows
            //
           
			PostQuitMessage(0);
            break;

        case WM_SIZE:
         
            break;

      case WM_COMMAND:       
          //  CmdDispatch(LOWORD(wParam), hwnd, lParam);        
				switch(LOWORD(wParam))
				{
				case IDM_ESCAPE:
//						Beep(199,100);
					break;
					case WM_FINDKEYS:
						strcpy(Apz,(char*)lParam);
						ConvertWildcards(Apz,Wildcard);
						if(Wildcard[0])
							FindKeys(Wildcard);	
						//FindKeys((char*)lParam);	
					break;
					/*
					case WM_KEYFOUND:
						SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_KEYFOUND,lParam);
					break;
					*/
				}
		 
		break;

      case WM_CHAR:
     break;

      case WM_CLOSE:
		  if(!HeapDestroy(hDataHeap))
					err=GetLastError();
                DestroyWindow(hwnd);
//				DeleteFile("scarabeo.tmp"); NO, SERVE PER IL RIPRISTINO AUTOMATICO
            break;

      default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0L;
}


TIMERPROC OnTimer()//praga comm
{
 
  if(++timercount=1)
  {
	  KillTimer(NULL,timer);
	  timercount=0xFFFF;
	  AggiornaFinestra();//ShowBoard();
//	  LeggiVocabolario();
  }	
return 0;
}

int crypt(HANDLE fileIn,HANDLE fileOut)
{
	/*
	Serve a crittare o decrittare files con la tabella crc32
	fileIn = puntatore al file aperto in lettura
	fileOut = puntatore al file aperto in scrittura
	usando la tabella unsigned long crcTable[256] trasforma fileIn in fileOut
	*/
	unsigned long ul;
	unsigned long wl;
	byte count=0;

	byte *ptab=(byte*)&crcTable[4];//punta all'inizio della tabella (i primi 4 sono zeri)
	byte read,write;
	SetFilePointer(fileIn,0,0,FILE_BEGIN);
	while(ReadFile(fileIn,&read,1,&ul,NULL))
	{
		if(!ul)
			break;
		write=(byte)read^*(ptab+count);
		WriteFile(fileOut,&write,1,&wl,NULL);
		count++;
		count%=1020;
	//	SetFilePointer(fileIn,1,0,FILE_CURRENT);
	}
	return count;
}
/****************************************************************************/
void crcgen( )
{
	unsigned long	crc, poly;
	int	i, j;

	//poly = 0xEDB88320L;
	poly = 0xcaf6be27L;
	for (i=0; i<256; i++) {
		crc = i;
		for (j=8; j>0; j--) {
			if (crc&1) {
				crc = (crc >> 1) ^ poly;
			} else {
				crc >>= 1;
			}
		}
		crcTable[i] = crc;
	}
}

int maincrypt(int op)
{
HANDLE fpr,fpw;
//int n;




//prima testa crypt
switch(op)
{
case KRYPT:
fpr=CreateFile(
		   gFILE_VOCABOLARIO,
		   GENERIC_READ,
		   FILE_SHARE_READ,
		   NULL,
		   OPEN_EXISTING,
		   NULL,
		   NULL	);

if(fpr==INVALID_HANDLE_VALUE)
	return 1;

//fpw=fopen(FILE_CRYPT,"wb");
fpw=CreateFile(
		   FILE_CRYPT,
		   GENERIC_WRITE,
		   NULL,
		   NULL,
		   CREATE_ALWAYS,
		   NULL,
		   NULL	);

if(fpw==INVALID_HANDLE_VALUE){
	CloseHandle(fpr);
	return 1;
	}


break;

case DEKRYPT:
//fpr=fopen(FILE_CRYPT,"rb");
fpr=CreateFile(
		   FILE_CRYPT,
		   GENERIC_READ,
		   FILE_SHARE_READ,
		   NULL,
		   OPEN_EXISTING,
		   NULL,
		   NULL	);

if(fpr==INVALID_HANDLE_VALUE)
	return 1;

fpw=CreateFile(
		   gFILE_VOCABOLARIO,
		   GENERIC_WRITE,
		   NULL,
		   NULL,
		   CREATE_ALWAYS,
		   NULL,
		   NULL	);

if(fpw==INVALID_HANDLE_VALUE){
	CloseHandle(fpr);
	return 1;
	}


	break;
}

crypt(fpr,fpw);
CloseHandle(fpw);
CloseHandle(fpr);
return 0;
}


int LeggiVocabolario(){
/*
	int z=MessageBox(ghwndMain,"Premere Yes per Italiano\r\nPress No for English","",MB_YESNO|MB_ICONQUESTION);
	if(z==IDYES)
		strcpy(gFILE_VOCABOLARIO,FILE_VOCABOLARIO_IT);
	else
		strcpy(gFILE_VOCABOLARIO,FILE_VOCABOLARIO_EN);
*/
#ifdef ITALIA
	strcpy(gFILE_VOCABOLARIO,FILE_VOCABOLARIO_IT);
#else
	strcpy(gFILE_VOCABOLARIO,FILE_VOCABOLARIO_EN);
#endif
	crcgen();
#ifdef KRYPTER
	if(maincrypt(DEKRYPT))
	{
		ErrorReporter("Vocabolario Assente");
		return 0;
	}
	HeapInit();
	DeleteFile(gFILE_VOCABOLARIO);
#else
	HeapInit();
#endif

#ifdef LUBECK
	Install();//LUBECK prova!!
	if(!CheckRegister())//LUBECK
	{
		ErrorReporter("TEMPO VALUTAZIONE SCADUTO");
		return 0;
	}
#endif

	return 1;
}
/*
Translate(char *pb)
{

	char mio[32];
	char *pm=mio;

			*pb=tolower(*pb);
			while(*pb)
				*pb=tolower(*pb);

			if(*pb=='*');
			else if(*pb!='$')
			{
				*pm++='$'

			}
			strcpy(pm,pb);
			pb=pm;
}			
*/

int CheckRegister()//LUBECK
{

	SYSTEMTIME Sy;
	
	//legge la data di sistema
	GetSystemTime(
	&Sy   // system time
	);

	char szI[12];
	sprintf(szI,"%02d%04d%02d",Sy.wMonth,Sy.wYear,Sy.wDay);
	
	
	DWORD dwtype,dwlen;
	TCHAR szP[32];
    
//    LONG lRet;
	
	HKEY hk1,hk2;
	

	if(RegOpenKey(
	HKEY_LOCAL_MACHINE,        // handle to open key
	"Software", // name of subkey to open
	&hk1  // handle to open key
	)==ERROR_SUCCESS)
		if(RegOpenKey(
		hk1,        // handle to open key
		"Skr", // name of subkey to open
		&hk2  // handle to open key
		)==ERROR_SUCCESS)
			RegQueryValueEx(hk2,"Krp",NULL,&dwtype,(LPBYTE)szP,&dwlen);
	RegCloseKey(hk2);
	RegCloseKey(hk1);

	//adesso ho una data criptata dentro szP
	byte *ptab=(byte*)&crcTable[27];//punta alla tabella (i primi 4 sono zeri)
	char dec[9];
	//la data di installazione deve essere nel formato MMAAAAGG
	for(int count=0;count<8;count++)
		dec[count]=(char)szP[count]^*(ptab+count);
	//adesso dec contiene la data di installazione in chiaro..
	
	int me=(szI[0]-0x30)*10+(szI[1]-0x30);
	int mi=(dec[0]-0x30)*10+(dec[1]-0x30);

	int ae=(szI[2]-0x30)*1000+(szI[3]-0x30)*100+(szI[4]-0x30)*10+(szI[5]-0x30);
	int ai=(dec[2]-0x30)*1000+(dec[3]-0x30)*100+(dec[4]-0x30)*10+(dec[5]-0x30);

	int ge=(szI[6]-0x30)*10+(szI[7]-0x30);
	int gi=(dec[6]-0x30)*10+(dec[7]-0x30);

	int dayE=ge+me*30+ae*30*12;
	int dayI=gi+mi*30+ai*30*12;

	if(abs(dayE-dayI)>90)
		return FALSE;

	return TRUE;
}


int Install()//LUBECK
{

	HKEY hk1,hk2;
	
//SE PROGRAMMA GIa installato esce
	if(RegOpenKey(
	HKEY_LOCAL_MACHINE,        // handle to open key
	"Software", // name of subkey to open
	&hk1  // handle to open key
	)==ERROR_SUCCESS)
		if(RegOpenKey(
		hk1,        // handle to open key
		"Skr", // name of subkey to open
		&hk2  // handle to open key
		)==ERROR_SUCCESS)
		{
			RegCloseKey(hk2);
			RegCloseKey(hk1);
			return FALSE;
		}
	RegCloseKey(hk2);
	RegCloseKey(hk1);

	//INSTALLA IL PROGRAMMA
	SYSTEMTIME Sy;
	
	//legge la data di sistema
	GetSystemTime(
	&Sy   // system time
	);
	
	char szI[12];
	sprintf(szI,"%02d%04d%02d",Sy.wMonth,Sy.wYear,Sy.wDay);

	byte *ptab=(byte*)&crcTable[27];//punta alla tabella (i primi 4 sono zeri)
	char dec[12];
	//la data di installazione deve essere nel formato MMAAAAGG
	for(int count=0;count<8;count++)
		dec[count]=(char)szI[count]^*(ptab+count);

	
//	DWORD dwtype,dwlen;
//	TCHAR szP[32];
    
//    LONG lRet;

	if(RegOpenKey(
	HKEY_LOCAL_MACHINE,        // handle to open key
	"Software", // name of subkey to open
	&hk1  // handle to open key
	)==ERROR_SUCCESS)
		if(RegCreateKey(
		hk1,        // handle to open key
		"Skr", // name of subkey to open
		&hk2  // handle to open key
		)==ERROR_SUCCESS)
			RegSetValueEx(
			hk2,           // handle to key
			"Krp", // value name
			NULL,      // reserved
			REG_SZ,        // value type
			(BYTE*)&dec[0],  // value data
			8         // size of value data
);
	RegCloseKey(hk2);
	RegCloseKey(hk1);

	return TRUE;
}

void Logga(char* msg)
{
OutputDebugString(msg);
}

int FiltraListBox(char* m)//elpaso
{
	
	char bufedit[4096*2];
	char bufedit2[4096*2];
	char *p;
	
	memset(bufedit2,0,sizeof(bufedit2));
	GetDlgItemText(ghWndToolbarDlg,IDC_EDIT2,bufedit,sizeof(bufedit)-1);
	p=strtok(bufedit,"\r\n");
	if(!p) return 0;
	int flag=0;
	for(int n=0;n<strlen(m);n++)
	{
		
		if(strchr(p,toupper(*(m+n)))) flag++;
	}
	if(!flag)
	{
		strcat(bufedit2,p);
			strcat(bufedit2,"\r\n");
	}
	while(p) 
	{
		p=strtok(NULL,"\r\n");
		
		if(!p) break;
		//if(strlen(p)<3) continue; 
		int flag=0;
		for(int n=0;n<strlen(m);n++)
		{
			if(strchr(p,toupper(*(m+n)))) flag++;
		}

		if(strlen(m)==1)
		{
		if(toupper(*m)=='A')
		{
			if(strstr(p,"A-")||strstr(p,"-A")) flag=0;
		}
		
		if(toupper(*m)=='E')
		{
			if(strstr(p,"E-")||strstr(p,"-E")) 
				flag=0;
		}
		if(toupper(*m)=='I')
		{
			if(strstr(p,"I-")||strstr(p,"-I")) flag=0;
		}
		
		if(toupper(*m)=='O')
		{
			//if(strstr(p,"-O")) flag=0;
			if(strstr(p,"O-")||strstr(p,"-O")) flag=0;
		}
		}

		if(!flag )
		{
			strcat(bufedit2,p);
				strcat(bufedit2,"\r\n");
		}

	}

	SetDlgItemText(ghWndToolbarDlg,IDC_EDIT2,bufedit2);			
/*
	int erro=SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_GETCOUNT,0,0);			
	for(int n=0;n<erro;n++)
	{
		SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_SETCURSEL,(WPARAM)(n),(LPARAM)0);
		SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_GETTEXT,(WPARAM)(erro),(LPARAM)bufedit);

	}
*/
return 0;
}


int MessaggioFinale()
{
	/*
	if(iplayer[PLAYER1].punti){
	sprintf(zona_appoggio[0].parola,"Uomo: punti");
	zona_appoggio[0].value=iplayer[PLAYER1].punti;
	Parla(&zona_appoggio[0]);						
	}
	Sleep(4000);
	if(iplayer[PLAYER2].punti){
	sprintf(zona_appoggio[0].parola,"Macchina: punti");
	zona_appoggio[0].value=iplayer[PLAYER2].punti;
	Parla(&zona_appoggio[0]);						
	}

	
	*/
//	if(*lpCmdLine=='#')
//		*lpCmdLine=0X1B;
//						PlaySound("DING.wav",NULL,NULL);
	PlaySound(
  "btnup.wav",  
  NULL,     
 SND_FILENAME|SND_NODEFAULT    
);

	char bu[800];
	if(iplayer[PLAYER1].punti)
		sprintf(bu,"#r4Uomo %d Macchina %d.\r\n%s vince.",
			iplayer[PLAYER1].punti,
			iplayer[PLAYER2].punti,
			iplayer[PLAYER1].punti>iplayer[PLAYER2].punti?"Uomo":
			iplayer[PLAYER2].punti>iplayer[PLAYER1].punti?"Macchina":"Nessuno"
			
			);

	else
		sprintf(bu,"#r4La macchina ha totalizzato %d.\r\n",
			iplayer[PLAYER2].punti
			);

	
	strcat(bu,"\r\nSalvare la partita?");

	int n=MessageBox(ghWndToolbarDlg,bu+3,"Fine partita. Salvare?",MB_YESNO|MB_ICONINFORMATION);//ENNA 2CHK
	//int n=MessageBox(ghWndToolbarDlg,bu+3,"Fine partita.",MB_ICONINFORMATION);
	if(n==IDYES)
		salva();
	DeleteFile("scarabeo.tmp");//GIUSTO

return 0;	
}

char IsValid(POINT p)
{
	//questo controlla che la casa puntata dal punto P non sia FUORI DALLO SCHERMO
	if(
		p.x<15
		&&
		p.y<15
		&&
		p.x>=0
		&&
		p.y>=0
		&&
		casa[p.y][p.x].s.lettera 
		&&
		(
		casa[p.y][p.x].flag==TEMPORANEA_PL1
		||
		casa[p.y][p.x].flag==PERMANENTE
		)
		&&
		casa[p.y][p.x].reserved==0
		&&
		casa[p.y][p.x].s.reserved==0)
		
		return((casa[p.y][p.x].fsc&&casa[p.y][p.x].flag==TEMPORANEA_PL1)?'?':casa[p.y][p.x].s.lettera);
		
	return 0;

}

int LeggiParolaInFormazione(POINT p)
{
	char ch;
	char buf[32];
	memset(buf,0,sizeof(buf));

	POINT d,e,f,g;
	
	d=p;

	
	while(IsValid(d))
		d.x--;
	d.x++;
	g=d;
	while(IsValid(g))
		g.x++;
	g.x--;

	e=p;
	while(IsValid(e))
		e.y--;
	e.y++;
	f=e;
	while(IsValid(f))
		f.y++;
	f.y--;


	int n=0;
	if(f.y-e.y>g.x-d.x)
	{
	while(ch=IsValid(e))
	{
		buf[n]=ch;
		e.y++;
		n++;
	}
	}
	else
	{
	while(ch=IsValid(d))
	{
		buf[n]=ch;
		d.x++;
		n++;
	}
	}
	char b2[32];
	sprintf(b2,"#m1%s",buf);

	ParlaS(b2);
	return 0;
}

#if 0
LeggiParolaInFormazione(POINT p)
{
	char buf[32];
	memset(buf,0,sizeof(buf));

	POINT d,e,f,g;
	
	d=p;

	while(casa[d.y][d.x].s.lettera&&casa[d.y][d.x].flag&&casa[d.y][d.x].reserved==0)
		d.x--;
	d.x++;
	g=d;
	while(casa[g.y][g.x].s.lettera&&casa[g.y][g.x].flag&&casa[g.y][g.x].reserved==0)
		g.x++;
	g.x--;

	e=p;
	while(casa[e.y][e.x].s.lettera&&casa[e.y][e.x].flag&&casa[e.y][e.x].reserved==0)
		e.y--;
	e.y++;
	f=e;
	while(casa[f.y][f.x].s.lettera&&casa[f.y][f.x].flag&&casa[f.y][f.x].reserved==0)
		f.y++;
	f.y--;


	int n=0;
	if(f.y-e.y>g.x-d.x)
	{
	while(casa[e.y][e.x].s.lettera&&casa[e.y][e.x].flag&&casa[e.y][e.x].reserved==0)
	{
		buf[n]=casa[e.y][e.x].s.lettera;
		e.y++;
		n++;
	}
	}
	else
	{
	while(casa[d.y][d.x].s.lettera&&casa[d.y][d.x].flag&&casa[d.y][d.x].reserved==0)
	{
		buf[n]=casa[d.y][d.x].s.lettera;
		d.x++;
		n++;
	}
	}
	char b2[32];
	sprintf(b2,"#m1%s",buf);

	ParlaS(b2);
}
#endif



int poipoipoi(
    HWND hWnd ,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT uType)
{

  int i= ::MessageBoxA(
  ghWndToolbarDlg,          // handle to owner window
  lpText,     // text in message box
  "ScaraBIT",  // message box title
   uType
  |
  MB_ICONHAND
  |						//con questi flag messi a cazzo la messagebox non fa dING!!!
  MB_APPLMODAL			//NON TOCCARE nIENTE
  |
  MB_ICONINFORMATION  
   );
return i;
}
int Assegna_punti(int player,int value)
{
	//for(int n=0;n<value;n++)
	//{
		//Sleep(10);
		iplayer[player].punti+=value;
//		Mostra_punti(ghWndToolbarDlg);
	//}
		return 0;
}
int Mescola_tessere()
{
	struct tesseraSTR appo;
	int dest,src;
		//for(int n=0;n<8;n++)
		//{
			src=rand()%(8);
			do{dest=rand()%(8);}while(src==dest);
			
			memcpy(&appo,&tessera[player][dest],sizeof(appo));
			memcpy(&tessera[player][dest],&tessera[player][src],sizeof(appo));
			memcpy(&tessera[player][src],&appo,sizeof(appo));
		
			Mostra_tessere_davvero();
		//}
return 0;
}
