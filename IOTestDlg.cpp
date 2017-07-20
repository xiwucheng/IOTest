// IOTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IOTest.h"
#include "IOTestDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIOTestDlg �Ի���


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


// CIOTestDlg ��Ϣ�������

BOOL CIOTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIOTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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
