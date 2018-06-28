#include "windows.h"
#include "scarabeo.h"
#include "resource.h"
//#include "tts.h"
#include <stdio.h>


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
extern int flag_FAI_SILENZIO;
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
extern int scarselect;
extern char parola_originale[];
extern float rapportoy,rapportox;
extern BOOL flag_salvato;
int Mescola()
{

	unsigned source,dest;
	struct saccoSTR appo;
	int n,steps;

	//riordina sacco randomly
	srand( (unsigned)GetTickCount() );
	steps=20000 +rand()%5000;
	for(n=0;n<steps;n++)
	{
		source=rand()%(NUM_TESSERE);
		do
		{
			dest=rand()%(NUM_TESSERE);

		}while(dest==source);
		memcpy(&appo,&sacco[source],sizeof(appo));
		memcpy(&sacco[source],&sacco[dest],sizeof(appo));
		memcpy(&sacco[dest],&appo,sizeof(appo));
	}

return steps;
}

int Assegna_tessere(BYTE player)
{
int n,cnt;
//char avviso[40];
unsigned dest;
struct saccoSTR appo;
int retry=0;
int cass;
	//Mostra_punti(ghWndToolbarDlg);//ASSISI//corinto
	cass=0;
	for(n=0;n<8;n++)
	{
		if(tessera[player][n].flag==ASSENTE)
		{
			if(psacco<NUM_TESSERE)
			{
				memcpy(&tessera[player][n],&sacco[psacco],sizeof(saccoSTR));
				tessera[player][n].pos=n;
				tessera[player][n].flag=PRESENTE;
				psacco++;
				

			}
			else
			{
				cass++;
				memset(&tessera[player][n].s,0,sizeof(struct saccoSTR));
				tessera[player][n].pos=n;
				tessera[player][n].flag=ASSENTE;
			}
		}
//	if(player==PLAYER1)
//	PlaySound("ringout.wav",NULL,NULL);//santiago: suona	
	}

	if(player==PLAYER1)
		PlaySound(
	  "btnup.wav",  
	  NULL,     
	 SND_FILENAME|SND_NODEFAULT    
	);
	Mostra_tessere_davvero();
	

	
	if(NUM_TESSERE-psacco<=0)
	{
		if(cass==8)//il sacco e' vuoto e il giocatore ha finito le tessere
		{
			return -1;
		}
		return 0;
	}


cambiotessere:;
			  
	//se sono tutte vocali o tutte consonanti cambia tutto

	cnt=0;
	for(n=0;n<8;n++)
	{
		if(tessera[player][n].s.lettera=='a'||
			tessera[player][n].s.lettera=='e'||
			tessera[player][n].s.lettera=='i'||
			tessera[player][n].s.lettera=='o'||
			//tessera[player][n].s.lettera==SCARABEO||
			tessera[player][n].s.lettera=='u')
				cnt++;
	}
//cnt=8;
	if((cnt==0||cnt==8)&&psacco<=NUM_TESSERE-8)
	{

		if(player==PLAYER1)
		{
			int g=MessageBox(ghWndToolbarDlg,"Cambiare tutte le tessere?","",MB_ICONQUESTION|MB_YESNO);
			if(g!=IDYES)
				return 0;
		}
		else if (!Global_Demox) //lima
		{
//santiago
			//sarebbe bene far vedere le tessere prima di cambiare
			int oflag_mostra_tessere=flag_mostra_tessere;
			flag_mostra_tessere=TRUE;
			Mostra_tessere_davvero();
				if(flag_check_validita)
				{

					int wen=MessageBox(ghWndToolbarDlg,"Posso cambiare le mie tessere?..","",MB_YESNO|MB_ICONINFORMATION);

					if(wen==IDNO)
					{
						flag_mostra_tessere=oflag_mostra_tessere;
						return 0;
					}

				}
				else
//fine santiago

				int g=MessageBox(ghWndToolbarDlg,"Cambio le tessere","",MB_ICONINFORMATION);
				flag_mostra_tessere=oflag_mostra_tessere;
		}

//		if(retry>2) lima
//			return 0; lima

//		psacco-=8;

		//Sleep(1000);
		//sprintf(avviso,"Cambio Tessere Pl.%d",player+1);
		//MessageBox(GetActiveWindow(),avviso,NULL,NULL);

		//Annulla_flag_temporanei(PRESENTE,ASSENTE);
	//	goto cambiotessere;

		for(n=0;n<8;n++)
		{
			dest=rand()%(NUM_TESSERE-psacco);
			tessera[player][n].flag=ASSENTE;
			memcpy(&appo,&tessera[player][n],sizeof(appo));
			memcpy(&tessera[player][n],&sacco[dest+psacco],sizeof(appo));
			memcpy(&sacco[dest+psacco],&appo,sizeof(appo));
			tessera[player][n].flag=PRESENTE;
			Mostra_tessere();

		}

		
		Mostra_tessere_davvero();


		retry++;
		AggiornaFinestra(); //scomm 19/2/12 

		if(retry<3)
			goto cambiotessere;
	}
	return 0;
}




