#include "windows.h"
#include "scarabeo.h"
#include "resource.h"
#include <stdio.h>
#include <time.h>
#define FIATA20 Sleep(10);//15 fino al 15/2/2009
//#define FIATA50 Sleep(50);//20
//#define MOSTRA_ELIM

extern HANDLE			hDataHeap;
extern HWND			ghWndToolbarDlg;
extern HINSTANCE		ghInst;
extern struct lemmaSTR lemma[NUM_LEMMI];// per il controllo e assegnazione punti
extern struct casaSTR casa[15][15];
extern BYTE			player;
extern struct lemmaSTR zona_appoggio[LZA];
extern int maxlen;
extern char old_parola[];//canicatti
extern int					flag_mostra_idee;
extern BYTE		gFaseHelp;//VENEZIA2
extern struct saccoSTR Info_Lettera[LETTERE_ALFABETO+Q_SCARABEI];
extern struct playerSTR iplayer[2];//bergamo
extern struct tesseraSTR tessera[2][8];
extern void * hBaseHeap;
extern char gFILE_VOCABOLARIO[32];
extern BYTE flag_prima_tessera;
extern BYTE salva_flag_1t;
extern BYTE salva_flag_77;
extern int gMaxPuntiHelp;
extern int iDIMTESSERA;
//extern BYTE flag_abil_Grect;ankara
extern RECT Grect;
extern char gFILE_BILETT[32];//oslo
extern int punticalc;//falluja
extern int Machine_Thinking; //okinawa
extern int eliminate[6];
extern char MemoriaBiletterali[16000];
extern struct gperpend gperp;
//char provincia[NUM_PROVINCIE][3]; //OSLO//[3]={"ag","al","an","ao","ap","aq","ar","at","av","ba","bg","bl","bn","bo","br","bs","bz","ca","cb","ce","ch","cl","cn","co","cr","cs","ct","cz","en","fe","fg","fi","fo","fr","ge","go","gr","im","is","le","li","lt","lu","ma","mc","me","mi","mn","mo","ms","mt","na","no","nu","or","pa","pc","pd","pe","pg","pi","pn","po","pr","ps","pt","pv","pz","ra","rc","re","rg","ri","rm","rn","ro","sa","si","so","sp","sr","ss","sv","ta","te","tn","to","tp","tr","ts","tv","ud","va","vc","ve","vi","vr","vt"};
int oldvalue=0;

//CERCA CON WILDCARDS
int ConvertWildcards(char*chiara,char*standard)
{
/*
	converte le wildcards per la ricerca manuale.
	da uno standard umano alla mia particolare codifica

	CANE  = $CANE
	CANE* = $CANE*
	*CANE = CANE*


	*/
//	int l=strlen(chiara);
	if(*chiara=='*')
	{
		chiara++;
		strcpy(standard,chiara);
	}
	else
	{
		*standard='$';
		strcpy(standard+1,chiara);
	}


	return 0;

}
int FindKeys(char *psk)
{

	/*
	REGOLE:
	$ = INIZIO PAROLA
	? = QUALUNQUE CARATTERE
	* = N CARATTERI
	<a-z> QUESTO CARATTERE



	*/
	char sk[32]="";
	char parola[32];
	int ndx=0;
	char *p,*savep;
	int n,g;
	int ncp=0;
	int conteggio=0;
	//SYSTEMTIME SystemTimeStart,SystemTimeStop;
	strcpy(sk,"");//prova
	strcat(sk,psk);

	p=savep=(char*)hBaseHeap;

	//GetSystemTime(&SystemTimeStart);
	while(1)
	{
		if(*p<=0)
		{
			SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_KEYEND,(LPARAM)NULL);
			return 0;
		}
		if(!ndx)
		{
			ncp=0;
			memset(parola,0,sizeof(parola));
		}
		switch(sk[ndx])
		{
		case 0:
			//la chiave di ricerca è terminata:
			//se il dizionario punta alla parola nuova
			//o ad una vocale tronca, la parola è trovata
			//if(sk[ndx-1]=='?' && (*p==VOC4));
			if(*p!=0x0d && *p!=VOC4)
			{
			ndx=0;
			break;
			}
			//parola trovata
			parola[ncp]=0;
			conteggio+=strlen(parola)+8;//todi: considerare 2 per CRLF piu espansione da 3 a a-e-i-o
			if(conteggio<DIM_BUFFER_RICERCA)
			//MessageBox(GetActiveWindow(),parola,NULL,NULL);
				SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_KEYFOUND,(LPARAM)parola);
			else//per non sforare il buffer di visualizzazione.. TODI
			{
				SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)WM_KEYEND,(LPARAM)conteggio);//todi
				return 0;
			}

			ndx=0;
			break;

		case '$':

			while(*p!=0x0a)
				p++;
			ndx++;
			p++;
			break;
		case '?':
			if(*p!=0x0d && *p!=0x0a)
			{
				parola[ncp++]=*p;
				p++;
				ndx++;
			}
			else
			{
				p++;
				ndx=0;
			}
				break;
		case '*':
		if(*p!=0x0d && *p!=0x0a)
			{
				parola[ncp++]=*p;
				p++;
			}
			else
				ndx++;
			break;
		default:
			if( *p==sk[ndx]||
				(*p==VOC0 && (sk[ndx]=='o'||sk[ndx]=='i'))||
				(*p==VOC1 && (sk[ndx]=='a'||sk[ndx]=='e'))||
				(*p==VOC2 && (sk[ndx]=='e'||sk[ndx]=='i'))||
				(*p==VOC3 && (sk[ndx]=='o'||sk[ndx]=='i'||sk[ndx]=='a'||sk[ndx]=='e'))||
				(*p==VOC4 && (sk[ndx]=='o'))||//||sk[ndx]=='i'))||BERNA comm
				(*p==VOC5 && (sk[ndx]=='a'||sk[ndx]=='e'||sk[ndx]=='i'))||
				(*p==VOC6 && (sk[ndx]=='a'||sk[ndx]=='i'||sk[ndx]=='o'))
				//da qui venezia
				||(*p==VOC7 && (sk[ndx]=='e'||sk[ndx]=='i'||sk[ndx]=='o'))
				||(*p==VOC8 && (sk[ndx]=='a'||sk[ndx]=='i'))
				||(*p==VOC9 && (sk[ndx]=='a'||sk[ndx]=='o'))
				||(*p==VOC10 && (sk[ndx]=='e'||sk[ndx]=='o'))
				||(*p==VOC11 && (sk[ndx]=='a'||sk[ndx]=='e'||sk[ndx]=='o'))
				)
			{
				if(!ncp)
				{
					for(n=1;n<20;n++)
						if(p-n<=savep||*(p-n)==0x0a)
							break;
						p-=n-1;
					for(g=0;g<n-1;g++)
					{
						{
							parola[ncp++]=*(p++);
						}
					}
				}
				parola[ncp++]=*p;
				p++;
				ndx++;
			}
			else
			{
				p++;
				ndx=0;
			}
		}

	}
return 0;
}
#ifndef TUNISI
//MEMORIZZA IL VOCABOLARIO ITALIANO
BOOL HeapInit()
{
//	PROCESS_HEAP_ENTRY info;
	        SYSTEM_INFO sysInfo;
	unsigned long	Vsize;
 HANDLE hVocabolario;
 DWORD Bread;
 int mul;
 //void* base;
//OVERLAPPED Overlap;
//char buffer[33];

DWORD dwsize;
hVocabolario=CreateFile(
		   gFILE_VOCABOLARIO,
		   GENERIC_READ,
		   FILE_SHARE_READ,
		   NULL,
		   OPEN_EXISTING,
		   NULL,
			NULL	);

	if(hVocabolario==INVALID_HANDLE_VALUE)
	{
		ErrorReporter("Manca Vocabolario");
		return FALSE;
	}

	if(dwsize=GetFileSize (hVocabolario,&Vsize)==INVALID_FILE_SIZE)
		ErrorReporter("size");

	Vsize=0x6FFFF;
    GetSystemInfo(&sysInfo);
	mul=Vsize/sysInfo.dwPageSize;
	Vsize=sysInfo.dwPageSize * mul;
        hDataHeap = HeapCreate(HEAP_NO_SERIALIZE,Vsize,Vsize);//647100 MAX DIM VOVABOLARIO
        if (hDataHeap == NULL) {
            ErrorReporter("HeapCreate (Data Heap)");
			return FALSE;
		}
	Vsize-=sysInfo.dwPageSize;
	if(HeapValidate(hDataHeap,HEAP_NO_SERIALIZE,NULL)==FALSE)
		ErrorReporter("HeapValidate");

	hBaseHeap=HeapAlloc(hDataHeap,HEAP_GENERATE_EXCEPTIONS|HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,Vsize);

	if(ReadFile(hVocabolario,hBaseHeap,Vsize,&Bread,NULL)==FALSE)
			ErrorReporter("REadFile");

	if(HeapValidate(hDataHeap,HEAP_NO_SERIALIZE,NULL)==FALSE)
		ErrorReporter("HeapValidate");

	if(Bread>Vsize)
		ErrorReporter("HeapCreate (VOC troppo lungo)");

	CloseHandle(hVocabolario);
//	HeapWalk(hDataHeap,&info);
//	HeapCompact(hDataHeap,HEAP_NO_SERIALIZE);
	//adesso ho tutto il vocabolario in memoria..... !!!!!!

#ifndef TROMSOE
	MemGrBil();//oslo
#endif

	return TRUE;
}
#endif
int Check_in_Diz(struct lemmaSTR *lem,int nlem)
{
	int n;
	char buf[32];
	//char zona_appoggio[320];
	int nparole=0;
	int tot=0;

	for(n=0;n<nlem;n++)
		if(lem->value)
		{
			sprintf(buf,"$%s",lem->parola);
			//tot+=nparole=Find_in_Diz(buf,0);malindi corregge baco che cancelava la prima parola
			nparole=Find_in_Diz(buf,LZA-1000);//malindi
			nparole-=(LZA-1000);//malindi
			tot+=nparole;
			lem->dizionario=nparole?IN_DIR:NOT_IN_DIR;
			lem++;
			//break;
		}
		return tot;
}

int Controlla_Inserimento(struct lemmaSTR *appo)
{
	char avviso[80];
	int ck;
					if(player==PLAYER1)
					{
						if(casa[7][7].flag==ASSENTE)
							return FALSE;
						ck=Check_in_Diz(appo,1);
						if(!ck)
						{
							int u,uu;//IDCANCEL;nassirya
							sprintf(avviso,"La parola %c%s non è contemplata nel dizionario:\r\nRitirarla..",toupper(appo->parola[0]),appo->parola+1);
							if(u=MessageBox(ghWndToolbarDlg,avviso,"Nuovo lemma",MB_ICONQUESTION|MB_YESNOCANCEL)==IDNO)//YES)
							{
								if(uu=MessageBox(ghWndToolbarDlg,
									"Desidera aggiungere la parola al dizionario?",
									"Nuovo lemma",
									MB_ICONQUESTION|MB_YESNO)
									==IDYES)
										int k=DialogBoxParam(ghInst,MAKEINTRESOURCE(IDD_DIALOG5),ghWndToolbarDlg,(DLGPROC) MoDizProc,(LPARAM)appo->parola);
								else
									return TRUE;//nassirya
							//	AggiungiAlDizionario(appo->parola);//anti venezia
							}
							else
								return FALSE;//nassirya
						}
					}

return TRUE;
}

