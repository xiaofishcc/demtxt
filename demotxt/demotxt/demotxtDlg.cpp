
// demotxtDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "demotxt.h"
#include "demotxtDlg.h"
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


// CdemotxtDlg 对话框



CdemotxtDlg::CdemotxtDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CdemotxtDlg::IDD, pParent)
	, m_DataType(0)
	, m_DataNum(100)//数据个数默认值100
	, m_txtName(_T("Data.txt"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdemotxtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_Rand, m_DataType);
	DDX_Text(pDX, IDC_DataNum, m_DataNum);
	DDX_Text(pDX, IDC_txtName, m_txtName);
}

BEGIN_MESSAGE_MAP(CdemotxtDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Save, &CdemotxtDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CdemotxtDlg 消息处理程序

BOOL CdemotxtDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdemotxtDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CdemotxtDlg::OnPaint()
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
HCURSOR CdemotxtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CdemotxtDlg::OnBnClickedSave()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	double Data[10000] = { 0 };
	switch (m_DataType)
	{
	case 0:
		for (int i = 0; i < m_DataNum; i++)
		{
			Data[i] = rand() % 10000;
			break;
		}
	case 1:
		Data[1] = 1; Data[2] = 1;
		for (int i = 2; i < m_DataNum; i++)
		{
			Data[i] = Data[i - 1] + Data[i-2];
			break;
		}
	case 2:
		for (int i = 0; i < m_DataNum; i++)
		{
			Data[i] = 1;
			for (int j = 1; j < i+1; j++)
			{
				Data[i] *= j;
			}
			break;
		}
	}
	//通过CStdioFile类的对象将数据写入txt文件中，Open函数可以指定保存路径，默认保存在工程文件的Demo\Demo\文件夹下
	CStdioFile file;
	file.Open(m_txtName, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	CString str;
	for (int i = 0; i < m_DataNum; i++)
	{
		str.Format(_T("%d\t%g\n"), i + 1, Data[i]);
		file.WriteString(str);
	}
	file.Close();
	AfxMessageBox(_T("已保存数据到 ") + m_txtName + _T(" 文件中！"));
}
