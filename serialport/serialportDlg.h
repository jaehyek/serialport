
// serialportDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "ComPortCombo.h"
#include "SerialCtrl.h"

// CserialportDlg ��ȭ ����
class CserialportDlg : public CDialogEx, public CSerialIO
{
// �����Դϴ�.
public:
	CserialportDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALPORT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
