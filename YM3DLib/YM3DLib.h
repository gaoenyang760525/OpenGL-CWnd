
// YM3DLib.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYM3DLibApp: 
// �йش����ʵ�֣������ YM3DLib.cpp
//

class CYM3DLibApp : public CWinApp
{
public:
	CYM3DLibApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYM3DLibApp theApp;