int GetIndexTessera(BYTE player,BYTE turn,POINT p)
{
	int n;

	if(player!=turn)
		return -1;

	if(p.y<iYTESSERA || p.y>iYTESSERA+iDIMTESSERA-1)
		return -3;

	for(n=0;n<8;n++)
	{

		if(p.x > tessera[player][n].x && p.x < (tessera[player][n].x+iDIMTESSERA-1))
			return(n);
	}
	return -2;
}



int GetIndexCasa(POINT p ,LPPOINT indici)//non torna coord ma indici
{
//il tprimo numero sono le coord del cursore
	//nel secondo torna gli indici della casella
	//se OK torna 1
	int n,g;


		indici->x=indici->y=0xFF;//errore
		for(n=0;n<15;n++)
		{

			if(p.x >= casa[0][n].x && p.x <= casa[0][n].x+iDIMTESSERA-1)
			{
				indici->x=n;
				for(g=0;g<15;g++)
				{
					if(p.y >= casa[g][0].y && p.y <= casa[g][0].y+iDIMTESSERA-1)
					{
							indici->y=g;
							return 1;
					}

				}

			}

		}


		return 0;


}

int sostituzione_automatica(BYTE player,POINT Cpoint,BYTE gselection)
{
	int n;
	int index=NOT_SELECTED;

	if(gselection==NOT_SELECTED)//si richiede cancellazione di una lettera e rimborso
	{
		if(casa[Cpoint.y][Cpoint.x].flag==PERMANENTE)//VIENNA
			return 0;
		for(n=0;n<8;n++)
			if(tessera[player][n].flag==ASSENTE &&tessera[player][n].s.lettera==casa[Cpoint.y][Cpoint.x].s.lettera)
			{
				index=n;//trova il primo posto libero? no:deve trovare la lettera cancellata!
				break;
			}
		if(index==NOT_SELECTED)
			return 0;


		DeponiLettera(player,Cpoint,gselection);//cancella la casa
		tessera[player][n].flag=PRESENTE;
		return 1;



	}
	return 0;
}

//cancella tutte le case che hanno un flag diverso da 0 e da FF
void Annulla_flag_temporanei(BYTE op)
{

	int x,y;
	for (y=0;y<15;y++)
	{
		for (x=0;x<15;x++)
		{
			if (casa[y][x].flag!=ASSENTE && casa[y][x].flag!=PERMANENTE)
			{
				if(op==ASSENTE)
					casa[y][x].fsc=0;
				casa[y][x].flag=op;
			}
		}
	}
}

//guarda se il computer ha disponibile una certa lettera, in caso setta un flag
//che deve essere temporaneo e reinizializzato ad ogni nuovo lemma
int CheckDisp(char c)
{

	/*
	se lettera speciale e disponibile torna il valore ascii oppure FF
	se lettera normale disponibile torna 1
	se non disponibile torna 0
	permanente=2
	scarabeo=3
	*/
	int n;
		if(c==VOC0||c==VOC1||c==VOC2||c==VOC3||c==VOC4||c==VOC5||c==VOC6||c==VOC7||c==VOC8||c==VOC9||c==VOC10||c==VOC11)
			return(Check2(c));

	if(isupper(c))
		return 2;

	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera==c && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 1;
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera==SCARABEO && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 3;
		}

		return 0;
}

int Check2(char c)
{
/*
ritorna il valore ascii della lettera speciale
se non disponibile torna 0
nel caso VOC4, se non ha la 'o' torna FF
  */



	int n;	//per lettere speciali
	switch(c)
	{
	case VOC0:
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='o' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'o';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='i' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'i';
		}
	break;
	case VOC1:
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='a' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'a';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='e' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'e';
		}
	break;
	case VOC2:
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='e' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'e';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='i' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'i';
		}
	break;
	case VOC3:
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='a' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'a';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='e' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'e';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='o' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'o';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='i' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'i';
		}
	break;
	case VOC4:
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='o' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'o';
		}
		return 0xFF;
	break;
	case VOC5:
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='a' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'a';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='e' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'e';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='i' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'i';
		}
	break;
	case VOC6:
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='a' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'a';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='i' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'i';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='o' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'o';
		}
	break;
	case VOC7://venezia
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='e' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'e';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='i' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'i';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='o' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'o';
		}
	break;
	case VOC8://venezia
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='a' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'a';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='i' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'i';
		}
	break;
	case VOC9://venezia
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='a' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'a';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='o' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'o';
		}
	break;
	case VOC10://venezia
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='e' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'e';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='o' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'o';
		}
	break;
	case VOC11://venezia bis
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='a' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'a';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='e' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'e';
		}
	for(n=0;n<8;n++)
		if(tessera[PLAYER2][n].s.lettera=='o' && tessera[PLAYER2][n].flag==PRESENTE)
		{
			tessera[PLAYER2][n].flag=CONSIDERATA;//già considerata
			return 'o';
		}
	break;

	}//eosw
	return 0;
}

