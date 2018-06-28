#ifndef VAI_A_FARTI_FOTTERE
#define VAI_A_FARTI_FOTTERE
#include "windows.h"
/*
13/8/02: correzione: il timer all'inizio permetteva si di vedere
il piano di gioco subito, ma faceva schiantare WINNT e WIN95
percio' l'ho tolto e adesso siamo compatibili (TESTATO SU WINNT) label PRAGA

 
notato errore madornale: se compongo una sigla provincia mi da molti punti
in più(forse quelli della parola incrociata???): corretto si trattava di
aggiungiextra : label lampedusa

*/

/*
20062002 modifiche per nuova gestione gruppi 2 lettere nella versione: codice ROMA
26062002 correzione: non calcola o controlla inserimento parola biletterale da utente : MADRID
29062002 correzione: help me deve prima annullare i flag temporanei ZARA
*/

/*
  DA FARE
  VERSIONE INGLESE
  PROTEZIONE CON CHIAVE DI REGISTRO
Bachi al 20/8/2002

il cpu passa la mano senza provare con le province

una lettera permanente sull'ultima colonna spariva inesorabilmete se cliccata
ERRORE CORRETTO DA VIENNA

qualche dubbio sul calcolo dei punti in incroci plurimi

una lettera durante il posizionamento è finita sotto lo schema (a coord. 0,0?) forse
cliccando fra tavolo gioco e portatessere

..forse la tecnica di ricerca del cpu dovrebbe essere cambiata: 
adesso parte dalle tre lettere
e poi via via aumenta: dovrebbe partire dalle 15 e poi scendere fino a N livelli sotto la
parola più lunga trovata ad es, se trova una parola di 8 lettere cerca anche quelle di 7,
di 6 e poi sceglie quella migliore.: è un'altra strategia che non dovrebbe però sostituire
l'attuale ma andare ad aggiungersi-.(config?)
PROVATO, MA SI ALLUNGANO I TEMPI RICERCA + altri problemi

Le modifiche di PRAGA sono necessarie se ambiente WIN95/NT: il timer non sembra funzionare
bene (eccezione): invece è OK su WIN2k

Cosa succede se il computer utilizza caratteri GRANDI o PERSONALIZZATI? i dialoghi
cambiano dimensione ma i bitmap no..... RISOLTO DA CEFALU

Lo scarabeo ha lo stesso colore delle lettere temporanee del computer: RISOLTO LERICI

BACO AL 26/8/2002
spesso si ripresenta il solito problema grafico, se MOSTRA IDEE selezionato: 
ad un certo punto
tutte le lettere diventano uguali: il programma non va in abend ma la parte grafica
quella si. bisogna salvare e ripartire. credo che sia dovuto al fatto che per ogni parola
ridisegna tutto lo schermo. occorre intervenire.
ANKARA ci ha provato ma ha fallito: anche xche in ogni caso: lo schermo deve essere aggiornato 
anche per la cancellazione della parola precedente; le tessere devono essere aggiornate e così
la editbox: tabto vale fare tutto...
ANKARA2 : aumenta il ritardo.. MA NON SERVE

*/

#define TIMER1		1

