// IOTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "WinIo\WinIo.h"
#ifdef _DEBUG
#pragma comment(lib,"Debug\\WinIo.lib")
#else
#pragma comment(lib,"Release\\WinIo.lib")
#endif
// CIOTestApp:
// �йش����ʵ�֣������ IOTest.cpp
//

class CIOTestApp : public CWinApp
{
public:
	CIOTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIOTestApp theApp;