int salva(int tmp)
{
	FILE *fp;
	unsigned short salva_sacco=psacco;//punta alla prossima lettera nel sacco;
	int x,y;
	if(!tmp)
		fp=fopen("Scarabeo.sav","a+");
	else
		fp=fopen("Scarabeo.tmp","w");
	if(fp)
	{
		for (y=0;y<15;y++)
		{
			for (x=0;x<15;x++)
			{
				if (casa[y][x].flag==PERMANENTE)
				{
					if(casa[y][x].fsc)
						fputc(tolower(casa[y][x].s.lettera),fp);
					else
						fputc(toupper(casa[y][x].s.lettera),fp);
				}
				else
					fputc('.',fp);
			}
			fprintf(fp,"\n");
		}
		//fprintf(fp,"\n");

		for (y=0;y<2;y++)
			for (x=0;x<8;x++)
			{
				if(tessera[y][x].flag)
					fputc(tessera[y][x].s.lettera,fp);
				else
					fputc('+',fp);
			}
		fprintf(fp,"\n%04d%04d%d%d%d%02d\n",
			iplayer[PLAYER1].punti,
			iplayer[PLAYER2].punti,
			flag_mostra_tessere,
			flag_mostra_idee,
			flag_check_validita,
			gMaxPuntiHelp//verona
			);



	//	fprintf(fp,"%04d\n",psacco);
	//	for (y=psacco;y<NUM_TESSERE-psacco;y++)
		while(psacco<NUM_TESSERE)
		{
			if(sacco[psacco].lettera<'@'||sacco[psacco].lettera>'z')
			{
				ErrorReporter("Errore Salvataggio");
			//	return 0;
			}
				fputc(sacco[psacco++].lettera,fp);
		}
		fprintf(fp,"\n");
		fclose(fp);
		psacco=salva_sacco;//punta alla prossima lettera nel sacco;
		if(!tmp)
		{
			flag_salvato=TRUE;
//			MessageBox(ghWndToolbarDlg,"La partita e' stata salvata","",MB_ICONINFORMATION|MB_OK);
		}
		else
			flag_salvato=FALSE;
		return 1;
	}
	return 0;
}

int ripristina(int tmp)
{

	FILE *fp;
	int x,y,a,b;
	char line[20][20];

	char c;
	int hj;

	if(tmp!=1)
		fp=fopen("Scarabeo.sav","rb");
	else
		fp=fopen("Scarabeo.tmp","rb");
	if(fp)
	{

		InitStructz();
		memset(sacco,0,sizeof(sacco));

		fseek(fp,-3,SEEK_END);
idno:;

		for(x=NUM_TESSERE-1;x>=0;x--)
		{

			c=fgetc(fp);

			if(c<'a' && c!='@')
				break;

					hj=c-'a';
					if(hj<0)
						hj=26;

					sacco[x].lettera=Info_Lettera[hj].lettera;
					sacco[x].bitmap=Info_Lettera[hj].bitmap;
					sacco[x].valore=Info_Lettera[hj].valore;

			fseek(fp,-2,SEEK_CUR);

		}
		psacco=x+1;

		fseek(fp,-288,SEEK_CUR);

		for (y=0;y<15;y++)
		{
			fgets(line[y],20,fp);
		}



		for (y=0;y<15;y++)
		{
			for (x=0;x<15;x++)
			{
				if (line[y][x]!='.')
				{
					if(islower(line[y][x]))
						casa[y][x].fsc=1;
					c=tolower(line[y][x]);
					hj=c-'a';
					if(hj<0)
						hj=26;

					casa[y][x].s.lettera=Info_Lettera[hj].lettera;
					casa[y][x].s.bitmap=Info_Lettera[hj].bitmap;
					casa[y][x].s.valore=Info_Lettera[hj].valore;
					casa[y][x].flag=PERMANENTE;
				}
			}
		}
		for (y=0;y<2;y++)//prende punti,lettere e puntatore sacco
		{
			fgets(line[y],20,fp);
		}

		for (y=0,a=0;y<2;y++,a+=8)
		{
			for (x=0;x<8;x++)
			{
				c=line[0][x+a];
				if(c=='+')
				{
					memset(&tessera[y][x],0,sizeof(tesseraSTR));
					continue;

				}else{
				hj=c-'a';
				if(hj==-1||hj==-33)
					hj=26;
				else if(hj<0)
					continue;
				}
				tessera[y][x].s.lettera=Info_Lettera[hj].lettera;
				tessera[y][x].s.bitmap=Info_Lettera[hj].bitmap;
				tessera[y][x].s.valore=Info_Lettera[hj].valore;
				tessera[y][x].pos=x;
				tessera[y][x].flag=PRESENTE;

			}
		}

		for (y=0,b=0;y<2;y++,b+=4)
			for (x=0,a=1000;x<4;x++,a/=10)
				iplayer[y].punti+=(line[1][x+b]-0x30)*a;

	if(tmp!=1)
	{
		gMaxPuntiHelp=(line[1][11]-0x30)*10+(line[1][12]-0x30);//verona
	}
	else gMaxPuntiHelp=0;//su rifiuta non conta

	if(tmp!=1)
	{
	BOOL b=PlaySound(
  "btnup.wav",  
  NULL,     
 SND_FILENAME|SND_NODEFAULT    
);

   

		AggiornaFinestra();
	}
	if(gMaxPuntiHelp)
	{
	char avviso[180];
		sprintf(avviso,"Era stato fornito aiuto per una parola da %d punti",gMaxPuntiHelp);
	MessageBox(ghWndToolbarDlg,avviso,"",MB_OK);

	}
	fclose(fp);
		return 1;
	}
	return 0;
}

