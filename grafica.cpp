#include "windows.h"
#include "resource.h"
#include "scarabeo.h"

#include <stdio.h>

extern HINSTANCE			ghInst;
extern HWND					ghWndToolbarDlg;
extern struct tesseraSTR	tessera[2][8];
extern BYTE					gselection;
extern struct casaSTR		casa[15][15];
extern int					flag_mostra_tessere;
extern int					flag_mostra_idee;
extern BYTE player;
extern struct playerSTR iplayer[2];
extern int gIndexBoard;
extern BYTE gFaseHelp;
extern unsigned short psacco;//punta alla prossima lettera nel sacco;
extern int iBASEX,iBASEY,iDIMBOARD,iDIMTESSERA,iXTESSERA,iYTESSERA;//cefalu
extern int iXMAN1,iXMAC1,iYPUNTO,iDIMXCIFRA,iDIMYCIFRA,iDISTACCO,iXMAS1,iYSUNTO;//cefalu
//DISEGNA LA TAVOLA DI GIOCO
int ShowBoard()
{
	OutputDebugString("SB-");
	int valret=0;
	HANDLE hbitmap;
	HDC hdc,memdc;
	HGDIOBJ gdi;//jakarta

		//hdc=CreateDC("DISPLAY",NULL,NULL,NULL);
	hdc=GetDC(ghWndToolbarDlg);	
	memdc=CreateCompatibleDC(hdc);
	hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_U));//TAVOLAGIOCO));CATANIA
	gdi=SelectObject(memdc,hbitmap);
//	if (!BitBlt(hdc, BASEX,BASEY,DIMBOARD,DIMBOARD,memdc,0,0,SRCCOPY)) 
//		valret=1;

	if (!StretchBlt(hdc, //cefalu
		iBASEX,iBASEY,iDIMBOARD,iDIMBOARD,memdc,0,0,DIMBOARD,DIMBOARD,SRCCOPY)) 
		valret=1;
	
	DeleteObject(hbitmap);
	DeleteObject(gdi);
	ReleaseDC(ghWndToolbarDlg,hdc);
	DeleteDC(memdc);
	return valret;
}
int ShowLogo()
{/*
	HANDLE hbitmap;
	HDC hdc,memdc;

		//hdc=CreateDC("DISPLAY",NULL,NULL,NULL);
	hdc=GetDC(ghWndToolbarDlg);	
	memdc=CreateCompatibleDC(hdc);
	hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_TAVOLAGIOCO));
	SelectObject(memdc,hbitmap);
	if (!BitBlt(hdc, BASEX+3,BASEY+22,DIMBOARD,DIMBOARD,memdc,0,0,SRCCOPY)) 
		return 1;*/
	return 0;
}
int SelezionaTessera(BYTE player,int selection)
{
	int valret=0;
	struct tesseraSTR appo;
	HANDLE hbitmap;
	HDC hdc,memdc;
	DWORD op;
	HGDIOBJ gdi;//jakarta
//	int n;
OutputDebugString("ST-");
	//se la tessera è in chiaro la mette in reverse
	//e copia le info nella tesseraselect
	//altrimenti fa il contrario
	if(tessera[player][selection].flag==ASSENTE &&gselection==NOT_SELECTED)
		return 1;
	if(gselection==NOT_SELECTED)
	{
		op=NOTSRCCOPY;
		gselection=selection;
	}
	else
	{
		if(gselection!=selection)//qui controlla che non ci sia un 'altra tesserea selezionata
		{
			memcpy(&appo,&tessera[player][gselection],sizeof(struct tesseraSTR));
			memcpy(&tessera[player][gselection],&tessera[player][selection],sizeof(struct tesseraSTR));
			memcpy(&tessera[player][selection],&appo,sizeof(struct tesseraSTR));
			gselection=selection=NOT_SELECTED;
			Mostra_tessere_davvero();
			return 0;
		}
		
			op=SRCCOPY;
			gselection=NOT_SELECTED;
	}

	hdc=GetDC(ghWndToolbarDlg);	
	memdc=CreateCompatibleDC(hdc);

	hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(tessera[player][selection].s.bitmap));
	gdi=SelectObject(memdc,hbitmap);
