// sceltalingua.cpp : implementation file
//

#include "stdafx.h"
#include "scarabeo.h"
#include "sceltalingua.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// sceltalingua dialog


sceltalingua::sceltalingua(CWnd* pParent /*=NULL*/)
	: CDialog(sceltalingua::IDD, pParent)
{
	//{{AFX_DATA_INIT(sceltalingua)
	m_lingua = -1;
	//}}AFX_DATA_INIT
}


void sceltalingua::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(sceltalingua)
	DDX_Radio(pDX, IDC_RADIO1, m_lingua);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(sceltalingua, CDialog)
	//{{AFX_MSG_MAP(sceltalingua)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// sceltalingua message handlers