/* label modifica giornaliere */
#define ROMA 21062002
#define PARIGI 22062002
#define MALINDI 24062002 //corregge bacaccio che cancellava la prima parte della zona_appoggio
#define MADRID 26062002 //conteggio biletterali
#define VENEZIA 26062002//nuovo dialogo aggiornamento dizionario
#define LAMPEDUSA 13082002//corregge errore su aggiunta extra a biletterali
#define ATENE	14082002//corregge un sacco di errori di VENEZIA, 
//grosse modifiche a tutto.. e nessuna label!!!
//Procedura dizionario: adesso è facile
//Nuovi tasti
//Avvisi in finestra
//salvataggio file temporaneo e procedura di rifiuto
//avvisi utente modificati
//INTRODOTTO UN ERRORE? ANALYSYSENGINE SBAGLIA LA RICERCA SULLA VOC4 
//(raddoppia le i)!!!!!!!!
#define VIENNA	24082002//corregge baco cancellazione permanente
#define MOSCA	24082002//alterna ricerca verticale a orizzontale
#define BERNA	25082002//forse corregge baco raddoppio delle i su VOC4
#define CEFALU	25082002//correzioni per supportare anche sistemi con font grandi
//o personalizzati:tutte le bitblt sostituite da stretchblt.
#define LERICI  26082002 //sfondo giallo per scarabeo
#define JAKARTA 30082002 //corregge errore non deallocazione GDI
#define SIENA	30082002 //sfondo colorato per lettere temporanee
#define OSLO	06092002 //gruppi biletterali letti da file	+ KRYPT
//#define LUBECK	06092002 //scrittura del registro per distribuzione
#define LUCCA	20092002 //aggiorna + la finestra.leva krypt pare avesse prob su Windows XP
							//lucca2 aggiorna subito list box dopo mod.dizionario
#define SANLUCA  01032003 //in ospedale: modifica per wildcards ricerca
#define CALCUTTA 01032003 //in ospedale: inserimento biletterali
#define OSAKA    02032003 //rotazione tabella
#define TODI	 07032003 //ricerca parole (estesa e corretta) 

#define GLASGOW  03082003  //flag per non ridare le messagebox (annullato), 
							//aggiornamento finestra dopo assegnazione tessere player 1
							//richiesta conferma su chiusura
							//modifica dizionario anche su lista computer
							//aggiornamento lista dopo inserimento glasgow3
 
/*
da fare:
			verificare perche' incremento memoria utilizzata su ricerca (task manager)
			migliorare partenza computer (ancona)
			migliorare disposizione tessere

  modifiche da fare  24/9/2003
    
	non deve chiedere due volte di selezionare la parola per modificare (non sono sicuro che si possa fare
	visto che la lista può essere lunga..)
	
	  la listbo deve scorrere!


*/

#define SANTIAGO  24092003 //se flag cpu conferma, chiedere prima di cambiare le tessere.
							//e di cominciare
#define BAHIA	  24092003 //dopo salvare? non deve chiudere
//LAPAZ annulla bahia

//#define VALPARAISO 24092003 //scorrimento automatico lista NON FUNZIONA

#define CATANIA		09102003 //cambio grafica tavola con scorrimento fra 4 possibili (ruota)


#define ENNA 12102003//RILEVA  CRASH IN CHIUSURA DOPO CHE PLAYER1 HA FINITO
//LE TESSERE CHIEDE SALVARE? POI DOPO L'OPERAZIONE SI BLOCCA TUTTO


#define TROMSOE 13052004 //se definito i gruppi biletterali non sono ammessi
//andrebbe trasformato in opzione utente!!

#define HAMMERFEST 13052004 //gestione modalità demo vedi Global_Demox
#define BERGEN 13052004 //abbassa delay vedi FIATA



/*
------------------------------------------------------------------------------------
problemi RILEVATI
schermo che sparisce (GDI)
selezione lettere non efficace e con bachetto (tessera va su)
tasti non letti durante elaborazione..
------------------------------------------------------------------------------------
  migliorie
trasformare la editbox del cerca in combo in modo da poter richiamare vecchie chiavi

------------------------------------------------------------------------------------

*/
#define LUXOR 15052004 /*
ADATTATE LE LETTERE ALLE PERCENTUALI DEL VOCABOLARIO
con questa versione si gestisce correttamente italiano,inglese e modalità demo.
se si cambia lingua in compilazione compilare 2 volte (vedi prebuild dove aggiorna i bitmap)
nelle opzioni di compilazione (defines) specificare ITALIA per compilare in italiano
ambedue le versioni hanno 127 lettere + 1 scarabeo: la frequenza lettere 
ed il valore delle stesse sono diversi fra le due lingue.
modificato Initstructz (inits.cpp) e scarabeo.h
*/

