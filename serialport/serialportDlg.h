
// serialportDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ComPortCombo.h"
#include "SerialCtrl.h"

// CserialportDlg 대화 상자
class CserialportDlg : public CDialogEx, public CSerialIO
{
// 생성입니다.
public:
	CserialportDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALPORT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    virtual void OnEventOpen(BOOL bSuccess);
    virtual void OnEventClose(BOOL bSuccess);
    virtual void OnEventRead(char *inPacket, int inLength);
    virtual void OnEventWrite(int nWritten);

    CComPortCombo m_comboPorts;
    CButton m_CheckOnlyPhysical;
    CButton m_CheckOnlyPresent;
    afx_msg void OnBnClickedOnlyPhysical();
    afx_msg void OnBnClickedOnlyPresent();
    afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);

    CComboBox m_comboBR;
    CButton m_btnOpen;
    CEdit m_editWrite;
    CListBox m_listboxRead;
    CStatic m_staticInfo;

    BOOL bPortOpened;

    afx_msg void OnBnClickedButtonOpen();
    afx_msg void OnBnClickedButtonWr();
};
