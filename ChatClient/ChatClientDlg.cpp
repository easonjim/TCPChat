// ChatClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"

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
// CChatClientDlg dialog

CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatClientDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
	//{{AFX_MSG_MAP(CChatClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonSatrt)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_MESSAGE(WM_SOCKET_READ,OnSocketRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg message handlers

BOOL CChatClientDlg::OnInitDialog()
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
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->SetAddress(10,116,46,246);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_SEND))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_EDIT_SEND))->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatClientDlg::OnPaint() 
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
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChatClientDlg::OnButtonSatrt() 
{
	// TODO: Add your control notification handler code here
	DWORD dwIP;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);

	m_Socket_Client=socket(AF_INET,SOCK_STREAM,0);

	addrClient.sin_family=AF_INET;
	addrClient.sin_port=htons(6000);
	addrClient.sin_addr.S_un.S_addr=htonl(dwIP);
	
	if (SOCKET_ERROR==connect(m_Socket_Client,(SOCKADDR*)&addrClient,sizeof(SOCKADDR)))
	{
		AfxMessageBox("连接过程发生错误！\n请确保IP输入正确无误！");
	}
	else
	{
		if (SOCKET_ERROR==WSAAsyncSelect(m_Socket_Client,m_hWnd,WM_SOCKET_READ,FD_READ))
		{
			AfxMessageBox("注册网络读取事件失败！");
		}
		else
		{
			((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_START))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_STOP))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_BUTTON_SEND))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_EDIT_SEND))->EnableWindow(TRUE);
		}
	}
}

void CChatClientDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	if(SOCKET_ERROR==closesocket(m_Socket_Client))
	{
		AfxMessageBox("关闭套接字失败！");
		return;
	}
	else
	{
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_START))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_STOP))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_SEND))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_EDIT_SEND))->EnableWindow(FALSE);

	}
}
LRESULT CChatClientDlg::OnSocketRead(WPARAM wParam,LPARAM lParam)
{
	if (FD_READ == LOWORD(lParam))
	{
		recvBufIP recvBufIP1;
		CString temBuf;
		CString EDITrecvBuf;
		if (SOCKET_ERROR == recv(m_Socket_Client,(char*)&recvBufIP1,sizeof(recvBufIP1),0))
		{
			AfxMessageBox("接受到一个错误消息！");
		}		
  		temBuf.Format("%s 说：%s",recvBufIP1.IP,recvBufIP1.buf);
  		temBuf+="\r\n";
  		((CEdit*)GetDlgItem(IDC_EDIT_RECV))->GetWindowText(EDITrecvBuf);
  		EDITrecvBuf+=temBuf;
  		((CEdit*)GetDlgItem(IDC_EDIT_RECV))->SetWindowText(EDITrecvBuf);
		((CEdit*)GetDlgItem(IDC_EDIT_RECV))->LineScroll(
			((CEdit*)GetDlgItem(IDC_EDIT_RECV))->GetLineCount(),0);
		
	}
	return 0;
}

void CChatClientDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	CString sendBuf;
	((CEdit*)GetDlgItem(IDC_EDIT_SEND))->GetWindowText(sendBuf);
	send(m_Socket_Client,sendBuf,sendBuf.GetLength()+1,0);
	((CEdit*)GetDlgItem(IDC_EDIT_SEND))->SetWindowText("");	

}