#define OKINAWA 16052004//prova a trasformare wm_supercomputer in un thread
/*in modo da continuare a gestire i messaggi della wnd
FUNZIONA!! ma bisgona disabilitare i bottoni che non si puo usare..
*/

#define ELPASO 20062004
/*
nella ricerca parole aggiung la sintassi -(lettere) in modo che filtri la
list box togliendo le parole che contengono queste: tale opzione puo non essere
reversibile (tanto qelle lettere non le avro mai)
*/

#define MEMPHIS 30112004 //raddoppia valore prima lettera


#define MAZARA	02012005 //buon anno. corregge errore di elpaso



#define FALLUJA 04032005 //L'AIUTO NON DIMEZZA SE PRECEDENTEMENTE AVEVI CALCOLATO UN PUNTEGGIO MAGGIORE

/*ci sono dei bachi:
1) bisogna che falluja valga solo se la parola inserita e' già nel dizionario
altrimenti e' facile fregare inserendo una parola inesistente

2)rispondendo no su aggiunta al dizionario, conferma la parola inserita e passa il turno
al computer (nassirya corregge)

*/
#define NASSIRYA 13072005

#define OKKAIDO 15082005//aggiunge dorso tessere e nuova board

#define KYOTO  02022006
/*
ci sono vari problemi ancora
scarabeo che sparisce
baco su ruota in alcune condizioni
raddoppio prima parola OK
VERIFICARE PUNTEGGI SU VERSIONE INGLESE

migliorie
gioco a tempo
gioco in rete
customizzazione tessere: potrebbe leggere da un INI
deve gestire una combo per le ricerche, che si ricordi le precedenti

FINE BRUSCA
TRASCINAMENTO TESSERE da migliorare


*/

#define BERLINOEST 08142006 //corregge baco su ricerca parole al bordo destro o basso:


//#define NARNI	 03102007 
/*
				qui controlla se ha aggiunto una sola lettera: in questo caso
				bisogna che oltre a calcolare normalmente tenga conto quando
				passa alle orizzontali (o viceversa) che questa lettera pu' essere
				usata come base 

*/
//#define LIONE	 03112007 //narni e' fallito. tutto da rifare


#define TUNISI	31102008 
/*
ripristina le biletterali. commentato tromsoe

cassa la procedura lione. il controllo delle perpendicolari funziona
ma ci sono problemi di grafica dopo un po (punteggi sparissìcono ecc..)
da rivedere con calma

cerco di migliorare la chiusura di partita:
la regola dice che 

1)quando un giocatore finisce le tessere in condizione
di sacco vuoto la partita e' finita e si prende i punti dell'avversario
(quanto vale lo scarabeo?)
2)
se ambedue passano e' finita cosi'

modificata allocazione heap in modo da metterci anche i gruppi di due lettere
forse non serve memgrbil a questo punto

rivedere la fine gioco


label 2013 quando controlla perpendicolari mostra la tessera inserita
(in quanto viene marcata come permanente) 

*/
//#undef ROMA// 19/2/12


int poipoipoi(
    HWND hWnd ,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT uType);

#define MessageBox poipoipoi


#define FILE_VOCABOLARIO_IT	"scarabeo.voc.it"
#define FILE_VOCABOLARIO_EN	"scarabeo.voc.en"
#define FILE_CRYPT			"scarabok.voc"
#define FILE_BILET			"2LT.voc"

#define RITIRA_INSERIMENTO	2727

#define HELP_IS_FOREVER	185
#define HELP_IS_ON	183
#define HELP_IS_OFF	0


#define ENGINE2

#define PLAYER1	0
#define PLAYER2	1
#define BASEX		12
#define BASEY		12
#define DIMBOARD	468
#define DISTANZA_TESSERE 279

//#define KRYPTER	
#define KRYPT	77
#define DEKRYPT	78

#define YTESSERA 490
#define XTESSERA 12
#define DIMTESSERA 32
#define NUM_LEMMI 16

