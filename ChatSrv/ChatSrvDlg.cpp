// ChatSrvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatSrv.h"
#include "ChatSrvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatSrvDlg dialog

CChatSrvDlg::CChatSrvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatSrvDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatSrvDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatSrvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatSrvDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatSrvDlg, CDialog)
	//{{AFX_MSG_MAP(CChatSrvDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_MESSAGE(WM_SERVER_ACCEPT,OnServerAccept)
	ON_MESSAGE(WM_SOCKET_READ_CLOSE,OnSocketReadClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatSrvDlg message handlers

BOOL CChatSrvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_BUTTON_STOP))->EnableWindow(FALSE);

	for (int i=0;i<20;i++)
	{
		m_Socket_Accept[i]=INVALID_SOCKET;
	}	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatSrvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatSrvDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatSrvDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChatSrvDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	m_Socket_Listen=socket(AF_INET,SOCK_STREAM,0);
	
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	addrSrv.sin_addr.S_un.S_addr=INADDR_ANY;
	
	if(SOCKET_ERROR==bind(m_Socket_Listen,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)))
	{
		AfxMessageBox("绑定套接字失败！");
		return;
	}
	
	if(SOCKET_ERROR==listen(m_Socket_Listen,20))
	{
		AfxMessageBox("侦听套接字失败！");
		return;
	}
	
	if(SOCKET_ERROR==WSAAsyncSelect(m_Socket_Listen,m_hWnd,WM_SERVER_ACCEPT,FD_ACCEPT))
	{
		AfxMessageBox("注册网络连接事件失败！");
		return;
	}
	((CButton*)GetDlgItem(IDC_BUTTON_START))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP))->EnableWindow(TRUE);
}

void CChatSrvDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_BUTTON_START))->EnableWindow(TRUE);
	if(SOCKET_ERROR==closesocket(m_Socket_Listen))
	{
		AfxMessageBox("关闭套接字失败！");
		return;
	}
	((CButton*)GetDlgItem(IDC_BUTTON_STOP))->EnableWindow(FALSE);
}

LRESULT CChatSrvDlg::OnServerAccept(WPARAM wParam,LPARAM lParam)
{
	int len = sizeof(SOCKADDR);
	if (LOWORD(lParam) == FD_ACCEPT)
	{
		for (int i=0;(i<20)&&(m_Socket_Accept[i]!=INVALID_SOCKET);)
		{
			i++;
		}
		if (i==20)
		{
			return 0;
		}
		m_Socket_Accept[i] = accept(m_Socket_Listen,(SOCKADDR*)&addrClient,&len);
		userIP[i]=inet_ntoa(addrClient.sin_addr);
		WSAAsyncSelect(m_Socket_Accept[i],m_hWnd,WM_SOCKET_READ_CLOSE,FD_READ|FD_CLOSE);
	}
	return TRUE;
}

LRESULT CChatSrvDlg::OnSocketReadClose(WPARAM wParam,LPARAM lParam)
{
	if (LOWORD(lParam) == FD_READ)
	{
		recvBufIP recvBufIP1;
		for (int i=0;(i<20)&&(m_Socket_Accept[i]!=wParam);)
		{
			i++;
		}
		if (i==20)
		{
			return 0;
		}
		if (SOCKET_ERROR==recv(m_Socket_Accept[i],recvBufIP1.buf,strlen(recvBufIP1.buf),0))
		{
			AfxMessageBox("接收到一个错误信息！");
		}
		strcpy(recvBufIP1.IP,userIP[i]);
		for (int j=0;j<20;j++)
		{	
			if (m_Socket_Accept[j]!=INVALID_SOCKET)
			{
				send(m_Socket_Accept[j],(char*)&recvBufIP1,sizeof(recvBufIP1),0);
			}
		}
	}
	if (LOWORD(lParam) == FD_CLOSE)
	{
		for (int i=0;(i<20)&&(m_Socket_Accept[i]!=wParam);)
		{
			i++;
		}
		if (i==20)
		{
			return 0;
		}
		m_Socket_Accept[i] = INVALID_SOCKET;
	}
	return TRUE;
}
