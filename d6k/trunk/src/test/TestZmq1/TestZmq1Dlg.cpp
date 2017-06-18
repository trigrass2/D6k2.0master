
// TestZmq1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestZmq1.h"
#include "TestZmq1Dlg.h"
#include "afxdialogex.h"


#pragma comment(lib,"libzmq.lib")
#include "zmq.h"

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


// CTestZmq1Dlg 对话框



CTestZmq1Dlg::CTestZmq1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestZmq1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestZmq1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestZmq1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestZmq1Dlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTestZmq1Dlg 消息处理程序

BOOL CTestZmq1Dlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	m_pCtx = zmq_ctx_new();
	ASSERT(m_pCtx);

	m_pSender = zmq_socket(m_pCtx, ZMQ_PUSH);
//	int nRet =zmq_bind(m_pSender, "tcp://*:10002");
//	int nRet = zmq_connect(m_pSender, "tcp://localhost:10002");
	int nRet = zmq_bind(m_pSender, "tcp://*:10002");
	ASSERT(nRet == 0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestZmq1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestZmq1Dlg::OnPaint()
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
HCURSOR CTestZmq1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestZmq1Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码

	zmq_msg_t msg;
	//zmq_msg_init_size(&msg, 1024);
//	char data[] = "1234556789";
	unsigned char data[20] = { 0 };

	static unsigned char nStart = 1;

	for (int i = 0; i < 20; i++)
	{
		data[i] = nStart+i;
	}

	nStart++;

	zmq_msg_init_data(&msg, data, sizeof data, nullptr, nullptr);

	int nRet = zmq_msg_send(&msg, m_pSender, ZMQ_DONTWAIT);
}


void CTestZmq1Dlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();


}


void CTestZmq1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	zmq_close(m_pSender);
	zmq_ctx_destroy(m_pCtx);
	// TODO:  在此处添加消息处理程序代码
}
