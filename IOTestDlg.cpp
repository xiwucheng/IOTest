// IOTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IOTest.h"
#include "IOTestDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIOTestDlg 对话框


CIOTestDlg::CIOTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIOTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIOTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIOTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_READ, &CIOTestDlg::OnBnClickedRead)
	ON_BN_CLICKED(IDC_WRITE, &CIOTestDlg::OnBnClickedWrite)
END_MESSAGE_MAP()


// CIOTestDlg 消息处理程序

BOOL CIOTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//lpInitializeWinIo fnInitializeWinIo = NULL;
	//lpShutdownWinIo fnShutdownWinIo = NULL;
	//lpMapPhysToLin fnMapPhysToLin = NULL;
	//lpUnmapPhysicalMemory fnUnmapPhysicalMemory = NULL;
	//lpGetPhysLong fnGetPhysLong = NULL;
	//lpSetPhysLong fnSetPhysLong = NULL;
	//lpGetPortVal fnGetPortVal = NULL;
	//lpSetPortVal fnSetPortVal = NULL;
	//lpInstallWinIoDriver fnInstallWinIoDriver = NULL;
	//lpRemoveWinIoDriver fnRemoveWinIoDriver = NULL;


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIOTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CIOTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIOTestDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

void CIOTestDlg::OnBnClickedRead()
{
	// TODO: Add your control notification handler code here
	DWORD dwAddr,dwValue;

	CString str;
	GetDlgItemText(IDC_EDIT1,str);
	if (str.GetLength() == 0)
	{
		return;
	}
	dwAddr = wcstoul(str,0,16);
	BOOL  b= GetPhysLong((LPBYTE)&dwAddr,&dwValue);
	if (!b)
	{
		MessageBox(TEXT("This address is unaccessible"),TEXT("Access Error"),MB_ICONERROR);
		return;
	}
	str.Format(TEXT("0x%08x"),dwValue);
	SetDlgItemText(IDC_EDIT2,str);
}

void CIOTestDlg::OnBnClickedWrite()
{
	// TODO: Add your control notification handler code here
	DWORD dwAddr,dwValue;

	CString str;
	GetDlgItemText(IDC_EDIT1,str);
	if (str.GetLength() == 0)
	{
		return;
	}
	dwAddr = wcstoul(str,0,16);
	if (dwAddr < 1)
	{
		return;
	}


	GetDlgItemText(IDC_EDIT2,str);
	if (str.GetLength() == 0)
	{
		return;
	}
	dwValue = wcstoul(str,0,16);
	BOOL b = SetPhysLong((LPBYTE)&dwAddr,dwValue);
	if (!b)
	{
		MessageBox(TEXT("This address is unaccessible"),TEXT("Access Error"),MB_ICONERROR);
	}
}
