
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����


//#############################################################################################
//  definitions by jaehyek 

#include <tchar.h>
#include <setupapi.h>
#include <malloc.h>
#include <winspool.h>
#include <Wbemcli.h>
#include <comdef.h>
#include <stdio.h>

#define CENUMERATESERIAL_USE_STL //Uncomment this line if you want to test the MFC / ATL support in CEnumerateSerial

#ifdef CENUMERATESERIAL_USE_STL
//Pull in STL support
#include <vector>
#include <string>
#endif

//Out of the box lets exclude support for CEnumerateSerial::UsingComDB on the Windows SDK 7.1 or earlier since msports.h
//is only available with the Windows SDK 8 or later.
#include <ntverp.h>
#if VER_PRODUCTBUILD <= 7600
#define NO_CENUMERATESERIAL_USING_COMDB
#endif

#ifndef NO_CENUMERATESERIAL_USING_COMDB
#include <msports.h>
#endif //#ifndef NO_CENUMERATESERIAL_USING_COMDB