int Trovaparola(struct lemmaSTR *pl)
{

#define HV pl->hv
#define INFOCASA casa[y][x].flag
#define PL_X pl->index.x
#define PL_Y pl->index.y

int y,x,flag;
int r,c;
flag=0;
char parola[16];
		for (y=0;y<15;y++)
		{
			for (x=0;x<15;x++)
			{
				if(INFOCASA==TEMPORANEA_PL1 && !flag)
				{
					PL_Y=y;
					PL_X=x;
					flag=1;
				}
				else if(INFOCASA==TEMPORANEA_PL1 && flag)
				{
					if(x==PL_X)
					{
						HV=VERTICALE;
						flag=2;
					//	return 0;
					}
					else if(y==PL_Y)
					{
						HV=ORIZZONTALE;
						flag=2;
					}
					else
						return 1;//errore di inserimento
				}
			}
		}
		if(!flag)
			return 2;//trovato niente

		else
		{
			//in questo caso abbiamo inserito una sola lettera:
			//bisogna trovare il punto di partenza della parola
			if(flag==1)
			{
				/*
				qui e' un bettarello TRAPANI

				*/
				if(PL_X>0)
					if(casa[PL_Y][PL_X-1].flag==PERMANENTE)
						HV=ORIZZONTALE;
				if(PL_X<14)
					if(casa[PL_Y][PL_X+1].flag==PERMANENTE)
						HV=ORIZZONTALE;
				if(PL_Y>0)
					if(casa[PL_Y-1][PL_X].flag==PERMANENTE)
						HV=VERTICALE;
				if(PL_Y<14)
					if(casa[PL_Y+1][PL_X].flag==PERMANENTE)
						HV=VERTICALE;

			}

			if(HV!=VERTICALE && HV!=ORIZZONTALE)
				return 1;

			//e adesso si trova l'inizio della parola
			switch(HV)
			{
				case ORIZZONTALE:
				while(casa[PL_Y][PL_X].flag!=LIBERA)
				{
					//if(PL_X)
					PL_X--;
					if(PL_X<0)
						break;
				}
				PL_X++;
				//PL_X+=2;
				break;
				case VERTICALE:
				while(casa[PL_Y][PL_X].flag!=LIBERA)
				{
					//if(PL_Y)
					PL_Y--;
					if(PL_Y<0)
						break;
				}
				PL_Y++;
				break;
			}
		}

		r=PL_Y;
		c=PL_X;
		int nper=0;//conta permanenti
		while(casa[r][c].flag!=LIBERA)
		{
			//qui controlla le permanenti
			if(casa[r][c].flag==PERMANENTE)
				nper++;

			switch(HV)
			{
			case ORIZZONTALE:
				if(r>0)
					if(casa[r-1][c].flag==PERMANENTE)
						nper++;
				if(r<14)
					if(casa[r+1][c].flag==PERMANENTE)
						nper++;
				c++;
			break;
			case VERTICALE:
				if(c>0)
					if(casa[r][c-1].flag==PERMANENTE)
						nper++;
				if(c<14)
					if(casa[r][c+1].flag==PERMANENTE)
						nper++;
				r++;
			break;
			}
		}

		if(casa[7][7].flag==ASSENTE)
			return 1;
		else if(casa[7][7].flag==PERMANENTE)
			if(!nper)
				return 1;//errore ins.

		r=PL_Y;
		c=PL_X;
		x=0;
		while(casa[r][c].flag!=LIBERA)
		{
				//qui controlla gli scarabei
				parola[x]=casa[r][c].s.lettera;
				if(parola[x]=='@')
				{
					BattezzaScarabeo(r,c);
				}
				x++;
				if(HV==ORIZZONTALE)
				{
					c++;
					if(c>14)
						break;
				}
				else if(HV==VERTICALE)
				{
					r++;
					if(r>14)
						break;

				}
		}
		parola[x]=0;
		strcpy(pl->parola,parola);
		
		//PAROLA contiene la parola inserita
		char buffer[32];
		sprintf(buffer,"%s [%c%X%X]\r\n"
			,parola
			,HV==ORIZZONTALE?'H':'V'
			,PL_Y
			,PL_X
			);
		AggiungiMessaggio(ghWndToolbarDlg,buffer);
	AggiornaFinestra();

		return 0;
}

int AggiungiExtra()
{
/*
conta le temporanee nello schema per sapere quante lettere hai utilizzato
*/

	int clib,n;

				clib=0;
				for(int x=0;x<15;x++)//lampedusa
				{
					for(int y=0;y<15;y++)//lampedusa
					{
						if(casa[x][y].flag==TEMPORANEA_PL1||casa[x][y].flag==TEMPORANEA_PL2)
							clib++;
					}
				}
				/*
				usate
				6 : 10 punti extra
				7 : 20 punti extra
				8 : 40 punti extra
				*/
				
				
				
				if(clib>5)
					n=(clib-5)*10;
				else
					n=0;

				
	return n;
}

