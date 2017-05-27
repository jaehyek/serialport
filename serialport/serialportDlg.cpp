
// serialportDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "serialport.h"
#include "serialportDlg.h"
#include "afxdialogex.h"

#include <Dbt.h>									// Equates for WM_DEVICECHANGE and BroadcastSystemMessage

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CserialportDlg 대화 상자



CserialportDlg::CserialportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIALPORT_DIALOG, pParent)
    , bPortOpened(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CserialportDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, m_comboPorts);
    DDX_Control(pDX, IDC_CHECK1, m_CheckOnlyPhysical);
    DDX_Control(pDX, IDC_CHECK2, m_CheckOnlyPresent);
    DDX_Control(pDX, IDC_COMBO_BR, m_comboBR);
    DDX_Control(pDX, IDC_BUTTON_OPEN, m_btnOpen);
    DDX_Control(pDX, IDC_EDIT_WRITE, m_editWrite);
    DDX_Control(pDX, IDC_LIST_READ, m_listboxRead);
    DDX_Control(pDX, IDC_STATIC_INFO, m_staticInfo);
}

BEGIN_MESSAGE_MAP(CserialportDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_CHECK1, &CserialportDlg::OnBnClickedOnlyPhysical)
    ON_BN_CLICKED(IDC_CHECK2, &CserialportDlg::OnBnClickedOnlyPresent)
    ON_WM_DEVICECHANGE()
    ON_BN_CLICKED(IDC_BUTTON_OPEN, &CserialportDlg::OnBnClickedButtonOpen)
    ON_BN_CLICKED(IDC_BUTTON_WR, &CserialportDlg::OnBnClickedButtonWr)
END_MESSAGE_MAP()


// CserialportDlg 메시지 처리기

BOOL CserialportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

// COM port selection combo box initialization.
//
// By default, the first combo box item is "<None>".
// This is especially useful with modern systems that did not have any
//  serial port anymore.
// To remove this item, call SetNoneItem(0).
//	m_comboPorts.SetNoneItem(0);

// By default, all COM ports are listed.
// When only physical ports and no virtual ones should be listed,
//  use SetOnlyPhysical(1).
//	m_comboPorts.SetOnlyPhysical(1);

// By default, only present COM ports are listed.
// To list also non-present ports, use SetOnlyPresent(0).
//	m_comboPorts.SetOnlyPresent(0);

// When a serial port has been configured in the past or is in use,
//  pass the port number here to be pre-selected in the list.
    int nPortNum = AfxGetApp()->GetProfileInt(_T("Config"), _T("ComPort1"), -1);
    m_comboPorts.InitList(nPortNum);

    // You may also use the COM port file name "COM<n>" or "\\.\COM<n>".
    //	CString strPort = AfxGetApp()->GetProfileString(_T("Config"), _T("ComPort1Str"));
    //	m_comboPorts.InitList(strPort.GetString());
    //	strPort = AfxGetApp()->GetProfileString(_T("Config"), _T("ComPort2Str"));


    m_CheckOnlyPresent.SetCheck(BST_UNCHECKED);

    m_comboBR.InsertString(0, CString("4800"));
    m_comboBR.InsertString(1, CString("9600"));
    m_comboBR.InsertString(2, CString("19200"));
    m_comboBR.InsertString(3, CString("115200"));
    m_comboBR.SetCurSel(1);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CserialportDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CserialportDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CserialportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CserialportDlg::OnBnClickedOnlyPhysical()
{
    // Pass option to include/exclude non-physical ports.
    m_comboPorts.SetOnlyPhysical(m_CheckOnlyPhysical.GetCheck() == BST_CHECKED);

    // Update the lists.
    m_comboPorts.InitList();

}


void CserialportDlg::OnBnClickedOnlyPresent()
{
    // Pass option to include/exclude non-present ports.
    m_comboPorts.SetOnlyPresent(m_CheckOnlyPresent.GetCheck() == BST_CHECKED);

    // Update the lists.
    m_comboPorts.InitList();

}

// WM_DEVICECHANGE handler.
// Used here to detect plug-in and -out of devices providing virtual COM ports.
// May open/close the configured virtual serial port when it matches the plugged device.
BOOL CserialportDlg::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
    TRACE1("WM_DEVICECHANGE event %#X\n", nEventType);

    BOOL bResult = CDialog::OnDeviceChange(nEventType, dwData);

    // Assume port changing (serial or parallel). The devicetype field is part of header of all structures.
    // The name passed here is always the COM port name (even with virtual ports).
    PDEV_BROADCAST_PORT pPort = reinterpret_cast<PDEV_BROADCAST_PORT>(dwData);
    if ((nEventType == DBT_DEVICEARRIVAL || nEventType == DBT_DEVICEREMOVECOMPLETE) &&
        pPort &&
        pPort->dbcp_devicetype == DBT_DEVTYP_PORT &&	// serial or parallel port
        CEnumDevices::GetPortFromName(pPort->dbcp_name) > 0)
    {
        if (nEventType == DBT_DEVICEARRIVAL)
            TRACE1("Device %s is now available\n", pPort->dbcp_name);
        else
            TRACE1("Device %s has been removed\n", pPort->dbcp_name);
        // Update the lists.
        m_comboPorts.InitList();

    }
    return bResult;
}


void CserialportDlg::OnEventOpen(BOOL bSuccess)
{
    CString str;
    if (bSuccess)
    {
        str = m_strPortName + CString(" open successfully");

        bPortOpened = TRUE;
        m_btnOpen.SetWindowText(CString("Close"));

    }
    else
    {
        str = m_strPortName + CString(" open failed");
    }
    m_staticInfo.SetWindowText(str);
}

void CserialportDlg::OnEventClose(BOOL bSuccess)
{
    CString str;
    if (bSuccess)
    {
        str = m_strPortName + CString(" close successfully");
        bPortOpened = FALSE;
        m_btnOpen.SetWindowText(CString("Open"));

    }
    else
    {
        str = m_strPortName + CString(" close failed");
    }
    m_staticInfo.SetWindowText(str);
}

void CserialportDlg::OnEventRead(char *inPacket, int inLength)
{

    m_listboxRead.AddString((LPCTSTR)inPacket);

    CString str;
    str.Format(CString("%d bytes read"), inLength);

    m_staticInfo.SetWindowText(str);

}
void CserialportDlg::OnEventWrite(int nWritten)
{
    if (nWritten>0)
    {
        CString str;
        str.Format(CString("%d bytes written"), nWritten);
        m_staticInfo.SetWindowText(str);
    }
    else
    {
        m_staticInfo.SetWindowText(CString("Write failed"));
    }

}


void CserialportDlg::OnBnClickedButtonOpen()
{
    if (bPortOpened == FALSE)
    {
        CString strPortName;
        CString strBaudRate;
        int nPortNum; 
        //m_comboPorts.GetLBText(m_comboPorts.GetCurSel(), strPortName);
        nPortNum = m_comboPorts.GetItemData(m_comboPorts.GetCurSel());
        strPortName.Format(_T("COM%d"), nPortNum); 

        m_comboBR.GetLBText(m_comboBR.GetCurSel(), strBaudRate);
        OpenPort(strPortName, strBaudRate);

    }
    else
    {
        ClosePort();

    }
}


void CserialportDlg::OnBnClickedButtonWr()
{
    CString strW;
    m_editWrite.GetWindowText(strW);
    Write(strW, strW.GetLength());
}
