#pragma once
#define _WIN32_IE 0x500
#include <tchar.h>
#include "Shellapi.h"
#ifndef ASSERT
#include <assert.h>
#define ASSERT assert
#endif

#define NIF_INFO  0x00000010
#define NIIF_INFO 0x00000001
#include "RESOURCE.h"



/* 
UTILIZZARE IN QUESTO MODO
  MessageBalloon mb("Quitting..", "Myapp",NIIF_WARNING);
*/
 
 
 
struct MessageBalloon : public NOTIFYICONDATA
{
 MessageBalloon(LPCTSTR _szInfo = _T("Prompt"), LPCTSTR _szInfoTitle = 0, DWORD myInfoFlags = NIIF_INFO, HICON _hIcon = 0, LPCTSTR _szTip = 0)
 {

	 		DWORD dwInfoFlags;
		
		char szInfoTitle[1000]={"ScaraBIT"};
		char szInfo[1000]={"ScaraBInfo"};;

	 ASSERT(_szInfo);
  static struct wnd_holder{
   HWND hwnd_;
   wnd_holder(){
   // hwnd_ = CreateWindowW(0L,"STATIC", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
   hwnd_ = CreateWindowEx(
     0L,      // extended window style
     "STATIC",  // registered class name
     "", // window name
     0,        // window style
     0,                // horizontal position of window
     0,                // vertical position of window
     0,           // window width
     0,          // window height
     (HWND) NULL,      // handle to parent or owner window
     (HMENU) NULL,          // menu handle or child identifier
     (HINSTANCE) NULL,  // handle to application instance
     NULL        // window-creation data
   );
   
   
   }
   ~wnd_holder(){DestroyWindow(hwnd_);}
  } wh;
  
  memset(this, 0, sizeof(*this));
  cbSize = sizeof(*this);
  hWnd = wh.hwnd_;
  hIcon = _hIcon ? _hIcon : ::LoadIcon(::GetModuleHandle(NULL),MAKEINTRESOURCE(128/*IDR_MAINFRAME*/));
  if (! hIcon) hIcon = ::LoadIcon(NULL, IDI_INFORMATION);
  // if 'NIF_INFO' is an undeclared identifier, define _WIN32_IE 0x500 at the very beginning
  uFlags = NIF_INFO | NIF_TIP | NIF_ICON; 
  dwInfoFlags = myInfoFlags;//;NIIF_INFO;//NIIF_ERROR;//NIIF_WARNING;
  _tcscpy(szInfo, _szInfo);
  if (! _szInfoTitle) LoadString(::GetModuleHandle(NULL), 57344/*AFX_IDS_APP_TITLE*/, szInfoTitle, sizeof(szInfoTitle));
  else _tcscpy(szInfoTitle, _szInfoTitle);
  _tcscpy(szTip, _szTip ? _szTip : szInfoTitle);
 
  Shell_NotifyIcon(NIM_ADD, this);
 }
 
 ~MessageBalloon(){Shell_NotifyIcon(NIM_DELETE, this);}
};
#if 0
struct MessageBalloon : public NOTIFYICONDATA
{
	MessageBalloon(LPCTSTR _szInfo = _T("Prompt"), LPCTSTR _szInfoTitle = 0, LPCTSTR _szTip = 0, HICON _hIcon = 0)
	{
		DWORD dwInfoFlags;
		
		char szInfoTitle[1000]={"ScaraBIT"};
		char szInfo[1000]={"ScaraBInfo"};;
		
		
		

		ASSERT(_szInfo);
		static struct wnd_holder{
			HWND hwnd_;
			
			wnd_holder(){
				//hwnd_ = CreateWindowW(0L,1,NULL, 0, 0, 0, 0, 0, 0, 0, 0);
				hwnd_ = CreateWindowEx( 
				0,                      // no extended styles           
				"STATIC",           // class name                   
				0,          // window name                  
				0,
				0,          // default horizontal position  
				0,          // default vertical position    
				0,          // default width                
				0,          // default height               
				(HWND) NULL,            // no parent or owner window    
				(HMENU) NULL,           // class menu used              
				NULL,              // instance handle              
				NULL);                  // no window creation data   
						}
			~wnd_holder(){DestroyWindow(hwnd_);}
		} wh;
		
		memset(this, 0, sizeof(*this));
		cbSize = sizeof(*this);
		hWnd = wh.hwnd_;
	//	hIcon = _hIcon ? _hIcon : ::LoadIcon(::GetModuleHandle(NULL),MAKEINTRESOURCE(128/*IDR_MAINFRAME*/));
			hIcon = _hIcon ? _hIcon : ::LoadIcon(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_APP));
		if (! hIcon) hIcon = ::LoadIcon(NULL, IDI_INFORMATION);
		// if 'NIF_INFO' is an undeclared identifier, define _WIN32_IE 0x500 at the very beginning
		uFlags = NIF_INFO | NIF_TIP | NIF_ICON; 
		dwInfoFlags = NIIF_INFO;
		_tcscpy(szInfo, _szInfo);
		if (! _szInfoTitle) 
			LoadString(::GetModuleHandle(NULL), 57344/*AFX_IDS_APP_TITLE*/, szInfoTitle, sizeof(szInfoTitle));
		else 
			_tcscpy(szInfoTitle, _szInfoTitle);
		_tcscpy(szTip, _szTip ? _szTip : szInfoTitle);

		Shell_NotifyIcon(NIM_ADD, this);



		#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

		NOTIFYICONDATA IconData = {0};

		IconData.cbSize = sizeof(IconData);
		IconData.hWnd = hWnd;
		IconData.uFlags = NIF_INFO;

		lstrcpyn(IconData.szTip, TEXT("Your message text goes here."), 
				 ARRAYSIZE(IconData.szTip));
//		IconData.uTimeout = 15000; // in milliseconds
 
		Shell_NotifyIcon(NIM_MODIFY, &IconData);

	}
	
	~MessageBalloon(){Shell_NotifyIcon(NIM_DELETE, this);}
};
#endif