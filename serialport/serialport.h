
// serialport.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CserialportApp:
// �� Ŭ������ ������ ���ؼ��� serialport.cpp�� �����Ͻʽÿ�.
//

class CserialportApp : public CWinApp
{
public:
	CserialportApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CserialportApp theApp;