int Mostra_Lemmi(int nl,HWND hdlg)
{

	//ritorna: 0 = errore  <n>=indice della parola selezionata nella zona_appoggio (maxi)
	int n,x,y,g,h,k;
	char buffer[8184];
	char avviso[160];
	char p[32];
	char ugo[64];
	BYTE fmi;
	int cnt,len,maxi,maxl,maxiv,maxv;
	int chkd;
nextword:;
	if(nl<=0)
		return -1;
	buffer[0]=0;
	maxi=maxl=maxv=maxiv=k=0;
	k=0;
	for(n=0;n<nl;n++)
	{

		while(!zona_appoggio[k].hv)//parola[0])
		{
			if(k<LZA)
				k++;
			else
				goto breakall;
		}

		if(zona_appoggio[k].hv)
		{
		
			if(strlen(zona_appoggio[k].parola)>maxl)
			{
				maxi=k;
				maxl=strlen(zona_appoggio[k].parola);
			}
			
			int val=zona_appoggio[k].value;
			if(strchr(zona_appoggio[k].parola,'q'))//eccezione per la q: gli da un valore di 1,5 nella valutazione
													//in modo da preferire sempre di deporla ma non sporca il valore vero
			{
				val*=150;
				val/=100;
			}

			//adesso dimezza per ogni scarabeo..
			if((val/(zona_appoggio[k].qsc+1))>maxv)
			{
				//anche se esiste una parola che senza scarabeo fa più della metà è meglio...
				maxiv=k;
				maxv=val/(zona_appoggio[k].qsc+1);
			}
			//un altra parola ha gli stessi punti.. LECCE
			else if((val/(zona_appoggio[k].qsc+1))==maxv)
			{
				//anche se esiste una parola che senza scarabeo fa più della metà è meglio...
				if(rand()%2)
					maxiv=k;
			}

			k++;
		}
	}
breakall:;
	if(maxl==0)
	{
		AggiungiMessaggio(ghWndToolbarDlg,"Nessuna possibile");
		return -1;
	}



	n=maxiv;	//seleziona la più valorosa

	sprintf(ugo,"Punti: %d\r\n%s",zona_appoggio[n].value,zona_appoggio[n].parola);
	AggiungiMessaggio(ghWndToolbarDlg,ugo);
	

		OutputDebugString(ugo);


		if(zona_appoggio[n].hv)
		{
			//calcola indice partenza parola
			//ma mi serve un punto di partenza..

			strcpy(p,zona_appoggio[n].parola);
			x=zona_appoggio[n].index.x;
			y=zona_appoggio[n].index.y;


			len=strlen(p);
			cnt=0;



			Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);
			Annulla_flag_temporanei(ASSENTE);
			//supponiamo orizzontale..


			if(zona_appoggio[n].hv==ORIZZONTALE)
			{

				for(g=x,h=0;g<x+len-cnt;g++,h++)
				{
					if(casa[y][g].flag==PERMANENTE)
					{
					}
					else if(casa[y][g].flag==LIBERA)
					{//se la mia lettera è maiuscola, vuol dire verticale

						/* va tolto: atene la base incrocio e' maiuscola ma la deve inserire
						in ogni caso siamo dentro 'libera'
						*/
						if (isupper(p[cnt+h]))
							p[cnt+h]=tolower(p[cnt+h]);


						if(p[cnt+h]==VOC4)
						{
							if(Check2(p[cnt+h])==0xFF)
							{
								//TRACE("\nvoc4 check2 FF");
								break;//p[cnt+h]=0;
							}
						}
						else if(p[cnt+h]>=VOC0 && p[cnt+h]<=VOC11)//venezia:era VOC6
						{
							p[cnt+h]=Check2(p[cnt+h]);
							//TRACE1("\ncheck2=%c",p[cnt+h]);
						}
						else
						{
							chkd=CheckDisp(p[cnt+h]);
							if(chkd==3)
							{
 								casa[y][g].fsc=1;//flag scarabeo
								OutputDebugString("SCARABEO\n");
								//TRACE2("SCARABEO %d %d\n",y,g);
							}
							else if(!chkd)
							{
								OutputDebugString ("chk2O fail\n");
								goto annulla;
							}
						}
						if(!p[cnt+h])
						{
							//TRACE ("\nP=0!");
							goto annulla;
						}


						casa[y][g].flag=TEMPORANEA_PL2;
						casa[y][g].s.lettera=p[cnt+h];
						casa[y][g].s.bitmap=Info_Lettera[p[cnt+h]-'a'].bitmap;
						casa[y][g].s.valore=Info_Lettera[p[cnt+h]-'a'].valore;
					}
				}

			//chiede check validità
				fmi=flag_mostra_idee;
				flag_mostra_idee=TRUE;//questa volta la deve mostrare!!
				AggiornaFinestra();//lettere temporanee

				if(flag_check_validita)
				{

				sprintf(avviso,"%s: %dPt",
				zona_appoggio[n].parola,
				//zona_appoggio[maxiv].index.y+1,
				//'H',
				zona_appoggio[n].value
				);

				int fn=MessageBox(GetActiveWindow(),avviso,"Propendo per..",MB_YESNO|MB_ICONINFORMATION);

				if(fn==IDNO)
				{
					memset(&zona_appoggio[maxiv],0,sizeof(lemmaSTR));
					flag_mostra_idee=fmi;
					Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);
					Annulla_flag_temporanei(ASSENTE);
					nl--;
					goto nextword;
				}
				}
				else
					Sleep(2000);//fa vedere in reverse per due secondi
			//fine check

							flag_mostra_idee=fmi;
			Annulla_flag_temporanei_T(CONSIDERATA,ASSENTE);
				Annulla_flag_temporanei(TEMPORANEA_PL2);
	Parla(&zona_appoggio[n]);
	
				return maxiv;
			}//orizzontale
			//goto novert;