//coord. per punteggi e sacco
#define XMAN1	498
#define XMAC1	XMAN1+82//585
#define YPUNTO	11
#define DIMXCIFRA	24
#define DIMYCIFRA	38
#define DISTACCO	24	
#define XMAS1		XMAC1
#define YSUNTO		485

//per scambio scarabeo (DIALOG4)
#define INTV 10			
#define LIMX 175
#define LIMY 213
#define MAG1 165
#define MAG2 203


//per ricerche
#define DIM_BUFFER_RICERCA	0x2000



#define NOT_SELECTED	0xFF

#define ORIZZONTALE 1
#define VERTICALE 2

//per le case (flag)
#define LIBERA			0
#define PERMANENTE		0xFF
#define TEMPORANEA_PL1	1
#define TEMPORANEA_PL2	2
#define BASE_INCROCIO	3//pisa

#define VIETATA			0xBB
//.. altri possono essere aggiunti..	

#define SCARABEO '@'

#define VOC0	'0'
#define VOC1	'1'
#define VOC2	'2'
#define VOC3	'3'
#define VOC4	'4'
#define VOC5	'5'
#define VOC6	'6'

#define VOC7	'7'//venezia 
#define VOC8	'8'//venezia
#define VOC9	'9'//venezia
#define VOC10	':'//venezia deve seguire lista ascii
#define VOC11	';'//venezia deve seguire lista ascii


/*
lettera		disp.	valore		presenze	in alfabeto
A				6	 	1		34476
I				6  		1		32246
O				6	 	1		28881
E				6 	 	1		28864
R				6	 	1		25131
T				6	 	1		21665

N				5	 	2		17673
S				5	 	2		16128
C				5	 	2		14691
L				5	 	2		12460

M				4  		3		8479
P				4	 	3		7656
G				4	 	3		6623
U				4	 	3		6569

D				3	 	5		5880
Z			 	3	 	5		4753
B				3	 	5		4215
F				3	 	5		4131

V				3	 	8		3809
H				2	 	8		1204

Q				2	  	10		493
K				1	 	10		73		
X		 		1		10		45
Y		 		1		10 		42
W		  		1		10		30
J				1	 	10		21

consideriamo 225 lettere totali?
classe 6	: (20) 120 30=180           
classe 5	: (12)	48	
classe 4	: (8)	32
classe 3	: (5)	25
classe 2	: (2)	4
classe 1	: (1)	5

sono un po' di più ma va bene..
*/

/*

#define A	1		//1
#define E	1		//1
#define I	1		//1
#define O	1		//1

#define N0	4
#define Q0	15				//15*4=60

#define R	1		//1
#define T	1		//1
#define C	1		//1

#define N1	3
#define Q1	10				//10*3=30

#define L	2		//2
#define M	2		//2
#define N	2		//2
#define P	2		//2
#define S	2		//2

#define N2	5
#define Q2	6				//8*5=40

#define B	4		//4
#define D	4		//4
#define F	4		//4
#define G	4		//4
#define U	4		//4
#define V	4		//4

#define N4	6
#define Q4	4			//6*6=36

#define H	8		//8
#define Z	8		//8

#define N8	2
#define Q8	2			//2*3=6

#define K	10		//10
#define J	10		//10
#define Q	10		//10
#define W	10		//10
#define X	10		//10
#define Y	10		//10

#define N10	6
#define Q10	1			//1*6=6	

#define Q_SCARABEI	1







//TESSERE VERSIONE ITALIA (12*4+7*4+6*3+4*7+2*2+1)+2=48+28+18+28+4+1+2=

#define A	1		//1
#define E	1		//1
#define I	1		//1
#define O	1		//1

#define N0	4
#define Q0	12				//15*4=60

#define R	1		//1
#define T	1		//1
#define C	1		//1
#define S	1		//2

#define N1	4
#define Q1	7				//10*3=30

#define L	2		//2
#define M	2		//2
#define N	2		//2

#define N2	3
#define Q2	6				//8*5=40


#define B	4		//4
#define D	4		//4
#define F	4		//4
#define G	4		//4
#define P	4		//2
#define U	4		//4
#define V	4		//4

#define N4	7
#define Q4	4			//6*6=36


#define H	8		//8
#define Z	8		//8

#define N8	2
#define Q8	2			//2*3=6

#define Q	10		//10

#define N10	1
#define Q10	1			//1*6=6	

#define W	10		//10
#define X	10		//10
#define Y	10		//10
#define K	10		//10
#define J	10		//10

*/
#ifdef ITALIA
#define A	1		//1
#define E	1		//1
#define I	1		//1
#define O	1		//1
#define R	1		//1
#define T	1		//1

