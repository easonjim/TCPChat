// ChatSrvDlg.h : header file
//

#if !defined(AFX_CHATSRVDLG_H__81C23068_9087_41C2_A919_586462A6AEC0__INCLUDED_)
#define AFX_CHATSRVDLG_H__81C23068_9087_41C2_A919_586462A6AEC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define WM_SERVER_ACCEPT		WM_USER+1
#define WM_SOCKET_READ_CLOSE	WM_USER+2

/////////////////////////////////////////////////////////////////////////////
// CChatSrvDlg dialog

class CChatSrvDlg : public CDialog
{
// Construction
public:
	SOCKADDR_IN addrClient;
	SOCKET m_Socket_Accept[20];
	SOCKADDR_IN addrSrv;
	SOCKET m_Socket_Listen;
	CChatSrvDlg(CWnd* pParent = NULL);	// standard constructor
	struct recvBufIP
	{
		char IP[100];
		char buf[200];		
	};
	CString userIP[20];



// Dialog Data
	//{{AFX_DATA(CChatSrvDlg)
	enum { IDD = IDD_CHATSRV_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatSrvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatSrvDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg LRESULT OnServerAccept(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSocketReadClose(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSRVDLG_H__81C23068_9087_41C2_A919_586462A6AEC0__INCLUDED_)