int Aggiorna_Flag(BYTE flag,struct lemmaSTR *lem)
{
/*
avendo le info, aggiorna lo schema con la parola e il flag indicato
*/
	int len;
	int cnt;
	int g,x,y,h;
char p[32];

			strcpy(p,lem->parola);
			x=lem->index.x;
			y=lem->index.y;

cnt=0;
			len=strlen(p);
		//	while(islower(p[cnt]))
		//		cnt++;

			if(lem->hv==ORIZZONTALE)
			{

				for(g=x,h=0;g<x+len-cnt;g++,h++)
				{

					if(casa[y][g].flag==PERMANENTE)
					{
						//conteggia il punteggio

					}
					else if(casa[y][g].flag==LIBERA)
					{//se la mia lettera è maiuscola, vuol dire verticale
						casa[y][g].flag=TEMPORANEA_PL2;
						casa[y][g].s.lettera=p[cnt+h];
						casa[y][g].s.bitmap=Info_Lettera[p[cnt+h]-'a'].bitmap;
						casa[y][g].s.valore=Info_Lettera[p[cnt+h]-'a'].valore;
					}
				}

				for(g=x,h=0;g>x-cnt-1;g--,h++)
				{
					if(casa[y][g].flag==PERMANENTE)
					{
					}
					else if(casa[y][g].flag==LIBERA)
					{
						casa[y][g].s.lettera=p[cnt-h];
						casa[y][g].flag=TEMPORANEA_PL2;
						casa[y][g].s.bitmap=Info_Lettera[p[cnt-h]-'a'].bitmap;
						casa[y][g].s.valore=Info_Lettera[p[cnt-h]-'a'].valore;
					}
				}
//				Annulla_flag_temporanei_T(CONSIDERATA,ASSENTE);
//				Annulla_flag_temporanei(PERMANENTE);
				return 0;
			}//orizzontale
			//goto novert;
//vert:;
			else if(lem->hv==VERTICALE)
			{
//				Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);
//				Annulla_flag_temporanei(ASSENTE);

				for(g=y,h=0;g<y+len-cnt;g++,h++)
				{

					if(casa[g][x].flag==PERMANENTE)
					{
					}
					else if(casa[g][x].flag==LIBERA)
					{

						casa[g][x].flag=TEMPORANEA_PL2;
						casa[g][x].s.lettera=p[cnt+h];
						casa[g][x].s.bitmap=Info_Lettera[p[cnt+h]-'a'].bitmap;
						casa[g][x].s.valore=Info_Lettera[p[cnt+h]-'a'].valore;
					}
				}

				for(g=y,h=0;g>y-cnt-1;g--,h++)
				{
					if(casa[g][x].flag==PERMANENTE)
					{

					}
					else if(casa[g][y].flag==LIBERA)
					{
						casa[g][x].s.lettera=p[cnt-h];
						casa[g][x].flag=TEMPORANEA_PL2;
						casa[g][x].s.bitmap=Info_Lettera[p[cnt-h]-'a'].bitmap;
						casa[g][x].s.valore=Info_Lettera[p[cnt-h]-'a'].valore;
					}
				}
//				Annulla_flag_temporanei_T(CONSIDERATA,ASSENTE);
//				Annulla_flag_temporanei(PERMANENTE);
				return 0;
			}//verticale
				return 1;


}

int MettiUnaLetteraACaso()
{
	return(0);//parigi
}

int AggiungiAlDizionario(char *lemma)
{
 HANDLE hVocabolario;
// DWORD Bread;
//OVERLAPPED Overlap;
char buffer[33];
#ifdef KRYPTER
maincrypt(DEKRYPT);
#endif
DWORD dwsize;
hVocabolario=CreateFile(
		   gFILE_VOCABOLARIO,
		   GENERIC_WRITE,
		   FILE_SHARE_READ,
		   NULL,
		   OPEN_EXISTING,
		   NULL,
			NULL	);

	if(hVocabolario==INVALID_HANDLE_VALUE)
	{
		ErrorReporter("Manca Vocabolario");
		return FALSE;
	}
	SetFilePointer(hVocabolario,0,0,FILE_END);
	sprintf(buffer,"%s\r\n",lemma);
	WriteFile(hVocabolario,buffer,strlen(buffer),&dwsize,NULL);
	CloseHandle(hVocabolario);
#ifdef KRYPTER
	maincrypt(KRYPT);
	DeleteFile(gFILE_VOCABOLARIO);
#endif
	return TRUE;

}



int Find_in_Diz(char *chiavericerca,int IndiceUfficiale)
{

/*
	AGGIUNGE PAROLE NELLO HEAP
	TORNA L'INDICE UFFICIALE ALLA PROSSIMA PAROLA LIBERA NELLO HEAP

	REGOLE:
	$ = INIZIO parolatrovata
	? = QUALUNQUE CARATTERE
	* = N CARATTERI
	<a-z> QUESTO CARATTERE

	*/

	char *p,*savep;

	p=savep=(char*)hBaseHeap;


	int idx_chiave=0;

	char parolatrovata[32];
	int idx_lettera=0;

	int n,g;

	while(1)
	{
		if(*p<=0)
			break;

		if(!idx_chiave)
		{
			idx_lettera=0;
			memset(parolatrovata,0,sizeof(parolatrovata));
		}

		switch(chiavericerca[idx_chiave])
		{
		case 0:
			if(*p!=0x0d &&*p!=VOC4)
			{
				idx_chiave=0;
				break;
			}
			parolatrovata[idx_lettera]=0;
			strcpy(zona_appoggio[IndiceUfficiale].parola,parolatrovata);
			IndiceUfficiale++;
			if(IndiceUfficiale>=LZA)
				return(IndiceUfficiale);
			idx_chiave=0;
		break;
		case '$'://INIZIO parolatrovata
			while(*p!=0x0a)
				p++;
			idx_chiave++;
			p++;
			break;
		case '?'://carattere singolo jolly
			if(*p!=0x0d && *p!=0x0a)
			{
				parolatrovata[idx_lettera++]=*p;
				p++;
				idx_chiave++;
			}
			else
			{
				p++;
				idx_chiave=0;
			}
				break;
		case '*'://carattere multi jolly
			if(*p!=0x0d && *p!=0x0a)
			{
				parolatrovata[idx_lettera++]=*p;
				p++;
			}
			else
				idx_chiave++;
			break;
		default://TUTTE LE LETTERE
			if(
				*p==chiavericerca[idx_chiave]
				||
				(*p==VOC0 && (chiavericerca[idx_chiave]=='o'||chiavericerca[idx_chiave]=='i'))||
				(*p==VOC1 && (chiavericerca[idx_chiave]=='a'||chiavericerca[idx_chiave]=='e'))||
				(*p==VOC2 && (chiavericerca[idx_chiave]=='e'||chiavericerca[idx_chiave]=='i'))||
				(*p==VOC3 && (chiavericerca[idx_chiave]=='o'||chiavericerca[idx_chiave]=='i'||chiavericerca[idx_chiave]=='a'||chiavericerca[idx_chiave]=='e'))||
				(*p==VOC4 && (chiavericerca[idx_chiave]=='o'))||
				(*p==VOC5 && (chiavericerca[idx_chiave]=='a'||chiavericerca[idx_chiave]=='e'||chiavericerca[idx_chiave]=='i'))||
				(*p==VOC6 && (chiavericerca[idx_chiave]=='a'||chiavericerca[idx_chiave]=='i'||chiavericerca[idx_chiave]=='o'))
				||(*p==VOC7 && (chiavericerca[idx_chiave]=='e'||chiavericerca[idx_chiave]=='i'||chiavericerca[idx_chiave]=='o'))
				||(*p==VOC8 && (chiavericerca[idx_chiave]=='a'||chiavericerca[idx_chiave]=='i'))
				||(*p==VOC9 && (chiavericerca[idx_chiave]=='a'||chiavericerca[idx_chiave]=='o'))
				||(*p==VOC10 && (chiavericerca[idx_chiave]=='e'||chiavericerca[idx_chiave]=='o'))
				||(*p==VOC11 && (chiavericerca[idx_chiave]=='a'||chiavericerca[idx_chiave]=='e'||chiavericerca[idx_chiave]=='o'))
				)

			{
				if(!idx_lettera)
				{
					for(n=1;n<20;n++)
					{
						if(p-n<=savep||*(p-n)==0x0a)
							break;
					}
					p-=n-1;

					for(g=0;g<n-1;g++)
						parolatrovata[idx_lettera++]=(*(p++));
				}

				if(*p==chiavericerca[idx_chiave])
						parolatrovata[idx_lettera++]=toupper(*(p++));

				else if(*p==VOC0||*p==VOC1||*p==VOC2||*p==VOC3||*p==VOC4||*p==VOC5||*p==VOC6||*p==VOC7||*p==VOC8||*p==VOC9||*p==VOC10||*p==VOC11)
				{
					parolatrovata[idx_lettera++]=toupper(chiavericerca[idx_chiave]);
					p++;
				}
				else
					parolatrovata[idx_lettera++]=*(p++);

				idx_chiave++;
			}
			else
			{
				p++;
				idx_chiave=0;
			}
		}

	}
return IndiceUfficiale;
}