#define N	2		//2
#define C	2		//1
#define S	2		//2
#define L	2		//2

#define M	3		//2
#define P	3		//2
#define G	3		//4
#define U	3		//4

#define D	5		//4
#define Z	5		//8 caorle
#define B	5		//4
#define F	5		//4
#define V	5		//8->6 caorle

#define H	8

#define Q	10		//10
#define W	10		//10
#define X	10		//10
#define Y	10		//10
#define K	10		//10
#define J	10		//10

#define QA	12		//1
#define QE	12		//1
#define QI	12		//-3
#define QO	12		//+2
#define QR	9		//1
#define QT	9		//1
#define QN	7		//2
#define QC	7		//1
#define QS	7		//2
#define QL	7		//2
#define QM	4	//2
#define QP	4	//2
#define QG	4		//4
#define QU	4		//4
#define QD	3		//4
#define QZ	3		//8
#define QB	3	//4
#define QF	3	//4
#define QV	2		//4
#define QH	2		//+1
#define QQ	1		//10

/*
//tabella ricalcolata da berlinoest: troppe vocali
#define QA 15
#define QB 2 
#define QC 6 
#define QD 2 
#define QE 15
#define QF 2 
#define QG 3 
#define QH 1 
#define QI 19
#define QL 5 
#define QM 3 
#define QN 7 
#define QO 12
#define QP 3 
#define QQ 1 
#define QR 10
#define QS 7 
#define QT 9 
#define QU 3 
#define QV 2 
#define QZ 2 
*/

#define QW	0		//10
#define QX	0		//10
#define QY	0		//10
#define QK	0		//10
#define QJ	0		//10
#else
#define A	1		//1
#define E	1		//1
#define I	1		//1
#define O	1		//1
#define R	1		//1
#define T	1		//1
#define N	1		//2
#define S	1		//2
#define C	2		//1
#define L	2		//2
#define M	2		//2
#define P	2		//2
#define U	2		//4
#define D	2		//4
#define H	2
#define G	2		//4
#define B	4		//4
#define F	4		//4
#define W	4 		//10
#define Y	4 		//10
#define K	8		//10
#define V	8		//4
#define Z	10		//8
#define Q	10		//10
#define X	10		//10
#define J	10		//10

#define QA	10		//1
#define QE	15		//1
#define QI	10		//1
#define QO	8		//1
#define QR	8		//1
#define QT	8		//1
#define QN	8		//2
#define QS	6		//2
#define QL	6		//2
#define QC	5		//1
#define QM	4		//2
#define QP	4		//2
#define QG	4		//4
#define QU	4		//4
#define QH	4
#define QD	4		//4
#define QB	3		//4
#define QF	3		//4
#define QY	3		//10
#define QV	2		//4
#define QW	2		//10
#define QK	2		//10
#define QX	1		//10
#define QJ	1		//10
#define QZ	1		//8
#define QQ	1		//10
#endif

#define Q_SCARABEI	1
#define LUNGHEZZA_MINIMA 2
//#define NUM_PROVINCIE 255//OSLO comm 98

#define VAL_SCARA	99

