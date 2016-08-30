// ChatSrv.h : main header file for the CHATSRV application
//

#if !defined(AFX_CHATSRV_H__BDBC89A3_C021_4E94_9E70_E262368E620B__INCLUDED_)
#define AFX_CHATSRV_H__BDBC89A3_C021_4E94_9E70_E262368E620B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChatSrvApp:
// See ChatSrv.cpp for the implementation of this class
//

class CChatSrvApp : public CWinApp
{
public:
	CChatSrvApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatSrvApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChatSrvApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSRV_H__BDBC89A3_C021_4E94_9E70_E262368E620B__INCLUDED_)