/*
	if (!BitBlt(hdc, 
               tessera[player][selection].x,
			   tessera[player][selection].y, 
               DIMTESSERA,DIMTESSERA, 
              memdc, 
               0,0, 
               op)) 
*/				if (!StretchBlt(hdc, //cefalu
					   tessera[player][selection].x,
					   tessera[player][selection].y, 
					   iDIMTESSERA,iDIMTESSERA, 
					  memdc, 
					   0,0, 
					   DIMTESSERA,DIMTESSERA,
					   op)) 

				valret= 1;
	DeleteObject(hbitmap);
	DeleteObject(gdi);
	ReleaseDC(ghWndToolbarDlg,hdc);
	DeleteDC(memdc);
	Mostra_tessere();
	return valret;

}

int DeponiLettera(BYTE plr,POINT icasa,BYTE itess)
{

	
	
	
OutputDebugString("DL-");	

	//ShellExecute(ghWndToolbarDlg,"open","btnup.wav","","",SW_HIDE);
if(plr==PLAYER1)
	BOOL b=PlaySound(
  "btnup.wav",  
  NULL,     
 SND_FILENAME|SND_NODEFAULT    
);

	int valret=0;

	//se itess==NOT_SELECTED deve rimettere a zero la casella
	HANDLE hbitmap;
	HDC hdc,memdc;
	HGDIOBJ gdi=NULL;//jakarta

	hdc=GetDC(ghWndToolbarDlg);	
	memdc=CreateCompatibleDC(hdc);
	
	if(itess==NOT_SELECTED)
	{
		casa[icasa.y][icasa.x].s.lettera=0;
		casa[icasa.y][icasa.x].s.valore=0;
		casa[icasa.y][icasa.x].s.bitmap=casa[icasa.y][icasa.x].obitmap;
		casa[icasa.y][icasa.x].flag=0;

		if(plr==PLAYER1||(plr==PLAYER2 && flag_mostra_idee))//2013
		{
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(casa[icasa.y][icasa.x].s.bitmap));
		gdi=SelectObject(memdc,hbitmap);
		if (!StretchBlt(hdc, //cefalu
               casa[icasa.y][icasa.x].x,
			   casa[icasa.y][icasa.x].y,
               iDIMTESSERA,iDIMTESSERA, 
              memdc, 
               0,0,
			   DIMTESSERA,DIMTESSERA, 
               SRCCOPY))
				valret=1;
		DeleteObject(hbitmap);//parigi jakarta corregge
		}

	}
	else
	{
		casa[icasa.y][icasa.x].s.lettera=tessera[plr][itess].s.lettera;
		casa[icasa.y][icasa.x].s.valore=tessera[plr][itess].s.valore;
		casa[icasa.y][icasa.x].s.bitmap=tessera[plr][itess].s.bitmap;
		if(casa[icasa.y][icasa.x].s.lettera=='@')
			casa[icasa.y][icasa.x].fsc=1;
		else
			casa[icasa.y][icasa.x].fsc=0;
		casa[icasa.y][icasa.x].flag=plr+1;

		if(plr==PLAYER1||(plr==PLAYER2 && flag_mostra_idee))//2013
		{
			hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(tessera[plr][itess].s.bitmap));
			gdi=SelectObject(memdc,hbitmap);
			if (!StretchBlt(hdc, //cefalu
				   casa[icasa.y][icasa.x].x,
				   casa[icasa.y][icasa.x].y,
				   iDIMTESSERA,iDIMTESSERA, 
				  memdc, 
				   0,0,
				   DIMTESSERA,DIMTESSERA, 
				   NOTSRCCOPY))//siena
					valret= 1;		
			DeleteObject(hbitmap);
		}

	}
	if(gdi)//28/6/18
		DeleteObject(gdi);//jakarta
	ReleaseDC(ghWndToolbarDlg,hdc);
	DeleteDC(memdc);

	return valret;
}
int DeponiPrimaLettera(BYTE plr,POINT icasa,BYTE itess)
{
	int valret=0;
OutputDebugString("DPL-");
	//se itess==NOT_SELECTED deve rimettere a zero la casella
	HDC hdc,memdc;

	hdc=GetDC(ghWndToolbarDlg);	
	memdc=CreateCompatibleDC(hdc);
	
	if(itess==NOT_SELECTED)
	{
		casa[icasa.y][icasa.x].s.lettera=0;
		casa[icasa.y][icasa.x].s.valore=0;
		casa[icasa.y][icasa.x].s.bitmap=casa[icasa.y][icasa.x].obitmap;
		casa[icasa.y][icasa.x].flag=0;
				valret=1;
	}
	else
	{
		casa[icasa.y][icasa.x].s.lettera=tessera[plr][itess].s.lettera;
		casa[icasa.y][icasa.x].s.valore=tessera[plr][itess].s.valore;
		casa[icasa.y][icasa.x].s.bitmap=tessera[plr][itess].s.bitmap;
		if(casa[icasa.y][icasa.x].s.lettera=='@')
			casa[icasa.y][icasa.x].fsc=1;
		else
			casa[icasa.y][icasa.x].fsc=0;

		casa[icasa.y][icasa.x].flag=(plr?TEMPORANEA_PL2:TEMPORANEA_PL1);//plr+1;
	}
	//DeleteObject(hbitmap);//parigi
	ReleaseDC(ghWndToolbarDlg,hdc);
	DeleteDC(memdc);

	return valret;
}