#define NUM_TESSERE			128//(Q0*N0+Q1*N1+Q2*N2+Q4*N4+Q8*N8+Q10*N10+Q_SCARABEI)
#ifdef ITALIA
#define LETTERE_ALFABETO	21//(Q0+Q1+Q2+Q4+Q8+Q10)
#else
#define LETTERE_ALFABETO	26//(Q0+Q1+Q2+Q4+Q8+Q10)
#endif
#define Q_LETTERE_ALFABETO_COMPLETE		26 /*SEMPRE 26 INDIPENDENTEMENTE DALLA LINGUA*/
#define Q_TIPI_JOLLY					1  /*TIPI DI SCARABEO: SEMpRE 1*/
#define WM_SUPERCOMPUTER WM_USER+1

//per le tessere
#define ASSENTE		0
#define PRESENTE	0xFF
#define CONSIDERATA	1

#define WM_KEYEND		0x997
#define WM_KEYFOUND		0x998
#define WM_FINDKEYS		0x999
//
// window coords
//
#define MAXXWINDOW         100
#define MAXYWINDOW         90
#define STARTXWINDOW        80
#define STARTYWINDOW        70
/*
#define Q_6		30
#define Q_5		12
#define Q_4		8
#define Q_3		5
#define Q_2		2
#define Q_1		1
*/

struct saccoSTR
{
	unsigned bitmap;
	char lettera;
	BYTE valore;
	short reserved;//parigi
};

struct tesseraSTR
{
	struct saccoSTR s;
	unsigned		x;//coordinate
	unsigned		y;
	BYTE			pos;//posizione nel portatessere
	BYTE			flag;
	short reserved;//parigi
};

struct casaSTR
{
	//ogni casella conosce queste informazioni:
	
	int y;//posizione video
	int x;//posizione video
	
	unsigned obitmap;//disegno casella a vuoto
	struct saccoSTR s;
	//char lettera;//'A' 'Z' oppure 0
	//unsigned bitmap;//disegno casella
	//BYTE vlettera; //1 2 3 5 8 10 valore lettera
	BYTE vcasa;//1->5	valore casa
	BYTE flag;//0=assente FF=stabile 1=player1(temp) 2=player2(temp)
	//quando si appoggia una lettera il flag è 1 o 2:
	//dopo la conferma diventa FF
	BYTE fsc;//1=SCARABEO
	BYTE flag_perp;
	BYTE reserved;
};





struct lemmaSTR// per il controllo e assegnazione punti
{
	/*
	dopo l'inserimento qui vengono tenuti tutti i lemmi
	*/
	char parola[32];			//'abetaia'
	unsigned short value;	// 142
	POINT index;			//posizione partenza nella matrice
	BYTE  hv;					//1=orizzontale, 2 verticale
	BYTE  len;//lunghezza parola
	BYTE  dizionario;//flag che indica se la parola è nel dizioanrio
	BYTE  qsc;//quanti scarabei?
};
//BYTE  dizionario;//flag che indica se la parola è nel dizioanrio
#define DONT_KNOW		0 //mah?
#define NOT_IN_DIR		1 //non c'è
#define VOC_FIN_DIFF	2  //se  c'è ma termina per E anzichè I ecc..
#define IN_DIR			3 //c'è

struct playerSTR
{
	unsigned short punti;
	BYTE cpu;		
	BYTE reserved;
};

struct gperpend
{
	int count;
	struct lemmaSTR dati[64];
};


//MAIN
BOOL InitializeApp(HINSTANCE hInst, int nShowCmd);
int WINAPI MTTTYWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL controllo_laterale(BYTE hv,int y,int x,int l,int i);
BOOL ControLL(BYTE hv,int y,int x);

//ERROR
void ErrorReporter(char * szMessage);
DWORD ErrorExtender(DWORD, char **);
int salva(int tmp=0);
int ripristina(int tmp=0);
//LemmiMacìhine
BOOL HeapInit(void);
int FindKeys(char *);
int Find_in_Diz(char *psk,int counter);
int Check_in_Diz(struct lemmaSTR *lem,int nlem);
int SuperEngine(int);

