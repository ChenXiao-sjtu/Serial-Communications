
// CommTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CommTest.h"
#include "CommTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCommTestDlg 对话框




CCommTestDlg::CCommTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommTestDlg::IDD, pParent)
	, m_EditSend(_T(""))
	, m_EditReceive(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
	DDX_Text(pDX, IDC_EDIT1, m_EditSend);
	DDX_Text(pDX, IDC_EDIT2, m_EditReceive);
}

BEGIN_MESSAGE_MAP(CCommTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CCommTestDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCommTestDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CCommTestDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CCommTestDlg 消息处理程序

BOOL CCommTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCommTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCommTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCommTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCommTestDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	// ---- 2进制 ----
	//UpdateData(true);//读取编辑框内容
	//m_mscomm.put_Output(COleVariant(m_EditSend));//发送数据
	////m_EditSend.Empty();//发送后清空输入框
	//m_EditReceive.Empty();
	//UpdateData(false);//更新编辑框内容
	
	UpdateData(true); //读取编辑框内容
	CByteArray hexdata;
	int len = String2Hex(m_EditSend,hexdata); //此处返回的len可以用于计算发送了多少个十六进制数
	m_mscomm.put_Output(COleVariant(hexdata)); //发送十六进制数据
	m_EditReceive.Empty();
}


void CCommTestDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_mscomm.get_PortOpen())
	{
		m_mscomm.put_PortOpen(FALSE);
	}
	m_mscomm.put_CommPort(3);//选择com3
	m_mscomm.put_InBufferSize(1024);//接收缓冲区
	m_mscomm.put_OutBufferSize(512);//发送缓冲区  【注意】设为512
	m_mscomm.put_InputLen(0);//设置当前接收区数据长度为0，表示全部读取
	m_mscomm.put_InputMode(1);//以二进制方式读写数据
	m_mscomm.put_RThreshold(1);//接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm事件
	m_mscomm.put_Settings(_T("9600,n,8,1"));//波特率9600无检验位，8个数据位，1个停止位
	if (!m_mscomm.get_PortOpen())//如果串口没有打开则打开
	{
		m_mscomm.put_PortOpen(TRUE);//打开串口
		AfxMessageBox(_T("串口3打开成功"));
	}
	else
	{
		m_mscomm.put_OutBufferCount(0);
		AfxMessageBox(_T("串口3打开失败"));
	}
}


void CCommTestDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	m_mscomm.put_PortOpen(FALSE);
	AfxMessageBox(_T("串口3已关闭"));	
}

BEGIN_EVENTSINK_MAP(CCommTestDlg, CDialogEx)
	ON_EVENT(CCommTestDlg, IDC_MSCOMM1, 1, CCommTestDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CCommTestDlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	static unsigned int cnt = 0;
	VARIANT variant_inp;
	COleSafeArray safearrary_inp;
	long len,k;
	unsigned int data[1024] = {0};
	byte rxdata[1024];   // 【注意】这里1024和512好像都可以
	CString strtemp;
	if (m_mscomm.get_CommEvent() == 2) // 值为2表示接收缓冲区内有字符
	{
		cnt++;
		variant_inp = m_mscomm.get_Input(); //读缓冲区消息
		safearrary_inp = variant_inp; // 变量转换
		len = safearrary_inp.GetOneDimSize(); //得到有效的数据长度
		for (k = 0; k < len; k++)
		{
			safearrary_inp.GetElement(&k, rxdata + k);
		}

		for (k = 0; k < len; k++)
		{
			strtemp.Format(_T("%02X"),*(rxdata+k)); // 【注意】
			m_EditReceive += strtemp;
			CString temp = _T("\r\n"); // 换行
			m_EditReceive += temp;
		}
	}

	UpdateData(FALSE);//更行编辑内容
}


int CCommTestDlg::String2Hex(CString str, CByteArray &senddata)
{
	int hexdata,lowhexdata;
	int hexdatalen = 0;
	int len = str.GetLength();
	senddata.SetSize(len/2);
	for(int i = 0;i<len;)
	{
		char lstr,hstr = str[i];
		if(hstr == ' ')
		{
			i++;
			continue;
		}
		i++;
		if(i >= len)
			break;
		lstr = str[i];
		hexdata = ConvertHexChar(hstr);
		lowhexdata = ConvertHexChar(lstr);
		if((hexdata == 16) || (lowhexdata == 16))
			break;
		else 
			hexdata = hexdata*16+lowhexdata;
		i++;
		senddata[hexdatalen] = (char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;
}

//这是一个将字符转换为相应的十六进制值的函数
//功能：若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1
char CCommTestDlg::ConvertHexChar(char ch) 
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else return (-1);
}
