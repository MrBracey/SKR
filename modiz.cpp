// modiz.cpp : implementation file
//

#include "scarabeo.h"
#include "modiz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// modiz dialog


modiz::modiz(CWnd* pParent /*=NULL*/)
	: CDialog(modiz::IDD, pParent)
{
	//{{AFX_DATA_INIT(modiz)
	//}}AFX_DATA_INIT
}


void modiz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(modiz)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(modiz, CDialog)
	//{{AFX_MSG_MAP(modiz)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// modiz message handlers
