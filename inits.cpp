#include "windows.h"
#include "scarabeo.h"
#include "resource.h"
extern char gFILE_VOCABOLARIO[32];
extern struct saccoSTR sacco[NUM_TESSERE];
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
extern int Machine_Thinking; //okinawa
extern HANDLE hThreadSC;
int InitStructz()
{
int y,x,cnt,alfa;

	

	//per board e tessere
	iBASEX=BASEX*rapportox;
	iBASEY=BASEY*rapportoy;
	iDIMBOARD=DIMBOARD*rapportoy;
	iDIMTESSERA=DIMTESSERA*rapportoy;
	iXTESSERA=XTESSERA*rapportox;
	iYTESSERA=YTESSERA*rapportoy;
	//cefalu per punti e sacco
	iXMAN1=XMAN1*rapportox;
	iXMAC1=XMAC1*rapportox;
	iXMAS1=XMAS1*rapportox;
	iYPUNTO=YPUNTO*rapportoy;
	iDIMXCIFRA=DIMXCIFRA*rapportoy;
	iDIMYCIFRA=DIMYCIFRA*rapportoy;
	iDISTACCO=DISTACCO*rapportox;
	iYSUNTO=YSUNTO*rapportoy;
//per dialog4 (scelta scarabeo)
	iINTV=INTV*rapportoy;
	iLIMX=LIMX*rapportoy;
	iLIMY=LIMY*rapportoy;
	iMAG1=MAG1*rapportoy;
	iMAG2=MAG2*rapportoy;
//FINE CEFALU
	psacco=0;
	turn=totalturn=0;
	player=PLAYER1;
	gselection=NOT_SELECTED;
	Machine_Thinking=FALSE; //okinawa	
	

	memset(&tessera,0,sizeof(tessera));
	memset(&casa,0,sizeof(casa));
	memset(&iplayer,0,sizeof(iplayer));
	iplayer[PLAYER2].cpu=1;

//inizializza le case
	for (y=0;y<15;y++)
	{
		for (x=0;x<15;x++)
		{
			casa[y][x].vcasa=value[y][x];
			casa[y][x].x=iBASEX+1+(iDIMTESSERA-1)*x;
			casa[y][x].y=iBASEY+1+(iDIMTESSERA-1)*y;

			//casa[y][x].x=31*x;
			//casa[y][x].y=31*y;
			
			switch(value[y][x])
			{
			case 1:
				casa[y][x].obitmap=IDB_1L;
				break;
			case 2:
				casa[y][x].obitmap=IDB_2L;
				break;
			case 3:
				casa[y][x].obitmap=IDB_3L;
				break;
			case 4:
				casa[y][x].obitmap=IDB_2P;
				break;
			case 5:
				casa[y][x].obitmap=IDB_3P;
				break;
			}
			//eccezione:
			if(y==7&&x==7)
				casa[y][x].obitmap=IDB_FIRMA;//IDB_SCARABOK;
		}
	}


	cnt=0;
	alfa=0;

// e le lettere..
	Info_Lettera[alfa].lettera='a';
	Info_Lettera[alfa].bitmap=IDB_A;
	Info_Lettera[alfa++].valore=A;
	Info_Lettera[alfa].lettera='b';
	Info_Lettera[alfa].bitmap=IDB_B;
	Info_Lettera[alfa++].valore=B;
	Info_Lettera[alfa].lettera='c';
	Info_Lettera[alfa].bitmap=IDB_C;
	Info_Lettera[alfa++].valore=C;
	Info_Lettera[alfa].lettera='d';
	Info_Lettera[alfa].bitmap=IDB_D;
	Info_Lettera[alfa++].valore=D;
	Info_Lettera[alfa].lettera='e';
	Info_Lettera[alfa].bitmap=IDB_E;
	Info_Lettera[alfa++].valore=E;
	Info_Lettera[alfa].lettera='f';
	Info_Lettera[alfa].bitmap=IDB_F;
	Info_Lettera[alfa++].valore=F;
	Info_Lettera[alfa].lettera='g';
	Info_Lettera[alfa].bitmap=IDB_G;
	Info_Lettera[alfa++].valore=G;
	Info_Lettera[alfa].lettera='h';
	Info_Lettera[alfa].bitmap=IDB_H;
	Info_Lettera[alfa++].valore=H;
	Info_Lettera[alfa].lettera='i';
	Info_Lettera[alfa].bitmap=IDB_I;
	Info_Lettera[alfa++].valore=I;
	Info_Lettera[alfa].lettera='j';
	Info_Lettera[alfa].bitmap=IDB_J;
	Info_Lettera[alfa++].valore=J;
	Info_Lettera[alfa].lettera='k';
	Info_Lettera[alfa].bitmap=IDB_K;
	Info_Lettera[alfa++].valore=K;
	Info_Lettera[alfa].lettera='l';
	Info_Lettera[alfa].bitmap=IDB_L;
	Info_Lettera[alfa++].valore=L;
	Info_Lettera[alfa].lettera='m';
	Info_Lettera[alfa].bitmap=IDB_M;
	Info_Lettera[alfa++].valore=M;
	Info_Lettera[alfa].lettera='n';
	Info_Lettera[alfa].bitmap=IDB_N;
	Info_Lettera[alfa++].valore=N;
	Info_Lettera[alfa].lettera='o';
	Info_Lettera[alfa].bitmap=IDB_O;
	Info_Lettera[alfa++].valore=O;
	Info_Lettera[alfa].lettera='p';
	Info_Lettera[alfa].bitmap=IDB_P;
	Info_Lettera[alfa++].valore=P;
	Info_Lettera[alfa].lettera='q';
	Info_Lettera[alfa].bitmap=IDB_Q;
	Info_Lettera[alfa++].valore=Q;
	Info_Lettera[alfa].lettera='r';
	Info_Lettera[alfa].bitmap=IDB_R;
	Info_Lettera[alfa++].valore=R;
	Info_Lettera[alfa].lettera='s';
	Info_Lettera[alfa].bitmap=IDB_S;
	Info_Lettera[alfa++].valore=S;
	Info_Lettera[alfa].lettera='t';
	Info_Lettera[alfa].bitmap=IDB_T;
	Info_Lettera[alfa++].valore=T;
	Info_Lettera[alfa].lettera='u';
	Info_Lettera[alfa].bitmap=IDB_U;
	Info_Lettera[alfa++].valore=U;
	Info_Lettera[alfa].lettera='v';
	Info_Lettera[alfa].bitmap=IDB_V;
	Info_Lettera[alfa++].valore=V;
	Info_Lettera[alfa].lettera='w';
	Info_Lettera[alfa].bitmap=IDB_W;
	Info_Lettera[alfa++].valore=W;
	Info_Lettera[alfa].lettera='x';
	Info_Lettera[alfa].bitmap=IDB_X;
	Info_Lettera[alfa++].valore=X;
	Info_Lettera[alfa].lettera='y';
	Info_Lettera[alfa].bitmap=IDB_Y;
	Info_Lettera[alfa++].valore=Y;
	Info_Lettera[alfa].lettera='z';
	Info_Lettera[alfa].bitmap=IDB_Z;
	Info_Lettera[alfa++].valore=Z;
	Info_Lettera[alfa].lettera='@';
	Info_Lettera[alfa].bitmap=IDB_SCARABOK;
	Info_Lettera[alfa++].valore=VAL_SCARA;
	//TESSERE VERSIONE ITALIA

	int ah=NUM_TESSERE;

	
	
	for (y=0;y<Q_SCARABEI;y++)
	{
		sacco[cnt].lettera='@';
		sacco[cnt].bitmap=IDB_SCARABOK;
		sacco[cnt++].valore=VAL_SCARA;
	}

	for (y=0;y<QA;y++){
		sacco[cnt].lettera='a';
		sacco[cnt].bitmap=IDB_A;
		sacco[cnt++].valore=A;
	}
	for (y=0;y<QB;y++){
		sacco[cnt].lettera='b';
		sacco[cnt].bitmap=IDB_B;
		sacco[cnt++].valore=B;
	}
	for (y=0;y<QC;y++){
		sacco[cnt].lettera='c';
		sacco[cnt].bitmap=IDB_C;
		sacco[cnt++].valore=C;
	}
	for (y=0;y<QD;y++){
		sacco[cnt].lettera='d';
		sacco[cnt].bitmap=IDB_D;
		sacco[cnt++].valore=D;
	}
	for (y=0;y<QE;y++){
		sacco[cnt].lettera='e';
		sacco[cnt].bitmap=IDB_E;
		sacco[cnt++].valore=E;
	}
	for (y=0;y<QF;y++){
		sacco[cnt].lettera='f';
		sacco[cnt].bitmap=IDB_F;
		sacco[cnt++].valore=F;
	}
	for (y=0;y<QG;y++){
		sacco[cnt].lettera='g';
		sacco[cnt].bitmap=IDB_G;
		sacco[cnt++].valore=G;
	}
	for (y=0;y<QH;y++){
		sacco[cnt].lettera='h';
		sacco[cnt].bitmap=IDB_H;
		sacco[cnt++].valore=H;
	}
	for (y=0;y<QI;y++){
		sacco[cnt].lettera='i';
		sacco[cnt].bitmap=IDB_I;
		sacco[cnt++].valore=I;
	}
	for (y=0;y<QL;y++){
		sacco[cnt].lettera='l';
		sacco[cnt].bitmap=IDB_L;
		sacco[cnt++].valore=L;
	}
	for (y=0;y<QM;y++){
		sacco[cnt].lettera='m';
		sacco[cnt].bitmap=IDB_M;
		sacco[cnt++].valore=M;
	}
	for (y=0;y<QN;y++){
		sacco[cnt].lettera='n';
		sacco[cnt].bitmap=IDB_N;
		sacco[cnt++].valore=N;
	}
	for (y=0;y<QO;y++){
		sacco[cnt].lettera='o';
		sacco[cnt].bitmap=IDB_O;
		sacco[cnt++].valore=O;
	}
	for (y=0;y<QP;y++){
		sacco[cnt].lettera='p';
		sacco[cnt].bitmap=IDB_P;
		sacco[cnt++].valore=P;
	}
	for (y=0;y<QQ;y++){
		sacco[cnt].lettera='q';
		sacco[cnt].bitmap=IDB_Q;
		sacco[cnt++].valore=Q;
	}
	for (y=0;y<QR;y++){
		sacco[cnt].lettera='r';
		sacco[cnt].bitmap=IDB_R;
		sacco[cnt++].valore=R;
	}
	for (y=0;y<QS;y++){
		sacco[cnt].lettera='s';
		sacco[cnt].bitmap=IDB_S;
		sacco[cnt++].valore=S;
	}
	for (y=0;y<QT;y++){
		sacco[cnt].lettera='t';
		sacco[cnt].bitmap=IDB_T;
		sacco[cnt++].valore=T;
	}
	for (y=0;y<QU;y++){
		sacco[cnt].lettera='u';
		sacco[cnt].bitmap=IDB_U;
		sacco[cnt++].valore=U;
	}
	for (y=0;y<QV;y++){
		sacco[cnt].lettera='v';
		sacco[cnt].bitmap=IDB_V;
		sacco[cnt++].valore=V;
	}
	for (y=0;y<QZ;y++){
		sacco[cnt].lettera='z';
		sacco[cnt].bitmap=IDB_Z;
		sacco[cnt++].valore=Z;
	}
	for (y=0;y<QJ;y++){
		sacco[cnt].lettera='j';
		sacco[cnt].bitmap=IDB_J;
		sacco[cnt++].valore=J;
	}
	for (y=0;y<QK;y++){
		sacco[cnt].lettera='k';
		sacco[cnt].bitmap=IDB_K;
		sacco[cnt++].valore=K;
	}
	for (y=0;y<QW;y++){
		sacco[cnt].lettera='w';
		sacco[cnt].bitmap=IDB_W;
		sacco[cnt++].valore=W;
	}
	for (y=0;y<QX;y++){
		sacco[cnt].lettera='x';
		sacco[cnt].bitmap=IDB_X;
		sacco[cnt++].valore=X;
	}
	for (y=0;y<QY;y++){
		sacco[cnt].lettera='y';
		sacco[cnt].bitmap=IDB_Y;
		sacco[cnt++].valore=Y;
	}
	

	if(cnt!=NUM_TESSERE)
		exit(4876);
	
	
	for (y=0;y<2;y++)
			for (x=0;x<8;x++)
				tessera[y][x].flag=ASSENTE;
	return 0;
}