//vert:;
			else if(zona_appoggio[n].hv==VERTICALE)
			{
				//	sprintf(avviso,"VERT");
				//	MessageBox(GetActiveWindow(),avviso,NULL,NULL);

				Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);
				Annulla_flag_temporanei(ASSENTE);
				zona_appoggio[n].hv=VERTICALE;
				for(g=y,h=0;g<y+len-cnt;g++,h++)
				{
					sprintf(avviso,"\n%c=%d\n",casa[g][x].s.lettera,casa[g][x].flag);
					OutputDebugString (avviso);

					if(casa[g][x].flag==PERMANENTE)
					{
					}
					else if(casa[g][x].flag==LIBERA)
					{
						/* va tolto: atene la base incrocio e' maiuscola ma la deve inserire
						in ogni caso siamo dentro 'libera'
						if (isupper(p[cnt+h]))
							goto annulla;
						*/
						if (isupper(p[cnt+h]))
							p[cnt+h]=tolower(p[cnt+h]);

						if(p[cnt+h]==VOC4)
						{
							if(Check2(p[cnt+h])==0xFF)
								break;//p[cnt+h]=0;
						}
						else if(p[cnt+h]>=VOC0 && p[cnt+h]<=VOC11)//venezia:era VOC6
							p[cnt+h]=Check2(p[cnt+h]);
						else
						{
							chkd=CheckDisp(p[cnt+h]);
							if(chkd==3)
							{
								casa[g][x].fsc=1;//flag scarabeo
								OutputDebugString("SCARABEO\n");
							}
							else if(!chkd)
							{
								OutputDebugString ("chk2V fail\n");
								goto annulla;
							}
						}
						if(!p[cnt+h])
							goto annulla;

						casa[g][x].flag=TEMPORANEA_PL2;
						casa[g][x].s.lettera=p[cnt+h];
						casa[g][x].s.bitmap=Info_Lettera[p[cnt+h]-'a'].bitmap;
						casa[g][x].s.valore=Info_Lettera[p[cnt+h]-'a'].valore;
					}
				}

				//chiede check validità
				fmi=flag_mostra_idee;
				flag_mostra_idee=TRUE;//questa volta la deve mostrare!!
				AggiornaFinestra();//lettere temporanee ci vuole


				if(flag_check_validita)
				{
					sprintf(avviso,"%s: %dPt",
					zona_appoggio[n].parola,
					zona_appoggio[n].value
					);

					int fn=MessageBox(GetActiveWindow(),avviso,"Propendo per..",MB_YESNO|MB_ICONINFORMATION);

					if(fn==IDNO)
					{

						memset(&zona_appoggio[maxiv],0,sizeof(lemmaSTR));
						nl--;
						flag_mostra_idee=fmi;
						Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);
						Annulla_flag_temporanei(ASSENTE);
						goto nextword;
					}
				}
				else
					Sleep(2000);//fa vedere in reverse per due secondi

			flag_mostra_idee=fmi;
				//fine check
			Annulla_flag_temporanei_T(CONSIDERATA,ASSENTE);
				Annulla_flag_temporanei(TEMPORANEA_PL2);
				
				Parla(&zona_appoggio[n]);
				
				return maxiv;
			}//verticale
			else
			{
annulla:;
				Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);
				Annulla_flag_temporanei(ASSENTE);

			}


		}



return -1;
}

int BattezzaScarabeo(int y,int x)
{


	HWND hwndGoto = NULL;  // window handle of dialog box

int k;

//    if (!IsWindow(hwndGoto))
 //   {

	k=DialogBox(ghInst,MAKEINTRESOURCE(IDD_DIALOG4),ghWndToolbarDlg,(DLGPROC) GoToProc);
	if(k==FALSE)
		return FALSE;

	memcpy(&casa[y][x].s,&Info_Lettera[scarselect],sizeof(struct saccoSTR));
	AggiornaFinestra();

	return 0;
}

int CPUchkScarab()
{
int x,y,n;
int qsc=0;
//parigi: controlla anche che non ci siano più scarabei del previsto
//(è un trucchetto,bisogna vedere perchè a volte compare uno scarabeo
//nella procedura di scambiatessere
		for (y=0;y<15;y++)
		{
			for (x=0;x<15;x++)
			{
				if(casa[y][x].fsc)
				{
					qsc++;
					if(qsc>Q_SCARABEI)//parigi
					{
						OutputDebugString("\nRILEVATI PIU SCARABEI, fix it!!!");
						casa[y][x].fsc=0;
						continue;
					}
					for(n=0;n<8;n++)
					{
						if(tessera[player][n].s.lettera==casa[y][x].s.lettera)
						{
							casa[y][x].fsc=0;
							memcpy(&tessera[player][n].s,&Info_Lettera[26],sizeof(struct saccoSTR));
							AggiornaFinestra();
							Sleep(1000);
							break;
		}}}}}
		return 0;
}


