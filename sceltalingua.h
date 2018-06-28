#if !defined(AFX_SCELTALINGUA_H__BA66A5F2_587F_41D1_B9A0_53F7A3236D67__INCLUDED_)
#define AFX_SCELTALINGUA_H__BA66A5F2_587F_41D1_B9A0_53F7A3236D67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// sceltalingua.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// sceltalingua dialog

class sceltalingua : public CDialog
{
// Construction
public:
	sceltalingua(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(sceltalingua)
	enum { IDD = IDD_DIALOG3 };
	int		m_lingua;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(sceltalingua)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(sceltalingua)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCELTALINGUA_H__BA66A5F2_587F_41D1_B9A0_53F7A3236D67__INCLUDED_)