int CancellaTessera(BYTE plr ,BYTE index)
{

	int valret=0;
	
	HANDLE hbitmap;
	HDC hdc,memdc;
	HGDIOBJ gdi;//jakarta

OutputDebugString("CT-");
	hdc=GetDC(ghWndToolbarDlg);	
	memdc=CreateCompatibleDC(hdc);
	hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_SCARABEO));
	gdi=SelectObject(memdc,hbitmap);
/*
	if (!BitBlt(hdc, 
               tessera[plr][index].x,
			   tessera[plr][index].y,
               DIMTESSERA,DIMTESSERA, 
              memdc, 
               0,0, 
               SRCCOPY)) 
*/
				if (!StretchBlt(hdc, //cefalu
					   tessera[plr][index].x,
					   tessera[plr][index].y, 
					   iDIMTESSERA,iDIMTESSERA, 
					  memdc, 
					   0,0, 
					   DIMTESSERA,DIMTESSERA,
					   SRCCOPY)) 

		valret=1;
	DeleteObject(hbitmap);
	DeleteObject(gdi);
	ReleaseDC(ghWndToolbarDlg,hdc);
	DeleteDC(memdc);
	
	return valret;

}

//dispone tutte le tessere sullo schermo
int MostraCase()//JAKARTA cerca problema GDI: troppi oggetti allocati schiantano l'APP
{
	
	
	OutputDebugString("MC-");
	
	int valret=0;
	HGDIOBJ gdi;
	int y,x;
	HANDLE hbitmap=NULL;
	HDC memdc;
	PAINTSTRUCT ps;
	HBRUSH hb=CreateSolidBrush(RGB(231,255,0));//LERICI sfondo giallo per scarabeo
	DWORD op;
	
	HDC hdc=BeginPaint(
		ghWndToolbarDlg,            // handle to window
		&ps // paint information
		);	

	//HDC hdc=GetDC(ghWndToolbarDlg);	

	memdc=CreateCompatibleDC(hdc);

	SelectObject(
	  hdc,          // handle to DC jakarta era hdc
	  hb   // handle to object
	);


	for (y=0;y<15;y++)
	{
		for (x=0;x<15;x++)
		{
			if (casa[y][x].flag!=0)
			{
				if(casa[y][x].flag==PERMANENTE)
				{
					if(casa[y][x].fsc) 
						op=MERGECOPY;
					else if(
						casa[y][x].flag_perp==1 //lione
						&& 
						flag_mostra_idee//debug 2013
						) //2013
							op=NOTSRCCOPY;//bologna perpendicolare
					
					else if(casa[y][x].flag_perp==2)
					{
						if(flag_mostra_idee)
							op=NOTSRCCOPY;//bologna perpendicolare
						else
							goto lax;//continue;//op=NOTSRCCOPY;//bologna perpendicolare

					}
					else 
						op=SRCCOPY;
					
				}
				else
				{

					switch(player)//SIENA
					{
						case PLAYER1:
								if(casa[y][x].fsc) op=MERGECOPY;//GIALLO
								else op=NOTSRCCOPY;//NERO
						break;
						case PLAYER2:
							if(flag_mostra_idee) //copia le provvisorie solo se c'è questo flag
							{
								if(casa[y][x].fsc) 
									op=MERGECOPY;//GIALLO
								else 
									op=NOTSRCCOPY;//NERO
							}
							else
								
								continue;
						break;
	
					}
				}
				hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(casa[y][x].s.bitmap));
				gdi=SelectObject(memdc,hbitmap);
				
				if (!StretchBlt(hdc, //cefalu
                casa[y][x].x,
			    casa[y][x].y,
                iDIMTESSERA,iDIMTESSERA, 
                memdc, 
                0,0,
			    DIMTESSERA,DIMTESSERA, 
                op))

					valret=1;
				DeleteObject(hbitmap);//jakarta!
				//}			
				
			}//se c'è una tessera
			else//bergamo
			{
lax:;
				hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(casa[y][x].obitmap));
				
				
				gdi=SelectObject(memdc,hbitmap);
				

				if (!StretchBlt(hdc, //cefalu
                casa[y][x].x,
			    casa[y][x].y,
                iDIMTESSERA,iDIMTESSERA, 
                memdc, 
                0,0,
			    DIMTESSERA,DIMTESSERA, 
                SRCCOPY))

					valret=1;
				DeleteObject(hbitmap);//jakarta!
			
			
			}
		}//next colonna x
	}//next riga y		
	DeleteObject(hb);
	DeleteObject(gdi);
	ReleaseDC(ghWndToolbarDlg,hdc);
	DeleteDC(memdc);