int Analysis_Engine(char *buf,POINT point,BYTE hv,BYTE nfisse,int *pTotParole)
{
/*
//torna le parole del diz che contengono la parola inserita che
//vale di più  (le lettere devono essere disponibili)
//se ha trovato una valida di 5 lettere non cerca quelle di 4,3,2...

buf:			chiave ricerca
point:			coordinate logiche inizio parola
hv:			orizzontale,verticale
nfisse:			numero di permanenti
*pTotParole: 	parole precedenti

*/

int start=0;
int n,k;

static char buffer[0xFFF]={0};//roma : era FFF

char ugo[80];
int index=0;
int nparole,g;
char avviso[80];

int lettere_disp=0;
int fisse;
int indice_ap;




memset(buffer,0,sizeof(buffer));

nparole=Find_in_Diz(buf,*pTotParole);
if(nparole<*pTotParole)
{
 	OutputDebugString("ahi!!");
}
nparole-=*pTotParole;
if(!nparole)
	return(*pTotParole);

#ifdef MOSTRA_ELIM
sprintf(avviso,"%s = %d parole nuove %d vecchie\n",buf,nparole,*pTotParole);
OutputDebugString(avviso);
#endif

int antibaco=*pTotParole;//ERA QUESTO IL FAMOSO BACO!!! ROMA l'a risolto!!!
static int old=0;

if(!antibaco)
	old=0;


for(n=0;n<nparole;n++)
{
	indice_ap=n+antibaco;//*pTotParole; roma
	Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);
	fisse=0;
	lettere_disp=0;
	zona_appoggio[indice_ap].len=strlen(zona_appoggio[indice_ap].parola);
	if(zona_appoggio[indice_ap].len<maxlen)//(maxlen<7?maxlen:maxlen-1))
	{
		#ifdef MOSTRA_ELIM
		sprintf(avviso,"E1: la parola con indice %d non esiste\n",indice_ap);
		OutputDebugString(avviso);
		#endif
		memset(&zona_appoggio[indice_ap],0,sizeof(lemmaSTR));//NON PUò cancellare, sennò resta a puntare alla 0!!!!
		zona_appoggio[indice_ap].hv=0xFF;
		eliminate[0]++;
		continue;
	}
	for(g=0;g<zona_appoggio[indice_ap].len;g++)
	{
		if(k=CheckDisp(zona_appoggio[indice_ap].parola[g]))
		{
			if(k==0xFF)
			{
				zona_appoggio[indice_ap].parola[g]=0;
				zona_appoggio[indice_ap].len--;
			}
			else if(k>3)
			{
				zona_appoggio[indice_ap].parola[g]=k;
				lettere_disp++;
			}
			else
			{
				if(k==3)
					zona_appoggio[indice_ap].qsc++;
				lettere_disp++;
			}
		}
		else
		{
			#ifdef MOSTRA_ELIM //lettera non disponibile!
			sprintf(avviso,"E2 (n/disp): %d:%s\n",indice_ap,zona_appoggio[indice_ap].parola);
			OutputDebugString(avviso);
			#endif

			memset(&zona_appoggio[indice_ap],0,sizeof(lemmaSTR));//NON PUò cancellare, sennò resta a puntare alla 0!!!!
			zona_appoggio[indice_ap].hv=0xFF;
			eliminate[1]++;

			goto nextbreak;//prossima parola..

		}
	}
	if
	(
		(
		strlen(zona_appoggio[indice_ap].parola)==lettere_disp
		)
		&& lettere_disp
	)
	{

		if(lettere_disp>nfisse)
		{
				zona_appoggio[indice_ap].len=strlen(zona_appoggio[indice_ap].parola);
				zona_appoggio[indice_ap].hv=hv;
				zona_appoggio[indice_ap].index.x=point.x;
				zona_appoggio[indice_ap].index.y=point.y;

				if(zona_appoggio[indice_ap].len<maxlen)
				{
					#ifdef MOSTRA_ELIM
					sprintf(avviso,"E3 (lenght): %d:%s\n",indice_ap,zona_appoggio[indice_ap].parola);
					OutputDebugString(avviso);
					#endif
					memset(&zona_appoggio[indice_ap],0,sizeof(lemmaSTR));//NON PUò cancellare, sennò resta a puntare alla 0!!!!
					zona_appoggio[indice_ap].hv=0xFF;
					eliminate[2]++;
					continue;
				}


				//qui imposta come temporanee pl2 le case con flag ASSENTE
				
				Aggiorna_Flag(TEMPORANEA_PL2,&zona_appoggio[indice_ap]);//scrive il flag
				if(zona_appoggio[indice_ap].value=ControLL(hv,zona_appoggio[indice_ap].index.y,zona_appoggio[indice_ap].index.x))
				{
					

					
					if(flag_mostra_idee)
						Sleep(zona_appoggio[indice_ap].len*50);

					memcpy(&zona_appoggio[*pTotParole],&zona_appoggio[indice_ap],sizeof(zona_appoggio[indice_ap]));

					if(zona_appoggio[indice_ap].len>maxlen)
						maxlen=zona_appoggio[indice_ap].len;

					sprintf(avviso,"T%04d:%c%s(%d)=%d\n",
						*pTotParole,
						zona_appoggio[*pTotParole].qsc?'*':' ',
						zona_appoggio[*pTotParole].parola,
						zona_appoggio[*pTotParole].len,
						zona_appoggio[*pTotParole].value);
					OutputDebugString(avviso);

					if(nfisse+1==zona_appoggio[*pTotParole].len)
					{
						//OutputDebugString("Skip controllo pendicolare\n");
						MemPerpendicolare(*pTotParole);
						//memorizza in un array gli incroci dove guardare
					}

					(*pTotParole)++;

					if(flag_mostra_idee)
					{

						if(gFaseHelp==HELP_IS_ON)
						{//
							if(gMaxPuntiHelp<zona_appoggio[indice_ap].value)
								gMaxPuntiHelp=zona_appoggio[indice_ap].value;
						}
						else
							gMaxPuntiHelp=0;

						if(strlen(buffer)<(sizeof(buffer)-32))
						{


							sprintf(ugo,"%02d %s%c [%c%X%X]\r\n",
								zona_appoggio[indice_ap].value,
								zona_appoggio[indice_ap].parola,
								zona_appoggio[indice_ap].qsc?'*':' ',
								zona_appoggio[indice_ap].hv==ORIZZONTALE?'H':'V',
								zona_appoggio[indice_ap].index.y+1,
								zona_appoggio[indice_ap].index.x+1
								);
							strtok(ugo,"\r\n");
							char *t=ugo;
							while(*t)
							{
								*t=toupper(*t);
								t++;
							}
							int erro=SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_ADDSTRING,0,(LPARAM)ugo);
							erro=SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_GETCOUNT,0,0);
							erro=SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_SETCURSEL,(WPARAM)(erro-1),0);

						}

						else
							OutputDebugString("Limite buffer raggiunto\n");





						if(flag_mostra_idee)//canicatti
						{
							//#M1
							sprintf(avviso,"%s??",zona_appoggio[indice_ap].parola);
							if(strcmp(avviso,old_parola))
							{

								//SE + CORTA, PARLA (PER NUOVO TURNO)
								if( strlen(old_parola)>strlen(avviso))
								{
									old_parola[0]=0;
									oldvalue=0;
								}
								//PARLA SE LA PAROLA E' + LUNGA DELL'ULTIMA
								if(
									strlen(avviso)>strlen(old_parola)
									||
									zona_appoggio[indice_ap].value>oldvalue
									)
								{
									strcpy(old_parola,avviso);
									oldvalue=zona_appoggio[indice_ap].value;
									AggiornaFinestra();//bergamo mostra la parola in reverse
									ParlaS(avviso);//canicatti
									//qui si manda alla combo
									SetDlgItemText(ghWndToolbarDlg,IDC_COMBO_SEARCH,zona_appoggio[indice_ap].parola);//glasgow3
									Machine_Thinking=FALSE;
									SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_BUTTON1,0L);//glasgow3
									Sleep(2000);
									Machine_Thinking=TRUE;

								}
							}
						}
						Sleep(zona_appoggio[indice_ap].len*50);//ankara2
					}

				}
				else
				{
#ifdef MOSTRA_ELIM
					sprintf(avviso,"E4(lati): %d:%s\n",indice_ap,zona_appoggio[indice_ap].parola);
					OutputDebugString(avviso);
#endif

					memset(&zona_appoggio[indice_ap],0,sizeof(lemmaSTR));
					eliminate[3]++;
					zona_appoggio[indice_ap].hv=0xFF;
				}
				Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);//spostato qui da su
				Annulla_flag_temporanei(LIBERA);
			}
			else
			{

#ifdef MOSTRA_ELIM
				sprintf(avviso,"E5 (fisse): %d:%s\n",indice_ap,zona_appoggio[indice_ap].parola);
				OutputDebugString(avviso);
#endif

				memset(&zona_appoggio[indice_ap],0,sizeof(lemmaSTR));
				zona_appoggio[indice_ap].hv=0xFF;
				eliminate[4]++;
			}
		}
		else
		{
#ifdef MOSTRA_ELIM
			sprintf(avviso,"E6: %d:%s\n",indice_ap,zona_appoggio[indice_ap].parola);
			OutputDebugString(avviso);
#endif
			memset(&zona_appoggio[indice_ap],0,sizeof(lemmaSTR));
			zona_appoggio[indice_ap].hv=0xFF;
			eliminate[5]++;
		}

nextbreak:;//prossima parola..

}//next n

	//if(*pTotParole>old)
	if(TRUE)
	{
		old=*pTotParole;
		sprintf(avviso,"%d / %d",*pTotParole,
				eliminate[0]+
				eliminate[1]+
				eliminate[2]+
				eliminate[3]+
				eliminate[4]+
				eliminate[5]
				);
	//	SetDlgItemText(ghWndToolbarDlg,IDC_EDIT1,avviso);
		SetWindowText(ghWndToolbarDlg,avviso);

		//FIATA20
	}


#ifdef MOSTRA_ELIM

	sprintf(avviso,
	"(TOT%d) %d trovate\n"\
	"E1: %d parola inesistente\n"\
	"E2: %d lettera non disp\n"\
	"E3: %d lunghezza eccessiva\n"\
	"E4: %d lati\n"\
	"E5: %d fisse\n"\
	"E6: %d altro\n"
	
	,nparole,*pTotParole,
	eliminate[0],
	eliminate[1],
	eliminate[2],
	eliminate[3],
	eliminate[4],
	eliminate[5]

	);
	OutputDebugString(avviso);
#endif


	return *pTotParole;
}

