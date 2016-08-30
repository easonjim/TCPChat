; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatClientDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChatClient.h"

ClassCount=4
Class1=CChatClientApp
Class2=CChatClientDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CHATCLIENT_DIALOG

[CLS:CChatClientApp]
Type=0
HeaderFile=ChatClient.h
ImplementationFile=ChatClient.cpp
Filter=N

[CLS:CChatClientDlg]
Type=0
HeaderFile=ChatClientDlg.h
ImplementationFile=ChatClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ChatClientDlg.h
ImplementationFile=ChatClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHATCLIENT_DIALOG]
Type=1
Class=CChatClientDlg
ControlCount=8
Control1=IDC_EDIT_RECV,edit,1353779332
Control2=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control3=IDC_STATIC,button,1342178055
Control4=IDC_BUTTON_START,button,1342242816
Control5=IDC_STATIC,button,1342178055
Control6=IDC_EDIT_SEND,edit,1350631552
Control7=IDC_BUTTON_SEND,button,1342242817
Control8=IDC_BUTTON_STOP,button,1342242816

