
// CommTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "CommTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCommTestDlg �Ի���




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


// CCommTestDlg ��Ϣ�������

BOOL CCommTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCommTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCommTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCommTestDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ---- 2���� ----
	//UpdateData(true);//��ȡ�༭������
	//m_mscomm.put_Output(COleVariant(m_EditSend));//��������
	////m_EditSend.Empty();//���ͺ���������
	//m_EditReceive.Empty();
	//UpdateData(false);//���±༭������
	
	UpdateData(true); //��ȡ�༭������
	CByteArray hexdata;
	int len = String2Hex(m_EditSend,hexdata); //�˴����ص�len�������ڼ��㷢���˶��ٸ�ʮ��������
	m_mscomm.put_Output(COleVariant(hexdata)); //����ʮ����������
	m_EditReceive.Empty();
}


void CCommTestDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_mscomm.get_PortOpen())
	{
		m_mscomm.put_PortOpen(FALSE);
	}
	m_mscomm.put_CommPort(3);//ѡ��com3
	m_mscomm.put_InBufferSize(1024);//���ջ�����
	m_mscomm.put_OutBufferSize(512);//���ͻ�����  ��ע�⡿��Ϊ512
	m_mscomm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0����ʾȫ����ȡ
	m_mscomm.put_InputMode(1);//�Զ����Ʒ�ʽ��д����
	m_mscomm.put_RThreshold(1);//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm�¼�
	m_mscomm.put_Settings(_T("9600,n,8,1"));//������9600�޼���λ��8������λ��1��ֹͣλ
	if (!m_mscomm.get_PortOpen())//�������û�д����
	{
		m_mscomm.put_PortOpen(TRUE);//�򿪴���
		AfxMessageBox(_T("����3�򿪳ɹ�"));
	}
	else
	{
		m_mscomm.put_OutBufferCount(0);
		AfxMessageBox(_T("����3��ʧ��"));
	}
}


void CCommTestDlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_mscomm.put_PortOpen(FALSE);
	AfxMessageBox(_T("����3�ѹر�"));	
}

BEGIN_EVENTSINK_MAP(CCommTestDlg, CDialogEx)
	ON_EVENT(CCommTestDlg, IDC_MSCOMM1, 1, CCommTestDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CCommTestDlg::OnCommMscomm1()
{
	// TODO: �ڴ˴������Ϣ����������
	static unsigned int cnt = 0;
	VARIANT variant_inp;
	COleSafeArray safearrary_inp;
	long len,k;
	unsigned int data[1024] = {0};
	byte rxdata[1024];   // ��ע�⡿����1024��512���񶼿���
	CString strtemp;
	if (m_mscomm.get_CommEvent() == 2) // ֵΪ2��ʾ���ջ����������ַ�
	{
		cnt++;
		variant_inp = m_mscomm.get_Input(); //����������Ϣ
		safearrary_inp = variant_inp; // ����ת��
		len = safearrary_inp.GetOneDimSize(); //�õ���Ч�����ݳ���
		for (k = 0; k < len; k++)
		{
			safearrary_inp.GetElement(&k, rxdata + k);
		}

		for (k = 0; k < len; k++)
		{
			strtemp.Format(_T("%02X"),*(rxdata+k)); // ��ע�⡿
			m_EditReceive += strtemp;
			CString temp = _T("\r\n"); // ����
			m_EditReceive += temp;
		}
	}

	UpdateData(FALSE);//���б༭����
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

//����һ�����ַ�ת��Ϊ��Ӧ��ʮ������ֵ�ĺ���
//���ܣ�������0-F֮����ַ�����ת��Ϊ��Ӧ��ʮ�������ַ������򷵻�-1
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
