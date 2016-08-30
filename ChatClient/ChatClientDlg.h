// ChatClientDlg.h : header file
//

#if !defined(AFX_CHATCLIENTDLG_H__A19BE482_AB4B_4E62_A2B6_9D27EA2D475C__INCLUDED_)
#define AFX_CHATCLIENTDLG_H__A19BE482_AB4B_4E62_A2B6_9D27EA2D475C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define WM_SOCKET_READ WM_USER+3

/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg dialog

class CChatClientDlg : public CDialog
{
// Construction
public:
	SOCKADDR_IN addrClient;
	SOCKET m_Socket_Client;
	CChatClientDlg(CWnd* pParent = NULL);	// standard constructor
	struct recvBufIP
	{
		char IP[100];
		char buf[200];		
	};

// Dialog Data
	//{{AFX_DATA(CChatClientDlg)
	enum { IDD = IDD_CHATCLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSatrt();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonSend();
	afx_msg LRESULT OnSocketRead(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENTDLG_H__A19BE482_AB4B_4E62_A2B6_9D27EA2D475C__INCLUDED_)