EndPaint(  ghWndToolbarDlg,            // handle to window
  &ps // paint information
);

	return valret;	

}

void AggiornaFinestra()
{
	RECT rect;
		OutputDebugString("AF-");
		//ShowBoard();
		GetClientRect(ghWndToolbarDlg,&rect);
		//InvalidateRect(ghWndToolbarDlg,&rect,FALSE);
		//InvalidateRect(ghWndToolbarDlg,&rect,TRUE);
		//UpdateWindow(ghWndToolbarDlg);
		//GetWindowRect(ghWndToolbarDlg,&rect);
		InvalidateRect(ghWndToolbarDlg,&rect,TRUE);
}

//mostra punteggi dei giocatori
void Mostra_punti(HWND hdlg)//jakarta corregge 
{
/*corinto comm
//	HDC hdc,memdc;
	char appo[32];
//	RECT rect;
				OutputDebugString("MP-");
				sprintf(appo,"%d",iplayer[PLAYER1].punti<1000?iplayer[PLAYER1].punti:999);
				SetDlgItemText(hdlg,IDC_PUNTI1,appo);
				sprintf(appo,"%d",iplayer[PLAYER2].punti<1000?iplayer[PLAYER2].punti:999);
				SetDlgItemText(hdlg,IDC_PUNTI2,appo);	
				sprintf(appo,"%d",NUM_TESSERE-psacco);
				SetDlgItemText(hdlg,IDC_LEFT,appo);	
				
*/				
				/*
		GetClientRect(hdlg,&rect);
		rect.left=500;
		rect.bottom=200;
		InvalidateRect(hdlg,&rect,FALSE);
		UpdateWindow(hdlg);
*//*
		hdc=GetDC(ghWndToolbarDlg);	
		memdc=CreateCompatibleDC(hdc);
		TextOut(hdc,600,200,appo,strlen(appo));
*/

HGDIOBJ gdi;//jAKARTA
HDC hdc,memdc;
char appo[32];
	int valret=0;
	HANDLE hbitmap=NULL;
OutputDebugString("MP-");
	int n;
	hdc=GetDC(ghWndToolbarDlg);	
	memdc=CreateCompatibleDC(hdc);

//		//BitBlt(hdc,XMAN1+n*DISTACCO,YPUNTO,DIMXCIFRA,DIMYCIFRA, memdc, 0,0, SRCCOPY);
	sprintf(appo,"%3d",iplayer[PLAYER1].punti);
	for(n=0;n<3;n++)
	{
		switch(appo[n])
		{
		default:
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_VUOTA)) ;
		break;

		case '0':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA0));
		break;
		case '1':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA1));
		break;
		case '2':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA2));
		break;
		case '3':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA3));
		break;
		case '4':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA4));
		break;
		case '5':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA5));
		break;
		case '6':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA6));
		break;
		case '7':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA7));
		break;
		case '8':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA8));
		break;
		case '9':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA9));
		break;
		}
		gdi=SelectObject(memdc,hbitmap);
		StretchBlt(hdc,iXMAN1+n*iDISTACCO,iYPUNTO,iDIMXCIFRA,iDIMYCIFRA, memdc, 0,0, DIMXCIFRA,DIMYCIFRA,SRCCOPY);
		DeleteObject(hbitmap);//JAKARTA
	}
	