int SuperEngine(int dummy)
{

//char buffer[0xFFF];
	//CON LEN = 1 CI SONO POTENZIALI DEADLOCK!!
//intanto, se min_len==1, non deve considerare le chiavi con più di un 'flag'
DWORD dwTick;
DWORD dwTack;

char memo[8]={0,0,0,0,0,0,0,0};

int totpar=0;
int min_len=1;
int cae=0;
maxlen=0; //è una globale che contiene la parola più lunga trovata e verificata
int indice_da_deporre=0;
BOOL flag1t=FALSE;
//	char key[16],key2[32];
//	int x,y,flag,z,target,itarget;
	//tutte le orizzontali
//char avviso[80];
	POINT point;

if(!casa[7][7].vcasa)
	return FALSE;



nexttry:;
	if(casa[7][7].flag==ASSENTE)//caso in cui il cpu comincia..
	{
		flag1t=TRUE;		
		flag_prima_tessera=TRUE;		
		
		
#if 0		
		
		for(indice_da_deporre=0;indice_da_deporre<7;indice_da_deporre++)
		{
			if(
				tessera[PLAYER2][indice_da_deporre].s.lettera=='a'||
				tessera[PLAYER2][indice_da_deporre].s.lettera=='e'||
				tessera[PLAYER2][indice_da_deporre].s.lettera=='i'||
				tessera[PLAYER2][indice_da_deporre].s.lettera=='o'||
				tessera[PLAYER2][indice_da_deporre].s.lettera=='u'
				)
				break;
			
		}
		
		if(indice_da_deporre>7)
			indice_da_deporre=0;//oppure la prima
#endif
	
		point.x=point.y=7;

		if(gFaseHelp==HELP_IS_ON)//ZARA
		{
			//devo salvare indice tessera
			flag_prima_tessera=indice_da_deporre+1;
			salva_flag_1t=tessera[PLAYER2][indice_da_deporre].flag;
			salva_flag_77=casa[7][7].flag;


		}
		


		DeponiPrimaLettera(PLAYER2,point,indice_da_deporre);
		//DeponiLettera(PLAYER2,point,indice_da_deporre);
		
		
		
		//ZARA QUI è IL PROBLEM: SE SI PONE CASA PERMANENTE
		//ALLA FINE DELL'HELP NON RIMUOVE LA TESSERINA..
		//MA SE SI PONE TEMPORANEA, NON FUNZIONA LA RICERCA...
		casa[7][7].flag=PERMANENTE;
		casa[7][7].flag_perp=2;//per invisibile
		tessera[PLAYER2][indice_da_deporre].flag=ASSENTE;
		//ALLORA IO QUANDO HELP_IS_OFF RIPRISTINO LO STATO ANTERIORE!!
	}



	SetWindowText(ghWndToolbarDlg,"Aspetta! Ricerca in corso!");
//		AggiornaFinestra();
//				SendDlgItemMessage(ghWndToolbarDlg,IDC_LIST,LB_RESETCONTENT,0,0);
dwTick=GetTickCount();
//AggiornaFinestra();//berilinoest

	//maxlen=0; //è una globale che contiene la parola più lunga trovata e verificata SPOSTO
	//ad uso di analysys_engine

	if(min_len<1)
		return 0;

	POINT p;

	p.x=p.y=0;


	srand((unsigned)time(NULL));
	int direzioneRandom=rand()%2;


	if(flag1t)
	{
	//	flag_prima_tessera=TRUE;
		Orizzontali(min_len,&totpar,p);
	}
	else
	{
		if(direzioneRandom)
		{
			Verticali(min_len,&totpar,p);
			Orizzontali(min_len,&totpar,p);
		}
		else
		{
			Orizzontali(min_len,&totpar,p);
			Verticali(min_len,&totpar,p);
		}
	}


char msg[255];

	dwTack=GetTickCount();
/*
  sprintf(msg,"Tempo %02d''%02d'''\r\nParole %d\r\n",

		((dwTack-dwTick)/1000),
		(((dwTack-dwTick))%1000)/10,
		totpar//,
		//cae

		);
*/
	  sprintf(msg,"Tempo %02d''%02d'''\r\n",

		((dwTack-dwTick)/1000),
		(((dwTack-dwTick))%1000)/10);


  char appo[1260];	
  sprintf(appo,
	"%d parole trovate\n"\
	"E1: %d parola inesistente\n"\
	"E2: %d lettera non disp\n"\
	"E3: %d lunghezza eccessiva\n"\
	"E4: %d lati\n"\
	"E5: %d fisse\n"\
	"E6: %d altro\n"
	
	,totpar,
	eliminate[0],
	eliminate[1],
	eliminate[2],
	eliminate[3],
	eliminate[4],
	eliminate[5]

	);
	OutputDebugString(appo);

	memset(&eliminate,0,sizeof(eliminate));



			if(gMaxPuntiHelp>punticalc)
			{
				char a[200];
				sprintf(a,
					"\r\nHO INDIVIDUATO UNA PAROLA DA %d PUNTI"\
					"\r\nIL TUO MIGLIOR CALCOLO E': %d"
					,gMaxPuntiHelp,punticalc);//verona
				//"\r\nTu da %d.\r\nSei fai un punteggio compreso fra %d e %d il tuo punteggio sarà dimezzato",gMaxPuntiHelp,punticalc,punticalc+1,gMaxPuntiHelp);//verona
				strcat(msg,a);
			}	
			else if(gMaxPuntiHelp && gMaxPuntiHelp==punticalc)
			{
				char a[200];
				sprintf(a,"\r\nSiamo d'accordo sulla tua parola: %d punti",gMaxPuntiHelp);//verona falluja
				strcat(msg,a);
			}
			else if(gMaxPuntiHelp)
			{
				char a[200];
				sprintf(a,"\r\nLa parola da te trovata e' meglio della mia (%d punti contro %d)\r\nBravo! L'hai anche aggiunta al dizionario ?-)",punticalc,gMaxPuntiHelp);//verona falluja
				strcat(msg,a);
			}

			
//			if(!flag1t)
//				AggiungiMessaggio(ghWndToolbarDlg,msg);
//			AggiornaFinestra();//NON CI VUOLE SENZA MOSTRA IDEE O FORSE MAI 19/2/2012


			if(flag1t)
			{

				memo[indice_da_deporre]=tessera[PLAYER2][indice_da_deporre].s.lettera;



				casa[7][7].flag=ASSENTE;
				casa[7][7].flag_perp=0;
				tessera[PLAYER2][indice_da_deporre].flag=PRESENTE;
				Annulla_flag_temporanei(ASSENTE);
				Annulla_flag_temporanei_T(ASSENTE,PRESENTE);

qui:;
				indice_da_deporre++;
				if(indice_da_deporre>7)
					return totpar;
				int m;
				for(m=0;m<indice_da_deporre;m++)
				{
					if(memo[m]==tessera[PLAYER2][indice_da_deporre].s.lettera)
					{
				
						break;
					}
				}
			
				if(m>=indice_da_deporre)
					goto nexttry;
				else
					goto qui;

			}


	if(gperp.count)
		DoPerp(&totpar);
AggiungiMessaggio(ghWndToolbarDlg,msg);

return totpar;
}


BOOL EseguiSostituzione(char *por,char *pnu)
{
	int inizio_parola=0;
	int fine_parola=0;
	char buffer[36];
//	char resto[36];
//  SYSTEM_INFO sysInfo;
	unsigned long	Vsize;
 HANDLE hVocabolario,hNuovo;
// DWORD Bread;
// int mul;

DWORD dwsize;
hVocabolario=CreateFile(
		   gFILE_VOCABOLARIO,
		   GENERIC_READ|GENERIC_WRITE,
		   FILE_SHARE_READ,
		   NULL,
		   OPEN_EXISTING,
		   NULL,
			NULL	);

	if(hVocabolario==INVALID_HANDLE_VALUE)
	{
		ErrorReporter("Manca Vocabolario");
		return FALSE;
	}

	if(dwsize=GetFileSize (hVocabolario,&Vsize)==INVALID_FILE_SIZE)
		ErrorReporter("size");



hNuovo=CreateFile(
		   "temp.voc",
		   GENERIC_WRITE,
		   FILE_SHARE_READ,
		   NULL,
		   CREATE_ALWAYS,
		   NULL,
			NULL	);

	if(hNuovo==INVALID_HANDLE_VALUE)
	{
		ErrorReporter("Errore proc437");
		CloseHandle(hNuovo);
		return FALSE;
	}



	DWORD Fpoint=SetFilePointer(hVocabolario,0,0,FILE_BEGIN);

	memset(buffer,0,sizeof(buffer));
	int m;
	for(m=0;m<strlen(por);m++)
	{
		*(por+m)=tolower(*(por+m));
	}

	char *z;
/*
venezia: gruppi:
0:	i o
1	a e
2	e i
mancan	(a i),(a o),(e o)
3   a e i o
4   o singola
5   AEI
6	AIO
manca EIO

*/
	if(z=strstr((char*)por,"a-e-i-o")){*z=VOC3;*(z+1)='\0';}
	else if(z=strstr((char*)por,"e-a-i-o")){*z=VOC3;*(z+1)='\0';}
	else if(z=strstr((char*)por,"i-a-e-o")){*z=VOC3;*(z+1)='\0';}
	else if(z=strstr((char*)por,"o-a-e-i")){*z=VOC3;*(z+1)='\0';}
	else if(z=strstr((char*)por,"a-e-i")){*z=VOC5;*(z+1)='\0';}
	else if(z=strstr((char*)por,"e-a-i")){*z=VOC5;*(z+1)='\0';}
	else if(z=strstr((char*)por,"i-a-e")){*z=VOC5;*(z+1)='\0';}
	else if(z=strstr((char*)por,"a-i-o")){*z=VOC6;*(z+1)='\0';}
	else if(z=strstr((char*)por,"i-a-o")){*z=VOC6;*(z+1)='\0';}
	else if(z=strstr((char*)por,"o-a-i")){*z=VOC6;*(z+1)='\0';}
	else if(z=strstr((char*)por,"e-i-o")){*z=VOC7;*(z+1)='\0';}
	else if(z=strstr((char*)por,"i-e-o")){*z=VOC7;*(z+1)='\0';}
	else if(z=strstr((char*)por,"o-e-i")){*z=VOC7;*(z+1)='\0';}
	//questa mancava!VOC11
	else if(z=strstr((char*)por,"a-e-o")){*z=VOC11;*(z+1)='\0';}
	else if(z=strstr((char*)por,"e-a-o")){*z=VOC11;*(z+1)='\0';}
	else if(z=strstr((char*)por,"o-a-e")){*z=VOC11;*(z+1)='\0';}

	else if(z=strstr((char*)por,"a-e")){*z=VOC1;*(z+1)='\0';}
	else if(z=strstr((char*)por,"e-a")){*z=VOC1;*(z+1)='\0';}
//	else if(z=strstr((char*)por,"i-o")){*z=VOC0;*(z+1)='\0';}
	//crea errore con VOC4
	else if(z=strstr((char*)por,"o-i")){*z=VOC0;*(z+1)='\0';}
	else if(z=strstr((char*)por,"e-i")){*z=VOC2;*(z+1)='\0';}
	else if(z=strstr((char*)por,"i-e")){*z=VOC2;*(z+1)='\0';}
	else if(z=strstr((char*)por,"a-i")){*z=VOC8;*(z+1)='\0';}
	else if(z=strstr((char*)por,"i-a")){*z=VOC8;*(z+1)='\0';}
	else if(z=strstr((char*)por,"a-o")){*z=VOC9;*(z+1)='\0';}
	else if(z=strstr((char*)por,"o-a")){*z=VOC9;*(z+1)='\0';}
	else if(z=strstr((char*)por,"e-o")){*z=VOC10;*(z+1)='\0';}
	else if(z=strstr((char*)por,"o-e")){*z=VOC10;*(z+1)='\0';}
	else if(z=strstr((char*)por,"-o")){*z=VOC4;*(z+1)='\0';}
	for(m=0;m<strlen(por);m++)
	{
		char c=*(por+m);
		if(!isalnum(c)&&c!=VOC10&&c!=VOC11)
		{
			CloseHandle(hVocabolario);
			CloseHandle(hNuovo);
			MessageBox(GetActiveWindow(),"Errore codifica nel dizionario","Ohi",MB_ICONINFORMATION);
			return FALSE;
		}
	}





	for(m=0;m<strlen(pnu);m++)
	{
		*(pnu+m)=tolower(*(pnu+m));
	}
	if(z=strstr((char*)pnu,"a-e-i-o")){*z=VOC3;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"e-a-i-o")){*z=VOC3;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"i-a-e-o")){*z=VOC3;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"o-a-e-i")){*z=VOC3;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"a-e-i")){*z=VOC5;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"e-a-i")){*z=VOC5;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"i-a-e")){*z=VOC5;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"a-i-o")){*z=VOC6;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"i-a-o")){*z=VOC6;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"o-a-i")){*z=VOC6;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"e-i-o")){*z=VOC7;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"i-e-o")){*z=VOC7;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"o-e-i")){*z=VOC7;*(z+1)='\0';}
	//questa mancava!VOC11
	else if(z=strstr((char*)pnu,"a-e-o")){*z=VOC11;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"e-a-o")){*z=VOC11;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"o-a-e")){*z=VOC11;*(z+1)='\0';}

	else if(z=strstr((char*)pnu,"a-e")){*z=VOC1;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"e-a")){*z=VOC1;*(z+1)='\0';}
	//else if(z=strstr((char*)pnu,"i-o")){*z=VOC0;*(z+1)='\0';}
	//crea errore con VOC4
	else if(z=strstr((char*)pnu,"o-i")){*z=VOC0;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"e-i")){*z=VOC2;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"i-e")){*z=VOC2;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"a-i")){*z=VOC8;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"i-a")){*z=VOC8;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"a-o")){*z=VOC9;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"o-a")){*z=VOC9;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"e-o")){*z=VOC10;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"o-e")){*z=VOC10;*(z+1)='\0';}
	else if(z=strstr((char*)pnu,"-o")){*z=VOC4;*(z+1)='\0';}
	for(m=0;m<strlen(pnu);m++)
	{
		char c=*(pnu+m);
		if(!isalnum(c)&&c!=VOC10&&c!=VOC11)
		{
			CloseHandle(hVocabolario);
			CloseHandle(hNuovo);
			MessageBox(GetActiveWindow(),"Sintassi scorretta o gruppo multiplo non supportato","Ahi",MB_ICONINFORMATION);
			return FALSE;
		}
	}

