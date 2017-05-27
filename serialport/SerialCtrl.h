#ifndef _SERIAL_CTRL_H
#define _SERIAL_CTRL_H

/**************************************************************************/
/* Title: CSerialIO: a useful and simple serial control                   */
/* Author: wufengkai                                                      */
/* Email:  tojine@hotmail.com                                             */

class SerialCtrl
{
private:
	BOOL m_portStatus;                    
	HANDLE m_portHandle;                  
	DCB m_portConfig;   
public:
	SerialCtrl(void);
	~SerialCtrl(void);             
	void SetPortStatus(BOOL bOnOff);
	BOOL GetPortStatus(void);
	HANDLE GetPortHandle(void);
	BOOL OpenPort(DCB dcb, CString portName=CString("COM1"));
	BOOL OpenPort(CString baudRate=CString("115200"), CString portName=CString("COM1"));
	BOOL Read(char * inputData, const unsigned int & sizeBuffer, unsigned long & length);
	BOOL Write(const char *outputData, const unsigned int & sizeBuffer, unsigned long & length);
	BOOL ClosePort(void);
};

class CSerialIO;

class SerialThread : public CWinThread
{
public:
	// To enable objects of CObject-derived classes to be created dynamically at  run timeto enable objects of CObject-derived classes to be created 

	DECLARE_DYNCREATE(SerialThread)  
	SerialThread ();               // Constructor.
	virtual ~SerialThread();       // Destructor.

	void ClosePort();
	virtual BOOL InitInstance();   // virtual function that derive from base-class.
	virtual int Run();             // virtual function that derive from base-class.  
	void setOwner(CSerialIO* serialIO)
	{
		m_serialIO = serialIO;
	}   

	static SerialCtrl& serialCtrl() // Implement as the singleton funciton.
	{
		static SerialCtrl serial;
		return serial;
	}
private:
	CSerialIO*  m_serialIO;         // The pointer that pointer to object user data, such dialog,window

};

#define MAX_SEND_BUFFER 1024

class CSerialIO{

public:
	CSerialIO();
	virtual ~CSerialIO();

    void OpenPort(CString strPortName,CString strBaudRate);//open serial port with parameter name and baud rate
	virtual void OnEventOpen(BOOL bSuccess);// handle the event whether the port is successfully opened 
	void ClosePort();//close serial port
	virtual void OnEventClose(BOOL bSuccess);//handle the event whether the port is successfully closed
	virtual void OnEventRead(CString inPacket,int inLength);// handle the received data from serial
	void Write(CString& outPacket,int outLength);// write data directly 
	virtual void OnEventWrite(int nWritten); //return how many bytes has been written

	BOOL GetSendActivateValue(void); 
	void SetSendActivate(BOOL bSendActivate);
	BOOL GetPortActivateValue(void);
	void SetPortActivate(BOOL bPortActivate);
	BOOL GetProcessActivateValue(void);
	void SetProcessActivate(BOOL bProcessActivate);
	DCB m_DCB;
	char m_sendBuffer[MAX_SEND_BUFFER];
	unsigned int m_sendSize;
	CString	m_strPortName;
	BOOL m_bClosePort;
private:
	BOOL Init();
	void UnInit();
	SerialThread* m_serialProcess;
	BOOL m_bProccessActivate;
	BOOL m_bPortActivate;
	BOOL m_bSendActivate;
	CString	m_strBaudRate;
};

#endif