//computer..
//		BitBlt(hdc,XMAC1+n*DISTACCO,YPUNTO,DIMXCIFRA,DIMYCIFRA, memdc, 0,0, SRCCOPY);
	sprintf(appo,"%3d",iplayer[PLAYER2].punti);
	for(n=0;n<3;n++)
	{
		switch(appo[n])
		{
		default:
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_VUOTA)) ;
		break;
		case '0':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA0));
		break;
		case '1':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA1));
		break;
		case '2':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA2));
		break;
		case '3':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA3));
		break;
		case '4':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA4));
		break;
		case '5':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA5));
		break;
		case '6':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA6));
		break;
		case '7':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA7));
		break;
		case '8':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA8));
		break;
		case '9':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA9));
		break;
		}
		gdi=SelectObject(memdc,hbitmap);
		StretchBlt(hdc,iXMAC1+n*iDISTACCO,iYPUNTO,iDIMXCIFRA,iDIMYCIFRA, memdc, 0,0, DIMXCIFRA,DIMYCIFRA,SRCCOPY);
		DeleteObject(hbitmap);//JAKARTA
	}
	DeleteObject(gdi);//JAKARTA
	ReleaseDC(ghWndToolbarDlg,hdc);//JAKARTA
	DeleteDC(memdc);//JAKARTA


}
int Mostra_sacco()//EFESO
{
	HGDIOBJ gdi;//jAKARTA
	HDC hdc,memdc;
	char appo[32];
		int valret=0;
		HANDLE hbitmap=NULL;

	int n;
	hdc=GetDC(ghWndToolbarDlg);	
	memdc=CreateCompatibleDC(hdc);
OutputDebugString("MS-");
	sprintf(appo,"%03d",NUM_TESSERE-psacco);
	for(n=0;n<3;n++)
	{
		switch(appo[n])
		{
		default:
		
			hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_VUOTA)) ;
		break;
		case '0':
		
			hbitmap=LoadBitmap(ghInst,
			n==0
			?
			MAKEINTRESOURCE(IDB_VUOTA)
			:
			(n==1&&appo[0]=='0')
			?
			MAKEINTRESOURCE(IDB_VUOTA)
			:
			(n==2&&appo[0]=='0'&&appo[1]=='0')
			?
			MAKEINTRESOURCE(IDB_VUOTA)
			:
			MAKEINTRESOURCE(IDB_CIFRA0)
			);
		break;
		case '1':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA1));
		break;
		case '2':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA2));
		break;
		case '3':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA3));
		break;
		case '4':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA4));
		break;
		case '5':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA5));
		break;
		case '6':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA6));
		break;
		case '7':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA7));
		break;
		case '8':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA8));
		break;
		case '9':
		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_CIFRA9));
		break;
		}
		gdi=SelectObject(memdc,hbitmap);
		StretchBlt(
			hdc,
			iXMAS1+n*iDISTACCO,
			iYSUNTO+6,
			iDIMXCIFRA,
			iDIMYCIFRA-6, 
			memdc, 
			0,3, 
			DIMXCIFRA,
			DIMYCIFRA-6,
			SRCCOPY//SRCINVERT
			);
		DeleteObject(hbitmap);//JAKARTA
	}
	DeleteObject(gdi);//JAKARTA
	ReleaseDC(ghWndToolbarDlg,hdc);//JAKARTA
	DeleteDC(memdc);//JAKARTA

return 0;
}