if(!*por)//inserisci
{
	Fpoint=SetFilePointer(hVocabolario,0,0,FILE_END);
	if(!WriteFile(hVocabolario,pnu,strlen(pnu),&dwsize,NULL))
		DWORD hh=GetLastError();
	WriteFile(hVocabolario,"\r\n",2,&dwsize,NULL);
	CloseHandle(hVocabolario);
	CloseHandle(hNuovo);
	if(!HeapFree(hDataHeap,NULL,NULL))
		ErrorReporter("dealloc heap");
	HeapInit();
//		MessageBox(GetActiveWindow(),"Vocabolario aggiornato","",MB_ICONINFORMATION);
		SetWindowText(ghWndToolbarDlg,"Vocabolario aggiornato");
		return TRUE;

}



	OutputDebugString("cerco ");
	OutputDebugString(por);
	OutputDebugString("\n");
	int trovo=0;
	for(int n=0;;n++)
	{

		BOOL b=
		ReadFile(
		hVocabolario,                // handle to file
		(void*)buffer,             // data buffer
		16,  // number of bytes to read
		&dwsize, // number of bytes read
		NULL   // overlapped buffer
		);

		if(dwsize<2)
			break;

		strtok(buffer,"\r\n");

		//strcpy(resto,strtok(NULL,""));
	//OutputDebugString(buffer);
	//OutputDebugString(",");

		int z=dwsize-2-strlen(buffer);

		if(!strcmp(buffer,por))
		{
			trovo++;
			OutputDebugString("TROVO!");
			strcpy(buffer,pnu);
		}

		if(buffer[0])//per elimina
		{
		Fpoint=SetFilePointer(hVocabolario,-z,0,FILE_CURRENT);

		WriteFile(hNuovo,buffer,strlen(buffer),&dwsize,NULL);
		WriteFile(hNuovo,"\r\n",2,&dwsize,NULL);
		}
		else
		{

			Fpoint=SetFilePointer(hVocabolario,-z,0,FILE_CURRENT);
		}
	}


CloseHandle(hVocabolario);
CloseHandle(hNuovo);

if(trovo)
{
BOOL b= CopyFile(
      // file name
  "temp.voc", // replacement file
  gFILE_VOCABOLARIO,
  FALSE
);
if(!b)
	DWORD error=GetLastError( );


if(!HeapFree(hDataHeap,NULL,NULL))
			ErrorReporter("dealloc heap");

HeapInit();
//	MessageBox(GetActiveWindow(),"Vocabolario aggiornato","",MB_ICONINFORMATION);
SetWindowText(ghWndToolbarDlg,"Vocabolario aggiornato");
DeleteFile("temp.voc");
}
else
{
	sprintf(buffer,"%s: lemma non trovato nel dizionario",por);
	MessageBox(GetActiveWindow(),buffer,"",MB_ICONINFORMATION);
}

return TRUE;
}

#ifndef NASSYRYA

BOOL ControLL(BYTE hv,int y,int x)
{
	struct lemmaSTR appo;
	char parola[32],parolabase[32];
	int cnt=0;
	int xflag=0;
	int ctx=0;
	int ystart,xstart;
	int value=0;
	int tvalue=0;
	int mulflag=1;
	int bvalue=0;
	int bmulflag=1;
	value=0;//madrid
	char ap2[80];
//	int ck;

	switch(hv)
	{
	case ORIZZONTALE:
		ystart=y;
		xstart=x;
		while(casa[y][x].flag!=LIBERA&&x<15)
		{
			//parigi: non usa bonus nascosti da lettere permanenti
			if(casa[y][x].vcasa<4)
				bvalue+=casa[y][x].s.valore*(casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa);
			else
			{
				bmulflag*=casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa-2;
				bvalue+=casa[y][x].s.valore;
			}

			parolabase[ctx++]=casa[y][x].s.lettera;
			if(casa[y][x].flag!=PERMANENTE)
			{
				//trova inizio parola verticale
				while(casa[y][x].flag!=LIBERA&&y>=0)
					y--;
				y++;
				if(y<0)
					y=0;

				for(y;;y++)
				{
					if(y>14)
						break;
					if(casa[y][x].flag!=LIBERA)
					{
						parola[cnt++]=casa[y][x].s.lettera;
						if(casa[y][x].vcasa<4)
							tvalue+=casa[y][x].s.valore*(casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa);
						else
						{
							mulflag*=casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa-2;
							tvalue+=casa[y][x].s.valore;
						}

					}
					else
						break;
				}
				parola[cnt]=0;
				cnt=0;
				if(strlen(parola)>LUNGHEZZA_MINIMA)//controlla lunghezza parola laterale verticale
				{

					//qui la parola laterale verticale è di più di due lettere...
					strcpy(appo.parola,parola);


					if(player==PLAYER2 && !Check_in_Diz(&appo,1))
					{

						value=0;
						return FALSE;
					}
					else if(player==PLAYER1)
					{
						appo.value=1;//sennò fallisce check in diz!!
						if(Controlla_Inserimento(&appo)==FALSE)
						{
							value=0;
							return RITIRA_INSERIMENTO;
						}

					}
				}
				else
				{

					//la parola laterale verticale è di due lettere
#ifdef ROMA
IBL1:;
		//CONTROLLA CHE I GRUPPI DI DDUE LETTERE
		//CONTENGANO UNA VOCALE ED UNA CONSONANTE
					xflag=0;
					if(strlen(parola)==LUNGHEZZA_MINIMA)
					{
						xflag=0;//roma
						if(Is_Biletterale(parola))
							xflag=1;
						/*
						for(int r=0;r<NUM_PROVINCIE;r++)
							if(!strcmp(parola,provincia[r]))
								xflag=1;
						*/
						if(!xflag)
						{
							if(player==PLAYER1)
							{

#ifndef TROMSOE
								sprintf(ap2,"il gruppo %s non è ammesso. Inserire?",parola);//calcutta
								if(MessageBox(ghWndToolbarDlg,ap2,"",MB_ICONQUESTION|MB_YESNO)==IDYES)//calcutta
								{
									InserisciBiletterale(parola);//calcutta
									goto IBL1;

								}
#endif
								return RITIRA_INSERIMENTO;
							}
							else if(player==PLAYER2)
								return FALSE;

						}
					}


					else//madrid
					{
						tvalue=0;
						mulflag=1;
					}
#endif//roma
				}
			}//fine casa non permanente

			value+=tvalue*mulflag;
			tvalue=0;
			mulflag=1;
			x++;
			y=ystart;
		}
		if(x-xstart>LUNGHEZZA_MINIMA)//la parola inserita ha almeno 3 lettere
		{
			if(player==PLAYER1)
			{
				parolabase[ctx]=0;
				strcpy(appo.parola,parolabase);
				appo.value=1;//sennò fallisce check in diz!!
				if(Controlla_Inserimento(&appo)==FALSE)
				{

					value=0;
					return RITIRA_INSERIMENTO;
				}
			}
			value+=bvalue*bmulflag;
		}//parola lunga
		else//la parola inserita ha 2 lettere
		{
#ifdef ROMA
IBL2:;
		//CONTROLLA CHE I GRUPPI DI DDUE LETTERE
					xflag=0;

					parolabase[ctx]=0;//madrid
					strcpy(parola,parolabase);//madrid
					if(strlen(parola)==LUNGHEZZA_MINIMA)
					{

						xflag=0;//ROMA
						if(Is_Biletterale(parola))
							xflag=1;
						/*
						for(int r=0;r<NUM_PROVINCIE;r++)
							if(!strcmp(parola,provincia[r]))
								xflag=1;
						*/

						if(xflag==3||!xflag)
						{
							if(player==PLAYER1)
							{

#ifndef TROMSOE
								sprintf(ap2,"il gruppo %s non è ammesso. Inserire?",parola);//calcutta
								if(MessageBox(ghWndToolbarDlg,ap2,"",MB_ICONQUESTION|MB_YESNO)==IDYES)//calcutta
								{
									InserisciBiletterale(parola);//calcutta
									goto IBL2;

								}
#endif
								return RITIRA_INSERIMENTO;
							}
							else if(player==PLAYER2)
								return FALSE;

						}
						value+=bvalue*bmulflag;//madrid
					}

#endif

		}//else
		break;
	case VERTICALE:
		xstart=x;
		ystart=y;
		while(casa[y][xstart].flag!=LIBERA&&y<15)
		{
			if(casa[y][x].vcasa<4)
				bvalue+=casa[y][x].s.valore*(casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa);
			else
			{
				bmulflag*=casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa-2;
				bvalue+=casa[y][x].s.valore;
			}
			parolabase[ctx++]=casa[y][x].s.lettera;
			if(casa[y][xstart].flag!=PERMANENTE)
			{

				//trova inizio parola orizzontale
				while(casa[y][x].flag!=LIBERA&&x>=0)
					x--;
				x++;
				if(x<0)
					x=0;

				for(x;;x++)
				{
					if(x>14)
						break;
					if(casa[y][x].flag!=LIBERA)
					{
						parola[cnt++]=casa[y][x].s.lettera;
						if(casa[y][x].vcasa<4)
							tvalue+=casa[y][x].s.valore*(casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa);
						else
						{
							mulflag*=casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa-2;
							tvalue+=casa[y][x].s.valore;
						}
					}
					else
						break;
				}
				parola[cnt]=0;
				cnt=0;
				if(strlen(parola)>LUNGHEZZA_MINIMA)
				{
				//	sprintf(avviso,"controll_H: %s",parola);
				//	MessageBox(GetActiveWindow(),avviso,NULL,NULL);
					strcpy(appo.parola,parola);
					if(player==PLAYER2 && !Check_in_Diz(&appo,1))
					{
						if(player==PLAYER2)
						{
							value=0;
							return FALSE;
						}
					}
					else if(player==PLAYER1)
					{
						appo.value=1;//sennò fallisce check in diz!!
						if(Controlla_Inserimento(&appo)==FALSE)
						{

							value=0;
							return RITIRA_INSERIMENTO;
						}

					}
				}
				else
				{
#ifdef ROMA
IBL3:;
		//CONTROLLA CHE I GRUPPI DI DDUE LETTERE
		//CONTENGANO UNA VOCALE ED UNA CONSONANTE
					xflag=0;
					if(strlen(parola)==LUNGHEZZA_MINIMA)
					{

						xflag=0;//ROMA
						if(Is_Biletterale(parola))
							xflag=1;
						/*
						for(int r=0;r<NUM_PROVINCIE;r++)
							if(!strcmp(parola,provincia[r]))
								xflag=1;
						*/

						if(xflag==3||!xflag)
						{
							if(player==PLAYER1)
							{

#ifndef TROMSOE
								sprintf(ap2,"il gruppo %s non è ammesso. Inserire?",parola);//calcutta
								if(MessageBox(ghWndToolbarDlg,ap2,"",MB_ICONQUESTION|MB_YESNO)==IDYES)//calcutta
								{
									InserisciBiletterale(parola);//calcutta
									goto IBL3;

								}
#endif
								return RITIRA_INSERIMENTO;
							}
							else if(player==PLAYER2)
								return FALSE;

						}
					}


					else//madrid
					{
						tvalue=0;
						mulflag=1;
					}
#endif//roma
				}//else
			}//permanente
			value+=tvalue*mulflag;
			tvalue=0;
			mulflag=1;
			y++;
			x=xstart;
		}//while
		if(y-ystart>LUNGHEZZA_MINIMA)//SERVE PER NON CONTEGGIARE LE PAROLE DI DUE LETTERE
		{
			if(player==PLAYER1)
			{
				parolabase[ctx]=0;
				strcpy(appo.parola,parolabase);
				appo.value=1;//sennò fallisce check in diz!!
				if(Controlla_Inserimento(&appo)==FALSE)
				{
					value=0;
					return RITIRA_INSERIMENTO;
				}
			}
			value+=bvalue*bmulflag;
		}//parola lunga
		else
		{
#ifdef ROMA
IBL4:;
		//CONTROLLA CHE I GRUPPI DI DDUE LETTERE
		//CONTENGANO UNA VOCALE ED UNA CONSONANTE
					parolabase[ctx]=0;//madrid
					strcpy(parola,parolabase);//madrid

					xflag=0;
					if(strlen(parola)==LUNGHEZZA_MINIMA)
					{

						xflag=0;//ROMA
						if(Is_Biletterale(parola))
							xflag=1;
						/*
						for(int r=0;r<NUM_PROVINCIE;r++)
							if(!strcmp(parola,provincia[r]))
								xflag=1;
						*/

						if(xflag==3||!xflag)
						{
							if(player==PLAYER1)
							{
#ifndef TROMSOE
								sprintf(ap2,"il gruppo %s non è ammesso. Inserire?",parola);//calcutta
								if(MessageBox(ghWndToolbarDlg,ap2,"",MB_ICONQUESTION|MB_YESNO)==IDYES)//calcutta
								{
									InserisciBiletterale(parola);//calcutta
									goto IBL4;

								}
#endif
								return RITIRA_INSERIMENTO;
							}
							else if(player==PLAYER2)
								return FALSE;

						}
						value+=bvalue*bmulflag;//madrid: conteggia anche gruppi 2 lettere!!!!
					}

#endif
			value+=0;
		}//else
		break;
	}//eosw hv
	//in value dovrei avere il valore delle parole nate dagli incroci
	//ma per ora non si ritorna

	//if(flag_prima_tessera && iplayer[0].punti==0){
	if(iplayer[0].punti==0 && iplayer[	1].punti==0){
			value*=2;//MEMPHIS
			flag_prima_tessera=FALSE; //kyoto
	}

	value+=AggiungiExtra();
	return value;
}