BOOL CALLBACK GoToProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int a;
	POINT punto;
	POINT Cpoint;

    switch (message)
    {

	case WM_INITDIALOG:

            return TRUE;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDOK:
					EndDialog(hwndDlg, wParam);
					return TRUE;

                case IDCANCEL:
					EndDialog(hwndDlg, wParam);
                    return FALSE;
            }
    	case WM_LBUTTONDOWN:

			GetCursorPos(&punto);
			ScreenToClient(hwndDlg, &punto);

			if(punto.x>iINTV&&punto.x<iLIMX)
			{
				Cpoint.x=(punto.x-iINTV)*5/iMAG1;
			}

			if(punto.y>iINTV&&punto.y<iLIMY)
			{
					Cpoint.y=(punto.y-iINTV)*6/iMAG2;
			}

			if(Cpoint.x>4||Cpoint.y>6)
				return -1;


			if(Cpoint.y<4)
				a=5*Cpoint.y+Cpoint.x;
			else
				a=20+3*(Cpoint.y-4)+Cpoint.x;
			scarselect=a;
			SendMessage(hwndDlg,WM_COMMAND,IDOK,0);

			return TRUE;
			break;

	}

    return FALSE;
}



int ScambiaTessere()
{
int n;
//char avviso[40];
int retry=0;
int cass;
struct tesseraSTR aptessera;

	volatile unsigned long address=(volatile unsigned long)&tessera[0][0];

	cass=0;
	for(n=0;n<8;n++)
	{
		memcpy((void*)&aptessera,(void*)&tessera[PLAYER1][n],sizeof(tesseraSTR));
		memcpy((void*)&tessera[PLAYER1][n],(void*)&tessera[PLAYER2][n],sizeof(tesseraSTR));
		memcpy((void*)&tessera[PLAYER2][n],(void*)&aptessera,sizeof(tesseraSTR));
	}
	Annulla_flag_temporanei_T(CONSIDERATA,PRESENTE);
	return 0;
}

BOOL CALLBACK MoDizProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

static char parola_originale[36];
static char parola_nuova[36];
char temp[36];
char avviso[120];
char*pc;


	switch (message)
   	{

	case WM_INITDIALOG:

		strcpy(parola_originale,(char*)lParam);
/*		if(!isalpha(parola_originale[0]))
		{
			//QUI POTREBBE GESTIRE OPZIONI PARTICOLARI
			EndDialog(hwndDlg, wParam);
			return FALSE;

		}*/
		SetDlgItemText(hwndDlg,IDC_ORIG,parola_originale);

		strcpy(parola_nuova,(char*)lParam);
		pc=strchr(parola_nuova,'-');
		if(pc) *pc=0;
			SetDlgItemText(hwndDlg,IDC_NUOVO,parola_nuova);


CheckDlgButton(
  hwndDlg,      // handle to dialog box
  IDC_INS,  // button identifier
  BST_CHECKED     // check state
);
			break;

    	case WM_COMMAND:
            switch (LOWORD(wParam))
            {
			case IDOK:

				GetDlgItemText(hwndDlg,IDC_NUOVO,parola_nuova,32);

				if(
				IsDlgButtonChecked(hwndDlg,IDC_CAN)
				)
				{
					if(parola_nuova[0])
					{


					int l=strlen(parola_nuova);
					char finale=parola_nuova[l-1];

					if(IsDlgButtonChecked(hwndDlg,IDC_A))
						if(finale!='A')//venezia
						strcat(parola_nuova,"-A");
					if(IsDlgButtonChecked(hwndDlg,IDC_E))
						if(finale!='E')//venezia
						strcat(parola_nuova,"-E");
					if(IsDlgButtonChecked(hwndDlg,IDC_I))
						if(finale!='I')//venezia
						strcat(parola_nuova,"-I");
					if(IsDlgButtonChecked(hwndDlg,IDC_O))
						if(finale!='O')//venezia
						strcat(parola_nuova,"-O");

					sprintf(avviso,"Cancellare %s?",parola_nuova);

					if(MessageBox(GetActiveWindow(),avviso,NULL,MB_YESNO)!=IDYES)
						break;
					EseguiSostituzione(parola_nuova,"");

						//qui deve potare eventuali trattini finali.. sanluca
						int y=strlen(parola_nuova)-1;
						char *pc;
						pc=parola_nuova+y;
						if(*pc>=VOC0 && *pc<=VOC11)
							*pc='?';

						parola_nuova[strlen(parola_nuova)-1]='*';//glasgow3
						SetDlgItemText(ghWndToolbarDlg,IDC_COMBO_SEARCH,parola_nuova);//glasgow3
						SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_BUTTON1,0L);//glasgow3
						EndDialog(hwndDlg, wParam);

					break;


					}
				}
				else if(
				IsDlgButtonChecked(hwndDlg,IDC_INS)
				)
				{

					if(parola_nuova[0])
					{




						int l=strlen(parola_nuova);
						char finale=parola_nuova[l-1];

						if(IsDlgButtonChecked(hwndDlg,IDC_A))
							if(finale!='A')//venezia
							strcat(parola_nuova,"-A");
						if(IsDlgButtonChecked(hwndDlg,IDC_E))
							if(finale!='E')//venezia
							strcat(parola_nuova,"-E");
						if(IsDlgButtonChecked(hwndDlg,IDC_I))
							if(finale!='I')//venezia
							strcat(parola_nuova,"-I");
						if(IsDlgButtonChecked(hwndDlg,IDC_O))
							if(finale!='O')//venezia
							strcat(parola_nuova,"-O");

						sprintf(avviso,"Inserire %s?",parola_nuova);

						if(MessageBox(GetActiveWindow(),avviso,NULL,MB_YESNO)==IDNO)
							break;

						EseguiSostituzione("",parola_nuova);
						//qui deve potare eventuali trattini finali.. sanluca
						int y=strlen(parola_nuova)-1;
						char *pc;
						pc=parola_nuova+y;
						if(*pc>=VOC0 && *pc<=VOC11)
							*pc='?';

						parola_nuova[strlen(parola_nuova)-1]='*';//glasgow3
						SetDlgItemText(ghWndToolbarDlg,IDC_COMBO_SEARCH,parola_nuova);//glasgow3
						SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_BUTTON1,0L);//glasgow3
						EndDialog(hwndDlg, wParam);
					}
					break;
				}
				else if(
				IsDlgButtonChecked(hwndDlg,IDC_SOS)
				)
				{

					if(parola_nuova[0])
					{




						int l=strlen(parola_nuova);
						char finale=parola_nuova[l-1];

						if(IsDlgButtonChecked(hwndDlg,IDC_A))
							if(finale!='A')//venezia
							strcat(parola_nuova,"-A");
						if(IsDlgButtonChecked(hwndDlg,IDC_E))
							if(finale!='E')//venezia
							strcat(parola_nuova,"-E");
						if(IsDlgButtonChecked(hwndDlg,IDC_I))
							if(finale!='I')//venezia
							strcat(parola_nuova,"-I");
						if(IsDlgButtonChecked(hwndDlg,IDC_O))
							if(finale!='O')//venezia
							strcat(parola_nuova,"-O");

							sprintf(avviso,"Sostituire %s con %s?",parola_originale,parola_nuova);

						if(MessageBox(GetActiveWindow(),avviso,NULL,MB_YESNO)==IDNO)
							break;

						EseguiSostituzione(parola_originale,parola_nuova);
						//qui deve potare eventuali trattini finali.. sanluca
						int y=strlen(parola_nuova)-1;
						char *pc;
						pc=parola_nuova+y;
						if(*pc>=VOC0 && *pc<=VOC11)
							*pc='?';

						parola_nuova[strlen(parola_nuova)-1]='*';//glasgow3
						SetDlgItemText(ghWndToolbarDlg,IDC_COMBO_SEARCH,parola_nuova);//glasgow3
						SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_BUTTON1,0L);//glasgow3
						EndDialog(hwndDlg, wParam);
						break;
					}

				}//INS/SOS

			break;
        case IDCANCEL:
			EndDialog(hwndDlg, wParam);
		break;

		}//EOSW!!!

	}

		return FALSE;
}