int Mostra_tessere_davvero(int FaseHelp)//okkaido
{
OutputDebugString("MTD-");
	//player identifica il giocatore
	//turn dice a chi sta la mano
	//se la mano è di un altro, visualizza in reverse le tessere
	int valret=0;
	HANDLE hbitmap=NULL;
	HDC hdc,memdc;
	DWORD op[2];
	DWORD opzione;
	int n;
	int pl;	
	HGDIOBJ gdi;
	hdc=GetDC(ghWndToolbarDlg);//	jakarta
	memdc=CreateCompatibleDC(hdc);

	/*
	casi possibili
	
	NO HELP NO TESSERE
	mostra normale p1 e dorso p2
	NO HELP TESSERE
	mostra normale p1 e reverse p2
	HELP NO TESSERE
	mostra normale p2 e dorso p1
	HELP TESSERE
	mostra reverse p1 e normale p2
	
	
	
	*/
#define SRCCOPY_D 2424




	for (pl=PLAYER1;pl<=PLAYER2;pl++)
	{
		if (gFaseHelp==HELP_IS_OFF && !flag_mostra_tessere){
			op[PLAYER1]=SRCCOPY;
			op[PLAYER2]=SRCCOPY_D;
		}	
		else if (gFaseHelp==HELP_IS_OFF && flag_mostra_tessere){
			op[PLAYER1]=SRCCOPY;
			op[PLAYER2]=NOTSRCCOPY;
		}	
		else if (gFaseHelp!=HELP_IS_OFF){
			op[PLAYER1]=SRCCOPY_D;
			op[PLAYER2]=SRCCOPY;
		}	
		/*
		else if (FaseHelp==HELP_IS_ON && flag_mostra_tessere){
			op[PLAYER1]=NOTSRCCOPY;
			op[PLAYER2]=SRCCOPY;
		}*/	
		for(n=0;n<8;n++)
		{
			tessera[pl][n].x=(iXTESSERA+pl*DISTANZA_TESSERE)+(n*(iDIMTESSERA-1));
			tessera[pl][n].y=iYTESSERA;
			if(tessera[pl][n].flag==PRESENTE){
				if(op[pl]==SRCCOPY_D)
				{
					opzione=SRCCOPY;
					hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_DORSO));					
				}
				else{
					if(n==gselection)
						opzione=NOTSRCCOPY;
					else
						opzione=op[pl];	
					hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(tessera[pl][n].s.bitmap));
					}
			}
			else	{
				opzione=pl==PLAYER1?SRCCOPY:NOTSRCCOPY;
				hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_SCARABEO));
			}
			gdi=SelectObject(memdc,hbitmap);				
			
			if (!StretchBlt(hdc, //cefalu
				   tessera[pl][n].x,
				   tessera[pl][n].y, 
				   iDIMTESSERA,iDIMTESSERA, 
				  memdc, 
				   0,0, 
				   DIMTESSERA,DIMTESSERA,
				   opzione)) 
					
				   valret=1;

			
			DeleteObject(hbitmap);

		}//next tessera
	}//next player
	DeleteObject(gdi);
	ReleaseDC(ghWndToolbarDlg,hdc);
	DeleteDC(memdc);
	return valret;
}