int Analysis_Engine(char*,POINT,BYTE,BYTE,int*);
int CheckPerpendicolare(int,int*);
int MemPerpendicolare(int last);
#ifdef VERSIONEOK
Analysis_Engine(char*,POINT,BYTE,BYTE,int);
CheckPerpendicolare(int);//lione
#endif

#define SEPARATORE	","
#define LZA	16000
int Aggiorna_Flag(BYTE,struct lemmaSTR*);
int CheckDisp(char c);
int Check2(char c);
int GetIndexCasa(POINT,LPPOINT);//non torna coord ma indici
void Annulla_flag_temporanei(BYTE);
void Annulla_flag_temporanei_T(BYTE,BYTE);
int sostituzione_automatica(BYTE,POINT,BYTE);//anche cancellazione
int is_legal(struct lemmaSTR *);
int	InitStructz();
int GetIndexTessera(BYTE,BYTE,POINT);
int Assegna_tessere(BYTE);
int Mescola();
int Mostra_Lemmi(int nl,HWND hdlg);
int GetInfoLettera(struct saccoSTR*);
//grafica
int MostraCase();
int DeponiLettera(BYTE,POINT,BYTE);
int DeponiPrimaLettera(BYTE,POINT,BYTE);
int CancellaTessera(BYTE,BYTE);
void Mostra_punti(HWND);
int SelezionaTessera(BYTE,int);
//int Mostra_tessere(BYTE,BYTE);
int Mostra_tessere(int FaseHelp=0);
int Mostra_tessere_davvero(int FaseHelp=0);
int	ShowLogo();
int Controlla_Inserimento(struct lemmaSTR *);
void AggiornaFinestra();
int Trovaparola(struct lemmaSTR *pl);
int AggiungiExtra();
int MettiUnaLetteraACaso();
int AggiungiAlDizionario(char*);
TIMERPROC OnTimer();//praga comm
void crcgen();
int crypt(HANDLE fileIn,HANDLE fileOut);
int maincrypt(int);
int LeggiVocabolario();
int BattezzaScarabeo(int y,int x);
int CPUchkScarab();
BOOL CALLBACK GoToProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK MoDizProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);
int AggF(byte hv,int y,int x,int len);
int ScambiaTessere();
BOOL EseguiSostituzione(char *por,char *pnu);
void Orizzontali(int min_len,int*,POINT p);//,BOOL single=FALSE);
void Verticali(int min_len,int*,POINT p);//,BOOL single=FALSE);
int MemGrBil();//oslo
int CheckRegister();//LUBECK
int Install();//LUBECK prova!!
int ConvertWildcards(char*chiara,char*standard);//SANLUCA
int InserisciBiletterale(char*);//calcutta
void Ruota();//osaka
void GetRapportoXY(float*rx,float*ry);//cefalu2
int AttivaScrittura(char *parolahelp);
int Parla(struct lemmaSTR *);
int ParlaS(char* frase);
int FiltraListBox(char* m);//elpaso
BOOL ControLLN(struct lemmaSTR* pappo);
int MessaggioFinale();

int LeggiParolaInFormazione(POINT p);
int Init_TTS();
char IsValid(POINT p);
void faite();
int Assegna_punti(int player,int value);
int Mostra_sacco();//EFESO
int Mescola_tessere();
BOOL Is_Biletterale(char*parola);
int AggiungiMessaggio(HWND hdlg,char* avviso);
void DoPerp(int *totpar);

#define SEPARATURNI "------------------------------------------\r\n"

//#define SEPARATURNI_C "----------- MACCHINA -----------\r\n"
//efine SEPARATURNI_U "PREGO E' IL SUO TURNO\r\n"
//#define SEPARATURNI_U "-------------- UOMO  --------------\r\n"


#endif//VAI_A_FARTI_FOTTERE