int AttivaScrittura(char *parolahelp)
{
	POINT Cpo;

	if(MessageBox(ghWndToolbarDlg,parolahelp,"Dovrei inserire..",MB_ICONQUESTION|MB_YESNO)==IDNO)
		return 0;
	SendMessage(ghWndToolbarDlg,WM_COMMAND,(WPARAM)IDC_ANNULLA,0L);

	char *value=strtok(parolahelp," ");
	char *word=strtok(NULL,"* ");
	char *pos=strtok(NULL,"");

	int lp=strlen(pos);

	Cpo.y=*(pos+lp-3)-0x31;
	if(Cpo.y>9)
		Cpo.y-=7;
	Cpo.x=*(pos+lp-2)-0x31;
	if(Cpo.x>9)
		Cpo.x-=7;

	while(*word)
	{


		switch (casa[Cpo.y][Cpo.x].flag)
		{
		case PERMANENTE:
			break;
		case LIBERA:
			int n;
			for(n=0;n<8;n++)
			{
				if(tessera[PLAYER1][n].flag==PRESENTE)
					if(toupper(tessera[PLAYER1][n].s.lettera)==*word)
						break;
			}
			if(n>=8)//non trovata: e' uno scarabeo
			{
				for(n=0;n<8;n++)
				{
					if(tessera[PLAYER1][n].flag==PRESENTE)
						if(toupper(tessera[PLAYER1][n].s.lettera)==SCARABEO)
							break;
				}
			}
			DeponiLettera(PLAYER1,Cpo,(BYTE)n);

			tessera[PLAYER1][n].flag=ASSENTE;
			Mostra_tessere(0);
			break;
		}
		word++;
	if(*(pos+lp-4)=='H')
		Cpo.x++;
	else
		Cpo.y++;
	}
	return 0;
}

int Parla(struct lemmaSTR* zap)
{
	return 0;
}

int ParlaS(char* frase)
{
return 0;
}


void Annulla_flag_temporanei_T(BYTE da,BYTE a)
{

	int x,y;
	for (y=0;y<2;y++)
	{
		if(da==ASSENTE && player!=y)
			continue;//parigi
		for (x=0;x<8;x++)
		{

			if (tessera[y][x].flag==da)
				if(tessera[y][x].s.lettera)//non annulla le assenti vere!
					tessera[y][x].flag=a;
		}
	}

}