int Mostra_tessere(int FaseHelp)//okkaido
{

	return 0;

	//player identifica il giocatore
	//turn dice a chi sta la mano
	//se la mano è di un altro, visualizza in reverse le tessere
	int valret=0;
	HANDLE hbitmap=NULL;
	HDC hdc,memdc;
	DWORD op[2];
	DWORD opzione;
	int n;
	int pl;	
	HGDIOBJ gdi;
	hdc=GetDC(ghWndToolbarDlg);//	jakarta
	memdc=CreateCompatibleDC(hdc);

	/*
	casi possibili
	
	NO HELP NO TESSERE
	mostra normale p1 e dorso p2
	NO HELP TESSERE
	mostra normale p1 e reverse p2
	HELP NO TESSERE
	mostra normale p2 e dorso p1
	HELP TESSERE
	mostra reverse p1 e normale p2
	
	
	
	*/
#define SRCCOPY_D 2424

	for (pl=PLAYER1;pl<=PLAYER2;pl++)
	{
		if (gFaseHelp==HELP_IS_OFF && !flag_mostra_tessere){
			op[PLAYER1]=SRCCOPY;
			op[PLAYER2]=SRCCOPY_D;
		}	
		else if (gFaseHelp==HELP_IS_OFF && flag_mostra_tessere){
			op[PLAYER1]=SRCCOPY;
			op[PLAYER2]=NOTSRCCOPY;
		}	
		else if (gFaseHelp!=HELP_IS_OFF){
			op[PLAYER1]=SRCCOPY_D;
			op[PLAYER2]=SRCCOPY;
		}	
		/*
		else if (FaseHelp==HELP_IS_ON && flag_mostra_tessere){
			op[PLAYER1]=NOTSRCCOPY;
			op[PLAYER2]=SRCCOPY;
		}*/	
		for(n=0;n<8;n++)
		{
			tessera[pl][n].x=(iXTESSERA+pl*DISTANZA_TESSERE)+(n*(iDIMTESSERA-1));
			tessera[pl][n].y=iYTESSERA;
			if(tessera[pl][n].flag==PRESENTE){
				if(op[pl]==SRCCOPY_D)
				{
					opzione=SRCCOPY;
					hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_DORSO));					
				}
				else{
					if(n==gselection)
						opzione=NOTSRCCOPY;
					else
						opzione=op[pl];	
					hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(tessera[pl][n].s.bitmap));
					}
			}
			else	{
				opzione=pl==PLAYER1?SRCCOPY:NOTSRCCOPY;
				hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(IDB_SCARABEO));
			}
			gdi=SelectObject(memdc,hbitmap);				
			
			if (!StretchBlt(hdc, //cefalu
				   tessera[pl][n].x,
				   tessera[pl][n].y, 
				   iDIMTESSERA,iDIMTESSERA, 
				  memdc, 
				   0,0, 
				   DIMTESSERA,DIMTESSERA,
				   opzione)) 
					
				   valret=1;

			
			DeleteObject(hbitmap);

		}//next tessera
	}//next player
	DeleteObject(gdi);
	ReleaseDC(ghWndToolbarDlg,hdc);
	DeleteDC(memdc);
	return valret;
}

void Ruota()//osaka
{
/*

..cane
g.....
a.....
t.....
t.....
o.....

.gatto
......
c.....
a.....
n.....
e.....

si tratta di invertire righe e colonne
*/
int x,y;
struct casaSTR	appo[15][15];
memcpy(&appo,&casa,sizeof(casa));


//controlla che siano tutte permanenti
	for (y=0;y<15;y++)
	{
		for (x=0;x<15;x++)
		{
			if(casa[x][y].flag!=ASSENTE &&
				casa[x][y].flag!=PERMANENTE)
			{
				return;
			}
		}
	}

	for (y=0;y<15;y++)
	{
		for (x=0;x<15;x++)
		{
			memcpy(&casa[y][x],&appo[x][y],sizeof(casaSTR));
		}
	}
	salva(1);
	ripristina(1);
	AggiornaFinestra();
}

void GetRapportoXY(float*rx,float*ry)
{
//DA QUI CEFALU: trasforma coordinate in base alla dimensione della finestra
	RECT r;
	while(!GetWindowRect(ghWndToolbarDlg,&r));
	*ry=(float)r.bottom/556.0F;
	*rx=(float)r.right/668.0F;
	
	char dsr[80];
	sprintf(dsr,"Rapporto finestra:x=%f,y=%f\n",*rx,*ry);
	OutputDebugString(dsr);
}

/*
void faite()
{
	OutputDebugString("FT-");
	int valret=0;
	HANDLE hbitmap;
	HDC hdc,memdc;
	HGDIOBJ gdi;//jakarta
	int x,y;

		//hdc=CreateDC("DISPLAY",NULL,NULL,NULL);
	hdc=GetDC(ghWndToolbarDlg);	
	memdc=CreateCompatibleDC(hdc);

for(y=0;y<15;y++)
	for(x=0;x<15;x++)
	{

		hbitmap=LoadBitmap(ghInst,MAKEINTRESOURCE(casa[y][x].obitmap));
		gdi=SelectObject(memdc,hbitmap);
		if (!StretchBlt(hdc, //cefalu
               casa[y][x].x,
			   casa[y][x].y,
               iDIMTESSERA,iDIMTESSERA, 
              memdc, 
               0,0,
			   DIMTESSERA,DIMTESSERA, 
               SRCCOPY));
		DeleteObject(hbitmap);//parigi jakarta corregge
	}
	DeleteObject(gdi);
	ReleaseDC(ghWndToolbarDlg,hdc);
	DeleteDC(memdc);

}
*/