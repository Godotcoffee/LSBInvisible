
// LSBInvisible.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLSBInvisibleApp: 
// �йش����ʵ�֣������ LSBInvisible.cpp
//

class CLSBInvisibleApp : public CWinApp
{
public:
	CLSBInvisibleApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLSBInvisibleApp theApp;