#endif

/* FINE SCROLL VERTICALE*/
int MemGrBil()//OSLO
{
	

	DWORD Bread;

//	memset(provincia,0,sizeof(provincia));
	memset(MemoriaBiletterali,0,sizeof(MemoriaBiletterali));

	HANDLE hBil=CreateFile(
		   FILE_BILET,
		   GENERIC_READ,
		   FILE_SHARE_READ,
		   NULL,
		   OPEN_EXISTING,
		   NULL,
		   NULL);

	if(hBil==INVALID_HANDLE_VALUE)
	{
		int er=GetLastError();
		char ap2[80];
		sprintf(ap2,"Errore %d su MemGrBil %s",er,FILE_BILET);
		MessageBox(ghWndToolbarDlg,ap2,"",MB_OK|MB_ICONSTOP);

		return FALSE;
	}

	if(ReadFile(hBil,(void*)MemoriaBiletterali,(sizeof(MemoriaBiletterali)-1),&Bread,NULL)==FALSE)
	{
		CloseHandle(hBil);
		return FALSE;
	}

	CloseHandle(hBil);

return TRUE;
}

int InserisciBiletterale(char* bi)//calcutta
{
	char carola[8];

	if(strlen(bi)!=2)
		return FALSE;
	strcpy(carola,bi);
	DWORD Bread;

//	memset(provincia,0,sizeof(provincia));
	//memset(appo,0,sizeof(appo));

	HANDLE hBil=CreateFile(
		   FILE_BILET,
		   GENERIC_READ|GENERIC_WRITE,
		   FILE_SHARE_READ,
		   NULL,
		   OPEN_ALWAYS,
		   NULL,
		   NULL);

	if(hBil==INVALID_HANDLE_VALUE)
	{
		int er=GetLastError();
		char ap2[80];
		sprintf(ap2,"Errore %d su Inseriscibiletterale %s",er,FILE_BILET);
		MessageBox(ghWndToolbarDlg,ap2,"",MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	SetFilePointer(hBil,0,0,FILE_END);

	strcat(carola,"\r\n");
	if(WriteFile(hBil,(void*)carola,4,&Bread,NULL)==FALSE)
	{
		CloseHandle(hBil);
		return FALSE;
	}

	CloseHandle(hBil);
	MemGrBil();//memorizza il file
	return TRUE;
}


//BOOL ControLL(BYTE hv,int y,int x)
BOOL ControLLN(struct lemmaSTR* pappo)
{

	BYTE hv=pappo->hv;
	int y=pappo->index.y;
	int x=pappo->index.x;
	//struct lemmaSTR appo;
	char parola[32],parolabase[32];
	int cnt=0;
	int xflag=0;
	int ctx=0;
	int ystart,xstart;
	int value=0;
	int tvalue=0;
	int mulflag=1;
	int bvalue=0;
	int bmulflag=1;
	value=0;//madrid
//	int ck;
	char ap2[80];
	switch(hv)
	{
	case ORIZZONTALE:
		ystart=y;
		xstart=x;
		while(casa[y][x].flag!=LIBERA&&x<15)
		{
			//parigi: non usa bonus nascosti da lettere permanenti
			if(casa[y][x].vcasa<4)
				bvalue+=casa[y][x].s.valore*(casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa);
			else
			{
				bmulflag*=casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa-2;
				bvalue+=casa[y][x].s.valore;
			}

			parolabase[ctx++]=casa[y][x].s.lettera;
			if(casa[y][x].flag!=PERMANENTE)
			{
				//trova inizio parola verticale
				while(casa[y][x].flag!=LIBERA&&y>=0)
					y--;
				y++;
				if(y<0)
					y=0;

				for(y;;y++)
				{
					if(y>14)
						break;
					if(casa[y][x].flag!=LIBERA)
					{
						parola[cnt++]=casa[y][x].s.lettera;
						if(casa[y][x].vcasa<4)
							tvalue+=casa[y][x].s.valore*(casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa);
						else
						{
							mulflag*=casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa-2;
							tvalue+=casa[y][x].s.valore;
						}

					}
					else
						break;
				}
				parola[cnt]=0;
				cnt=0;
				if(strlen(parola)>LUNGHEZZA_MINIMA)//controlla lunghezza parola laterale verticale
				{

					//qui la parola laterale verticale è di più di due lettere...
					strcpy(pappo->parola,parola);


					if(player==PLAYER2 && !Check_in_Diz(pappo,1))
					{

						value=0;
						return FALSE;
					}
					else if(player==PLAYER1)
					{
						pappo->value=1;//sennò fallisce check in diz!!
						if(Controlla_Inserimento(pappo)==FALSE)
						{
							value=0;
							return RITIRA_INSERIMENTO;
						}

					}
				}
				else
				{

					//la parola laterale verticale è di due lettere
#ifdef ROMA
IBL1:;
		//CONTROLLA CHE I GRUPPI DI DDUE LETTERE
		//CONTENGANO UNA VOCALE ED UNA CONSONANTE
					xflag=0;
					if(strlen(parola)==LUNGHEZZA_MINIMA)
					{
						xflag=0;//roma
						if(Is_Biletterale(parola))
							xflag=1;
						/*
						for(int r=0;r<NUM_PROVINCIE;r++)
							if(!strcmp(parola,provincia[r]))
								xflag=1;
						*/

						if(!xflag)
						{
							if(player==PLAYER1)
							{

#ifndef TROMSOE
								sprintf(ap2,"il gruppo %s non è ammesso. Inserire?",parola);//calcutta
								if(MessageBox(ghWndToolbarDlg,ap2,"",MB_ICONQUESTION|MB_YESNO)==IDYES)//calcutta
								{
									InserisciBiletterale(parola);//calcutta
									goto IBL1;

								}
#endif
								return RITIRA_INSERIMENTO;
							}
							else if(player==PLAYER2)
								return FALSE;

						}
					}


					else//madrid
					{
						tvalue=0;
						mulflag=1;
					}
#endif//roma
				}
			}//fine casa non permanente

			value+=tvalue*mulflag;
			tvalue=0;
			mulflag=1;
			x++;
			y=ystart;
		}
		if(x-xstart>LUNGHEZZA_MINIMA)//la parola inserita ha almeno 3 lettere
		{
			if(player==PLAYER1)
			{
				parolabase[ctx]=0;
				strcpy(pappo->parola,parolabase);
				pappo->value=1;//sennò fallisce check in diz!!
				if(Controlla_Inserimento(pappo)==FALSE)
				{

					value=0;
					return RITIRA_INSERIMENTO;
				}
			}
			value+=bvalue*bmulflag;
		}//parola lunga
		else//la parola inserita ha 2 lettere
		{
#ifdef ROMA
IBL2:;
		//CONTROLLA CHE I GRUPPI DI DDUE LETTERE
		//CONTENGANO UNA VOCALE ED UNA CONSONANTE
					xflag=0;

					parolabase[ctx]=0;//madrid
					strcpy(parola,parolabase);//madrid
					if(strlen(parola)==LUNGHEZZA_MINIMA)
					{

						xflag=0;//ROMA
						if(Is_Biletterale(parola))
							xflag=1;
						/*
						for(int r=0;r<NUM_PROVINCIE;r++)
							if(!strcmp(parola,provincia[r]))
								xflag=1;
						*/

						if(xflag==3||!xflag)
						{
							if(player==PLAYER1)
							{

#ifndef TROMSOE
								sprintf(ap2,"il gruppo %s non è ammesso. Inserire?",parola);//calcutta
								if(MessageBox(ghWndToolbarDlg,ap2,"",MB_ICONQUESTION|MB_YESNO)==IDYES)//calcutta
								{
									InserisciBiletterale(parola);//calcutta
									goto IBL2;

								}
#endif
								return RITIRA_INSERIMENTO;
							}
							else if(player==PLAYER2)
								return FALSE;

						}
						value+=bvalue*bmulflag;//madrid
					}

#endif

		}//else
		break;
	case VERTICALE:
		xstart=x;
		ystart=y;
		while(casa[y][xstart].flag!=LIBERA&&y<15)
		{
			if(casa[y][x].vcasa<4)
				bvalue+=casa[y][x].s.valore*(casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa);
			else
			{
				bmulflag*=casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa-2;
				bvalue+=casa[y][x].s.valore;
			}
			parolabase[ctx++]=casa[y][x].s.lettera;
			if(casa[y][xstart].flag!=PERMANENTE)
			{

				//trova inizio parola orizzontale
				while(casa[y][x].flag!=LIBERA&&x>=0)
					x--;
				x++;
				if(x<0)
					x=0;

				for(x;;x++)
				{
					if(x>14)
						break;
					if(casa[y][x].flag!=LIBERA)
					{
						parola[cnt++]=casa[y][x].s.lettera;
						if(casa[y][x].vcasa<4)
							tvalue+=casa[y][x].s.valore*(casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa);
						else
						{
							mulflag*=casa[y][x].flag==PERMANENTE?1:casa[y][x].vcasa-2;
							tvalue+=casa[y][x].s.valore;
						}
					}
					else
						break;
				}
				parola[cnt]=0;
				cnt=0;
				if(strlen(parola)>LUNGHEZZA_MINIMA)
				{
				//	sprintf(avviso,"controll_H: %s",parola);
				//	MessageBox(GetActiveWindow(),avviso,NULL,NULL);
					strcpy(pappo->parola,parola);
					if(player==PLAYER2 && !Check_in_Diz(pappo,1))
					{
						if(player==PLAYER2)
						{
							value=0;
							return FALSE;
						}
					}
					else if(player==PLAYER1)
					{
						pappo->value=1;//sennò fallisce check in diz!!
						if(Controlla_Inserimento(pappo)==FALSE)
						{

							value=0;
							return RITIRA_INSERIMENTO;
						}

					}
				}
				else
				{
#ifdef ROMA
IBL3:;
		//CONTROLLA CHE I GRUPPI DI DDUE LETTERE
		//CONTENGANO UNA VOCALE ED UNA CONSONANTE
					xflag=0;
					if(strlen(parola)==LUNGHEZZA_MINIMA)
					{

						xflag=0;//ROMA
						if(Is_Biletterale(parola))
							xflag=1;
						/*
						for(int r=0;r<NUM_PROVINCIE;r++)
							if(!strcmp(parola,provincia[r]))
								xflag=1;
						*/

						if(xflag==3||!xflag)
						{
							if(player==PLAYER1)
							{

#ifndef TROMSOE
								sprintf(ap2,"il gruppo %s non è ammesso. Inserire?",parola);//calcutta
								if(MessageBox(ghWndToolbarDlg,ap2,"",MB_ICONQUESTION|MB_YESNO)==IDYES)//calcutta
								{
									InserisciBiletterale(parola);//calcutta
									goto IBL3;

								}
#endif
								return RITIRA_INSERIMENTO;
							}
							else if(player==PLAYER2)
								return FALSE;

						}
					}


					else//madrid
					{
						tvalue=0;
						mulflag=1;
					}
#endif
				}//else
			}//permanente
			value+=tvalue*mulflag;
			tvalue=0;
			mulflag=1;
			y++;
			x=xstart;
		}//while
		if(y-ystart>LUNGHEZZA_MINIMA)//SERVE PER NON CONTEGGIARE LE PAROLE DI DUE LETTERE
		{
			if(player==PLAYER1)
			{
				parolabase[ctx]=0;
				strcpy(pappo->parola,parolabase);
				pappo->value=1;//sennò fallisce check in diz!!
				if(Controlla_Inserimento(pappo)==FALSE)
				{
					value=0;
					return RITIRA_INSERIMENTO;
				}
			}
			value+=bvalue*bmulflag;
		}//parola lunga
		else
		{
#ifdef ROMA
IBL4:;
		//CONTROLLA CHE I GRUPPI DI DDUE LETTERE
		//CONTENGANO UNA VOCALE ED UNA CONSONANTE
					parolabase[ctx]=0;//madrid
					strcpy(parola,parolabase);//madrid

					xflag=0;
					if(strlen(parola)==LUNGHEZZA_MINIMA)
					{

						xflag=0;//ROMA
						if(Is_Biletterale(parola))
							xflag=1;
						/*
						for(int r=0;r<NUM_PROVINCIE;r++)
							if(!strcmp(parola,provincia[r]))
								xflag=1;
						*/

						if(xflag==3||!xflag)
						{
							if(player==PLAYER1)
							{
#ifndef TROMSOE
								sprintf(ap2,"il gruppo %s non è ammesso. Inserire?",parola);//calcutta
								if(MessageBox(ghWndToolbarDlg,ap2,"",MB_ICONQUESTION|MB_YESNO)==IDYES)//calcutta
								{
									InserisciBiletterale(parola);//calcutta
									goto IBL4;

								}
#endif
								return RITIRA_INSERIMENTO;
							}
							else if(player==PLAYER2)
								return FALSE;

						}
						value+=bvalue*bmulflag;//madrid: conteggia anche gruppi 2 lettere!!!!
					}

#endif
			value+=0;
		}//else
		break;
	}//eosw hv
	//in value dovrei avere il valore delle parole nate dagli incroci
	//ma per ora non si ritorna
	value+=AggiungiExtra();
//	if(flag_prima_tessera)
//			value*=2;//MEMPHIS

	return value;
}


int MemPerpendicolare(int last)
{
/*
OK QUI LA PAROLA HA UNA LETTERA MINUSCOLA: VA TROVATA
E AUMENTATO X O Y SECONDO SE E' H O V.
A QUESTO PUNTO TROVO LA RIGA O LA COLONNA DA TESTARE

  nella struttura ci metto la direzione giusta e l'indice dove deporre la lettera
*/
	char mialettera;
	int i=gperp.count;


	//struct lemmaSTR copia;
	memcpy(&gperp.dati[i],&zona_appoggio[last],sizeof(struct lemmaSTR));
	struct lemmaSTR *tmp=&gperp.dati[i];//&zona_appoggio[last];

	int n;
	for(n=0;n<strlen(tmp->parola);n++)
	{
		if(*(tmp->parola+n)==tolower(*(tmp->parola+n)))
		{
			mialettera=*(tmp->parola+n);
			break;
		}
	}

	
	if(tmp->hv==ORIZZONTALE)
		tmp->index.x+=n;
	else
		tmp->index.y+=n;


	tmp->hv=(tmp->hv==ORIZZONTALE)?VERTICALE:ORIZZONTALE;

	

	tmp->parola[0]=mialettera;
	

	for(n=0;n<i;n++)//evita ripetizioni
	{
		if(!memcmp(tmp,&gperp.dati[n],sizeof(struct lemmaSTR)))
			return 0;
	}
	
	gperp.count++;

}
void Orizzontali(int min_len,int *totpar,POINT base)//MOSCA NARNI
{
	POINT point;
	char key[16],key2[32],avviso[80];
	int cae=0;
	int indice_base=-1;//narni2
	OutputDebugString("SuperEngine H\n");
	int start,stop;

	if(base.y)//narni lione
		{
		base.y-=100;
		base.x-=100;
		start=base.y;
		stop=start+1;
		}
	else
		{
		start=0;stop=15;
		}
	for(int y=start;y<stop;y++)

	{
		int target=15;

alux:;
		int itarget=16-target;//=numero di lettere della parola


		for(int z=0;z<itarget;z++)//per tutte le lettere..
		{
			int flag=0;


			//scarta se quella prima e' permanente
			if(z)//se siamo oltre la prima lettera..
				if(casa[y][z-1].flag==PERMANENTE)
				{
					//OutputDebugString("u1-");
					continue;
				}


			if(base.y)//lione
			{
				if(z>base.x)
				{
					//OutputDebugString("U4-");
					continue;//break;
				}
				if(target+z<base.x)//digione
				{
					//OutputDebugString("U5-");
					continue;//break;
				}

			}

			for(int x=z;x<target+z;x++)//x=posizione
			{
				//controlla che la casella dopo sia libera
				if(x<14)
				{
					if(target+z<15)//berlinoest
						if(casa[y][target+z].flag==PERMANENTE)
							goto thez;//non è libera
				}

				if(casa[y][x].flag==PERMANENTE)
				{
					if(!flag)//coordinate dell'origine nella matrice
					{
						point.x=x;
						point.y=y;
					}
					flag++;
					key[x-z]=casa[y][x].s.lettera;
				}
				else
					key[x-z]='?';
			}

			if(flag>=min_len)//conto costanti>=minimo numero di costanti
			{
			//trovato qualcosa..
			//	nparole=Find_in_Diz(buf);ù
				cae++;
				//Beep(220,10);
				if(flag>1)
					flag=flag;

				key[target]=0;
				if(!strchr(key,'?'))
					continue;//deve aggiungere almeno una lettera!

				strcpy(key2,"$");
				strcat(key2,key);
				
		

				//dopo che una parola e' stata trovata, vengono eliminate tutte le chiavi
				//di lungh. inferiore a maxlen. una opzione potrebbe stabilire
				//a quanto limitare il maxlen. ad es, anche se ho trov. una parola di 13
				//voglio lo stesso cercare quelle di 7. allora metto maxlen=7
				//maxlen=maxlen>7?7:maxlen;//DIGIONE!!
				if(strlen(key)<maxlen)//<>7?7:maxlen))//(maxlen<7?maxlen:maxlen-1))
				{
					continue;
				}


				point.x=z;

				//cancella la zona appoggio dopo quella buona..
				//int fim=totpar*sizeof(struct lemmaSTR);
				//memset((byte*)&zona_appoggio+fim,0,sizeof(zona_appoggio)-fim);
char avviso[166];
/*
				if(base.y)//lione
				{
				sprintf(avviso,"%s - (H)y=%d x=%d trg=%d z=%d\n"
					,key2,point.y,point.x,target,z);
				OutputDebugString(avviso);
				}
*/
				Analysis_Engine(key2,point,ORIZZONTALE,flag,totpar);

#ifdef VERSIONEOK
				*totpar=Analysis_Engine(key2,point,ORIZZONTALE,flag,*totpar);
#endif

				if(*totpar<0)
				{
				sprintf(avviso,"\nNO PAROLE - FINE\n"
					,key2,point.y,point.x,target,z);
				OutputDebugString(avviso);
					return;
				}




				FIATA20

				flag=0;

			}
thez:;
		}//z
		target--;
		if(target)
			goto alux;
	}
}

void DoPerp(int *totpar)
{
char avviso[80];
	POINT p,d;
		sprintf(avviso,"%d perpendicolari",gperp.count);
		OutputDebugString(avviso);

	for(int n=0;n<gperp.count;n++)
	{
		//if (maxlen>3)
		maxlen=2;

		p.x=gperp.dati[n].index.x;
		p.y=gperp.dati[n].index.y;
		int x;
		for (x=0;x<8;x++)
		{

			
				if(tessera[PLAYER2][x].s.lettera==
					gperp.dati[n].parola[0]
					)
					break;
					
		}

		DeponiLettera(PLAYER2,p,x);

//simula la casa permanente e toglie la tessera dal mazzo
		casa[p.y][p.x].flag=PERMANENTE;
		casa[p.y][p.x].flag_perp=1;
		tessera[PLAYER2][x].flag=ASSENTE;
		
		//questo serve per eseguire la ricerca successiva in modo speciale (temporaneo)
		d.x=p.x+100;
		d.y=p.y+100;
		
		if(gperp.dati[n].hv==ORIZZONTALE)
			Orizzontali(1,totpar,d);
		else
			Verticali(1,totpar,d);
		
		casa[p.y][p.x].flag=ASSENTE;
		casa[p.y][p.x].flag_perp=0;
		tessera[PLAYER2][x].flag=PRESENTE;
		Annulla_flag_temporanei(ASSENTE);
		Annulla_flag_temporanei_T(ASSENTE,PRESENTE);
		AggiornaFinestra();
	}
	gperp.count=0;
}
void Verticali(int min_len,int *totpar,POINT base)//MOSCA lione<<<
{

POINT point;
char key[16],key2[32];
int cae=0;
int indice_base=-1;//narni2
int start,stop;//narni
OutputDebugString("SuperEngine V\n");

if(base.x)//lione
{
	base.y-=100;
	base.x-=100;

	start=base.x;
	stop=start+1;
}
else
{
start=0;stop=15;
}

for(int y=start;y<stop;y++)//movimento sull'asse x
{
	int target=15;


alux2:;


	int itarget=16-target;


	for(int z=0;z<itarget;z++)
	{
		memset(&key,0,sizeof(key));
		int flag=0;
		if(z)
			if(casa[z-1][y].flag==PERMANENTE)
				continue;
		if(base.x)//lione
		{
			if(z>base.y)
				continue;

			if(target+z<base.y)//digione:la lunghezza deve comprendere la lettera 'jolly'
				continue;

		}

		for(int x=z;x<target+z;x++)
		{


			if(x<14)
				if(target+z<15)//berlinoest
					if(casa[target+z][y].flag==PERMANENTE)
						goto thez2;

			if(casa[x][y].flag==PERMANENTE)
			{
				if(!flag)//coordinate dell'origine nella matrice
				{
					point.x=y;
					point.y=x;
				}
				flag++;
				key[x-z]=casa[x][y].s.lettera;
			}
			else
				key[x-z]='?';
		}

		//FLAG E' IL CONTEGGIO DELLE PERMANENTI
		if(flag>=min_len)//tutto ma non le lettere singole
		{
			//trovato qualcosa..
			if(flag>1)
				flag=flag;

			cae++;
			key[target]=0;
			if(!strchr(key,'?'))
				continue;//deve aggiungere almeno una lettera!

			strcpy(key2,"$");
			strcat(key2,key);


			//QUI CONTROLLA CHE LA LUNGHEZZA DELLA CHIAVE DI RICERCA SIA UGUALE O MAGGIORE
			//ALLA PAROLA PIU' LUNGA GIA TROVATA
			if(strlen(key)<maxlen)//(maxlen<7?maxlen:maxlen-1))
				continue;
			char avviso[166];
			point.y=z;
			

			//QUI RICERCA NEL DIZIONARIO CON LA CHIAVE
			Analysis_Engine(key2,point,VERTICALE,flag,totpar);
#ifdef VERSIONEOK
			*totpar=Analysis_Engine(key2,point,VERTICALE,flag,*totpar);
#endif

			//QUI EVIDENTEMENTE NON PUO TROVARE PIU NIENTE..
			if(*totpar<0)
				return;

			FIATA20
		}
thez2:;
	}//z
	target--;
	if(target)
		goto alux2;

	}
}

#ifdef TUNISI
//MEMORIZZA IL VOCABOLARIO ITALIANO
BOOL HeapInit()
{
//	PROCESS_HEAP_ENTRY info;
	        SYSTEM_INFO sysInfo;
	unsigned long	Vsize;

 HANDLE hVocabolario;
 HANDLE hVocabolarioBilet;
 DWORD Bread;
 DWORD Bread2;
 int mul;
 //void* base;
//OVERLAPPED Overlap;
//char buffer[33];

DWORD dwsize;
DWORD dwsizeB;
hVocabolario=CreateFile(
		   gFILE_VOCABOLARIO,
		   GENERIC_READ,
		   FILE_SHARE_READ,
		   NULL,
		   OPEN_EXISTING,
		   NULL,
			NULL	);

	if(hVocabolario==INVALID_HANDLE_VALUE)
	{
		ErrorReporter("Manca Vocabolario");
		return FALSE;
	}

	if(dwsize=GetFileSize (hVocabolario,&Vsize)==INVALID_FILE_SIZE)
		ErrorReporter("size");


#ifdef TROMSOE
	hVocabolarioBilet = INVALID_HANDLE_VALUE;
	goto mavai;
#endif

	hVocabolarioBilet=CreateFile(
		   "2lt.voc",
		   GENERIC_READ,
		   FILE_SHARE_READ,
		   NULL,
		   OPEN_EXISTING,
		   NULL,
			NULL	);

mavai:;

	if(hVocabolarioBilet!=INVALID_HANDLE_VALUE)
	{
		dwsizeB=GetFileSize (hVocabolarioBilet,&Vsize);
		if(dwsizeB==INVALID_FILE_SIZE)
			dwsizeB=0;
	}
	
	CloseHandle(hVocabolarioBilet);
	Vsize=0x6FFFF;
    GetSystemInfo(&sysInfo);
	mul=Vsize/sysInfo.dwPageSize;
	Vsize=sysInfo.dwPageSize * mul;
        hDataHeap = HeapCreate(HEAP_NO_SERIALIZE,Vsize,Vsize);//647100 MAX DIM VOVABOLARIO
        if (hDataHeap == NULL) {
            ErrorReporter("HeapCreate (Data Heap)");
			return FALSE;
		}
	Vsize-=sysInfo.dwPageSize;
	if(HeapValidate(hDataHeap,HEAP_NO_SERIALIZE,NULL)==FALSE)
		ErrorReporter("HeapValidate");

	hBaseHeap=HeapAlloc(hDataHeap,
		HEAP_GENERATE_EXCEPTIONS|HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,
		Vsize);

	Bread=0;
	if(hVocabolarioBilet!=INVALID_HANDLE_VALUE)
	{
	
	if(ReadFile(hVocabolarioBilet,hBaseHeap,Vsize,&Bread,NULL)==FALSE)//
		//ErrorReporter("REadFileB");
		int y=GetLastError();
	}
	void * hHeap2=(void*)((volatile unsigned long)hBaseHeap+Bread);//((volatile unsigned long)hBaseHeap+Bread-300);
	if(ReadFile(hVocabolario,hHeap2,Vsize,&Bread2,NULL)==FALSE)
			ErrorReporter("REadFile");

	if(HeapValidate(hDataHeap,HEAP_NO_SERIALIZE,NULL)==FALSE)
		ErrorReporter("HeapValidate");

	if(Bread+Bread2>Vsize)
		ErrorReporter("HeapCreate (VOC troppo lungo)");

	CloseHandle(hVocabolario);
//	HeapWalk(hDataHeap,&info);
//	HeapCompact(hDataHeap,HEAP_NO_SERIALIZE);
	//adesso ho tutto il vocabolario in memoria..... !!!!!!

#ifndef TROMSOE
	MemGrBil();//oslo
#endif

	return TRUE;
}


#endif
BOOL Is_Biletterale(char*parola)
{
	char* p=MemoriaBiletterali;
	while(p && *p)
	{
		if(
			*parola==*p
			&&
			*(parola+1)==*(p+1)
		)
			return TRUE;
		p+=4;
	}
	return FALSE;
}

int AggiungiMessaggio(HWND hdlg,char* avviso)
{
char buffer[0xFFF];
GetDlgItemText(hdlg,IDC_EDIT2,buffer,sizeof(buffer)-32);
int l=strlen(buffer);
if(l&& buffer[l-1]!='\n' && avviso[0]!='\r')
strcat(buffer,"\r\n");
strcat(buffer,avviso);
SetDlgItemText(hdlg,IDC_EDIT2,buffer);
SendDlgItemMessage(hdlg,IDC_EDIT2,EM_LINESCROLL,0,1024);
		return 0;
}