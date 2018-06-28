
#ifndef INIZIO_ESPORTAZIONE_TTS
#define INIZIO_ESPORTAZIONE_TTS


#include <io.h>
#include <STDio.h>
#include "ttsinc\\ttsso_types.h"
#include "ttsinc\\lh_ttsso.h"
#include "Mmsystem.h"
#include "Mmreg.h"


	HINSTANCE m_hDxxApi32;
	HINSTANCE m_hSrlApi32;
	HINSTANCE m_hTTSApi32;
	TTSRETVAL (* m_lpf_TtsInitialize)( HTTSINSTANCE *,LH_SDK_SERVER*,TTSPARM*, VOID* );
	TTSRETVAL (* m_lpf_TtsProcess)( HTTSINSTANCE );
	TTSRETVAL (* m_lpf_TtsUninitialize)( HTTSINSTANCE );
	TTSRETVAL (* m_lpf_TtsSetParam)(HTTSINSTANCE,unsigned short,unsigned short);

	void CALLBACK waveOutProc(
  HWAVEOUT hwo,      
  UINT uMsg,         
  DWORD dwInstance,  
  DWORD dwParam1,    
  DWORD dwParam2     
);

	HANDLE		evAudioFree;
	HWAVEOUT	wo;

//#define TTS_DIRECTORY	"C:\\programmi\\lhSP\\Telecom Realspeak\\engine"
#define TTS_DIRECTORY	".\\engine"
#define OUTBUFSIZE      2048
#define NAMESIZE        256
#define SRC_FILE		"A"
#define DST_FILE		"B"
enum cmdspk
{
	SPK_STOP, //default:stop bloccante
	SPK_GO //non bloccante
};




/*struct that contains file pointers to the input text file and the output PCM file*/
typedef struct
{
	FILE *fpText;
	FILE *fpPCM;
} APPDATA;

CHAR        outputBuffer[OUTBUFSIZE];

/* Send data to text to speech */
int TTS(char *inputfile,char *outputfile,unsigned short OutputType);
int TTS2(char *inputfile,char *outputfile,unsigned short OutputType);
//int ChiudiAudio();
int LeggiAudio(char *outputfile,int frq=8000);

int SpkEngine(
                     LPSTR     lpCmdLine,
                     int       nCmdShow);


/*
	TTSRETVAL       RetVal;
    HTTSINSTANCE    hInst1;
    TTSPARM         Parm;
    VOID            *lpAppData = NULL;
	APPDATA			appdata;
	CHAR            szDirectory[256];
*/
//FINE ESPORTAZIONE TTS
#endif