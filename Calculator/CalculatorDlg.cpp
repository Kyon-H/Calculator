
// CalculatorDlg.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include "BigInt.h"
#include "Check.h"
#include <string>
#include <direct.h>
#include <io.h>
#include <fstream>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Number firstnum ,secondnum;//计算过程中第一个数和第二个数
char op;//记录当前计算符号
int poz;//保存小数点位置，初始化为0
bool point_flag;//小数点标志位，判断是否为小数
bool isend;//判断一次计算是否结束

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnCal();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//ON_BN_CLICKED(IDC_NUM1, &CAboutDlg::OnCal)
END_MESSAGE_MAP()


// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, m_Dis(_T("0"))
	, m_Dis2(_T(""))
	, m_show(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DIS, m_Dis);
	DDX_Text(pDX, IDC_DIS2, m_Dis2);
	DDX_Text(pDX, IDC_SHOW, m_show);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BACKSPACE, &CCalculatorDlg::OnBnClickedBackspace)
	ON_BN_CLICKED(IDC_NUM0, &CCalculatorDlg::OnCal)
	ON_BN_CLICKED(IDC_NUM1, &CCalculatorDlg::OnCal)
	ON_BN_CLICKED(IDC_NUM9, &CCalculatorDlg::OnCal)
	ON_BN_CLICKED(IDC_NUM2, &CCalculatorDlg::OnCal)
	ON_BN_CLICKED(IDC_NUM3, &CCalculatorDlg::OnCal)
	ON_BN_CLICKED(IDC_NUM4, &CCalculatorDlg::OnCal)
	ON_BN_CLICKED(IDC_NUM5, &CCalculatorDlg::OnCal)
	ON_BN_CLICKED(IDC_NUM6, &CCalculatorDlg::OnCal)
	ON_BN_CLICKED(IDC_NUM7, &CCalculatorDlg::OnCal)
	ON_BN_CLICKED(IDC_NUM8, &CCalculatorDlg::OnCal)
	ON_BN_CLICKED(IDC_NEG, &CCalculatorDlg::OnBnClickedNeg)
	ON_BN_CLICKED(IDC_PT, &CCalculatorDlg::OnBnClickedPt)
	ON_BN_CLICKED(IDC_CLEAR, &CCalculatorDlg::OnBnClickedClear)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_BN_CLICKED(IDC_ADD, &CCalculatorDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_MIN, &CCalculatorDlg::OnBnClickedMin)
	ON_BN_CLICKED(IDC_MUL, &CCalculatorDlg::OnBnClickedMul)
	ON_BN_CLICKED(IDC_DIV, &CCalculatorDlg::OnBnClickedDiv)
	ON_BN_CLICKED(IDC_CE, &CCalculatorDlg::OnBnClickedCe)
	ON_BN_CLICKED(IDC_EQU, &CCalculatorDlg::OnBnClickedEqu)
	ON_BN_CLICKED(IDC_MOD, &CCalculatorDlg::OnBnClickedMod)
	ON_BN_CLICKED(IDC_BUTTON26, &CCalculatorDlg::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON25, &CCalculatorDlg::OnBnClickedButton25)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码
	int err=_mkdir(FILE_DIR);
	CFile file;
	if (file.Open(L"save\\data.txt", CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate))
		file.Close();
	if (file.Open(L"save\\data.txt", CFile::modeRead, NULL))
	{
		char* pBuf;
		DWORD dwFileLen;
		dwFileLen = file.GetLength();
		pBuf = new char[dwFileLen + 1];
		pBuf[dwFileLen] = 0;
		file.Read(pBuf, dwFileLen);
		file.Close();
		USES_CONVERSION;
		m_show = A2T(pBuf);
		delete[] pBuf;
		UpdateData(FALSE);
	}
	Init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorDlg::OnPaint()
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
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Backspace 按钮处理函数
void CCalculatorDlg::OnBnClickedBackspace()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isend)
	{
		isend = false;
		m_Dis2.Empty();
		UpdateData(FALSE);
		return;
	}
	if (m_Dis.GetLength() == 1)
	{
		m_Dis = '0';
		UpdateData(FALSE);
		return;
	}
	if (m_Dis.GetAt(0) == '-')
	{
		m_Dis = m_Dis.Right(m_Dis.GetLength() - 1);
		UpdateData(FALSE);
		return;
	}
	wchar_t last = m_Dis.GetAt(m_Dis.GetLength() - 1);//获取最后一位字符
	if(iswdigit(last))//last为数字
		m_Dis = m_Dis.Left(m_Dis.GetLength() - 1);
	else if (last == '.')//1. 2. 等情况
	{
		point_flag = false;
		m_Dis = m_Dis.Left(m_Dis.GetLength() - 1);
	}
	UpdateData(FALSE);
}



//数字按钮处理函数
void CCalculatorDlg::OnCal()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isend)
	{
		m_Dis.Empty();
		m_Dis2.Empty();
		isend = false;
		Init();
		UpdateData(FALSE);
	}
	CWnd* pWnd = GetFocus();
	int nPortID = pWnd->GetDlgCtrlID();
	UpdateData(TRUE);
	if (m_Dis == '0')
	{
		m_Dis = (char)(nPortID - 1021 + '0');
	}
	else
	{
		m_Dis += (char)(nPortID - 1021 + '0');
	}
	
	UpdateData(FALSE);
}

//"+/-"按钮处理函数
void CCalculatorDlg::OnBnClickedNeg()
{
	// TODO: 在此添加控件通知处理程序代码
	Number temp;
	temp.num = m_Dis;
	FormatNum(temp);
	if (temp.num == '0')
		return;
	if (isend)
		m_Dis2.Empty();
	if (m_Dis.Find('-') == 0)
	{
		m_Dis = m_Dis.Right(m_Dis.GetLength() - 1);
	}
	else
	{
		m_Dis = '-' + m_Dis;
	}
	isend = false;
	UpdateData(FALSE);
}

//" . "按钮处理函数
void CCalculatorDlg::OnBnClickedPt()
{
	// TODO: 在此添加控件通知处理程序代码
	if (point_flag)
	{
		return;
	}
	m_Dis += '.';
	point_flag = true;
	UpdateData(FALSE);
}

//"C"按钮处理函数
void CCalculatorDlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	Init();
	m_Dis = '0';
	m_Dis2.Empty();
	UpdateData(FALSE);
}

////////
//键盘响应
void CCalculatorDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_NUMPAD0:
		GetDlgItem(IDC_NUM0)->SetFocus();
		OnCal(); break;
	case VK_NUMPAD1:
		GetDlgItem(IDC_NUM1)->SetFocus();
		OnCal(); break;
	case VK_NUMPAD2:
		GetDlgItem(IDC_NUM2)->SetFocus();
		OnCal(); break;
	case VK_NUMPAD3:
		GetDlgItem(IDC_NUM3)->SetFocus();
		OnCal(); break;
	case VK_NUMPAD4:
		GetDlgItem(IDC_NUM4)->SetFocus();
		OnCal(); break;
	case VK_NUMPAD5:
		GetDlgItem(IDC_NUM5)->SetFocus();
		OnCal(); break;
	case VK_NUMPAD6:
		GetDlgItem(IDC_NUM6)->SetFocus();
		OnCal(); break;
	case VK_NUMPAD7:
		GetDlgItem(IDC_NUM7)->SetFocus();
		OnCal(); break;
	case VK_NUMPAD8:
		GetDlgItem(IDC_NUM8)->SetFocus();
		OnCal(); break;
	case VK_NUMPAD9:
		GetDlgItem(IDC_NUM9)->SetFocus();
		OnCal(); break;
	case VK_ADD:
		GetDlgItem(IDC_ADD)->SetFocus();//加号
		OnBnClickedAdd(); break;
	case VK_SUBTRACT:
		GetDlgItem(IDC_MIN)->SetFocus();//减号
		OnBnClickedMin(); break;
	case VK_MULTIPLY:
		GetDlgItem(IDC_MUL)->SetFocus();//乘号
		OnBnClickedMul(); break;
	case VK_DIVIDE:
		GetDlgItem(IDC_DIV)->SetFocus();//除号
		OnBnClickedDiv(); break;
	case VK_BACK:
		GetDlgItem(IDC_BACKSPACE)->SetFocus();//<[back]按钮
		OnBnClickedBackspace(); break;
	case VK_DECIMAL:
		GetDlgItem(IDC_PT)->SetFocus();//. 按钮
		OnBnClickedPt(); break;
	case VK_DELETE:
		GetDlgItem(IDC_CE)->SetFocus();//CE 按钮
		OnBnClickedCe(); break;
	case VK_CLEAR:
		GetDlgItem(IDC_CLEAR)->SetFocus();//C 按钮
		OnBnClickedClear(); break;
	default:
		break;
	}
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	return CDialog::PreTranslateMessage(pMsg);
}

void CCalculatorDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码

	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
}
//////

/// <summary>
/// //"+"号按钮处理函数
/// </summary>
void CCalculatorDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!firstnum.num.IsEmpty())
		return;
	m_Dis2 = m_Dis;
	firstnum.num = m_Dis;
	op = '+';
	m_Dis2+= op;
	m_Dis = '0';
	isend = false;
	UpdateData(FALSE);
	point_flag = false;
	FormatNum(firstnum);
}

/// <summary>
/// //"-"号按钮处理函数
/// </summary>
void CCalculatorDlg::OnBnClickedMin()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!firstnum.num.IsEmpty())
		return;
	m_Dis2 = m_Dis;
	firstnum.num = m_Dis;
	op = '-';
	m_Dis2 += op;
	m_Dis = '0';
	isend = false;
	UpdateData(FALSE);
	point_flag = false;
	FormatNum(firstnum);
}

/// <summary>
/// //"*"按钮处理函数
/// </summary>
void CCalculatorDlg::OnBnClickedMul()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!firstnum.num.IsEmpty())
		return;
	m_Dis2 = m_Dis;
	firstnum.num = m_Dis;
	op = 'X';
	m_Dis2 += op;
	m_Dis = '0';
	isend = false;
	UpdateData(FALSE);
	point_flag = false;
	FormatNum(firstnum);
}

/// <summary>
/// //"/"按钮处理函数
/// </summary>
void CCalculatorDlg::OnBnClickedDiv()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!firstnum.num.IsEmpty())
		return;
	m_Dis2 = m_Dis;
	firstnum.num = m_Dis;
	op = '/';
	m_Dis2 += op;
	m_Dis = '0';
	isend = false;
	UpdateData(FALSE);
	point_flag = false;
	FormatNum(firstnum);
}
/// <summary>
/// "mod"按钮处理函数
/// </summary>
void CCalculatorDlg::OnBnClickedMod()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!firstnum.num.IsEmpty())
		return;
	m_Dis2 = m_Dis;
	firstnum.num = m_Dis;
	op = '%';
	m_Dis2 += op;
	m_Dis = '0';
	isend = false;
	UpdateData(FALSE);
	point_flag = false;
	FormatNum(firstnum);
}
/// <summary>
/// “CE”按钮处理函数
/// </summary>
void CCalculatorDlg::OnBnClickedCe()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!firstnum.num.IsEmpty() && secondnum.num.IsEmpty())//ce只修改第二个数字
	{
		m_Dis = '0';
		point_flag = false;
		UpdateData(FALSE);
	}
}

/// <summary>
/// 等号按钮处理函数
/// </summary>
void CCalculatorDlg::OnBnClickedEqu()
{
	// TODO: 在此添加控件通知处理程序代码
	if (firstnum.num.IsEmpty())
		return;
	secondnum.num = m_Dis;
	FormatNum(secondnum);
	CString res;
	if (op == '+')//操作符为“+”
	{
		int n = max(firstnum.poz, secondnum.poz);
		if (n != 0)
		{
			Addzero(firstnum, n - firstnum.poz);
			Addzero(secondnum, n - secondnum.poz);
		}
		USES_CONVERSION;
		char* numa = T2A(firstnum.num);
		char* numb = T2A(secondnum.num);
		char* result = new char;
		if (firstnum.isnega && !secondnum.isnega)//一负一正时
		{
			subtract(numb, numa, result);
			Number restemp;
			// restemp 带有正负号无小数点的整数
			restemp.num = A2T(result);
			//格式化为完全的Number类型数
			FormatNum(restemp,n);
			res = relFormatNum(restemp);
		}
		else if (!firstnum.isnega && secondnum.isnega)//一正一负时
		{
			subtract(numa, numb, result);
			Number restemp;
			restemp.num = A2T(result);
			FormatNum(restemp, n);
			res = relFormatNum(restemp);
		}
		else if (firstnum.isnega && secondnum.isnega)//两个都是负数
		{
			addition(numa, numb, result);
			Number restemp;
			restemp.num = A2T(result);
			FormatNum(restemp, n);
			res = relFormatNum(restemp);
			res = '-' + res;
		}
		else if (!firstnum.isnega && !secondnum.isnega)//两个都是正数
		{
			addition(numa, numb, result);
			Number restemp;
			restemp.num = A2T(result);
			FormatNum(restemp, n);
			res = relFormatNum(restemp);
		}
	}
	else if (op == '-')
	{
		int n = max(firstnum.poz, secondnum.poz);
		if (n != 0)
		{
			Addzero(firstnum, n - firstnum.poz);
			Addzero(secondnum, n - secondnum.poz);
		}
		USES_CONVERSION;
		char* numa = T2A(firstnum.num);
		char* numb = T2A(secondnum.num);
		char* result = new char;
		if (firstnum.isnega && !secondnum.isnega)//一负一正时
		{
			addition(numa, numb,result);
			Number restemp;
			restemp.num = A2T(result);
			FormatNum(restemp, n);
			res = relFormatNum(restemp);
			res = '-' + res;
		}
		else if (!firstnum.isnega && secondnum.isnega)//一正一负时
		{
			addition(numa, numb, result);
			Number restemp;
			restemp.num = A2T(result);
			FormatNum(restemp, n);
			res = relFormatNum(restemp);
		}
		else if (firstnum.isnega && secondnum.isnega)//两个都是负数
		{
			subtract(numb, numa, result);
			Number restemp;
			restemp.num = A2T(result);
			FormatNum(restemp, n);
			res = relFormatNum(restemp);
		}
		else if (!firstnum.isnega && !secondnum.isnega)//两个都是正数
		{
			subtract(numa, numb, result);
			Number restemp;
			restemp.num = A2T(result);
			FormatNum(restemp, n);
			res = relFormatNum(restemp);
		}
	}
	else if (op == 'X')
	{
		int n =firstnum.poz+ secondnum.poz;
		USES_CONVERSION;
		char* numa = T2A(firstnum.num);
		char* numb = T2A(secondnum.num);
		char* result = new char;
		multiply(numa, numb, result);
		Number restemp;
		restemp.num = A2T(result);
		FormatNum(restemp, n);
		res = relFormatNum(restemp);
		if (firstnum.isnega != secondnum.isnega)//符号不同时
			res = '-' + res;
	}
	else if (op == '/')
	{
	if (secondnum.num == '0')
	{
		MessageBox(_T("除数不应为0"),mess+ _T("提示"));
		return;
	}
		int n = firstnum.poz - secondnum.poz;
		USES_CONVERSION;
		char* numa = T2A(firstnum.num);
		char* numb = T2A(secondnum.num);
		char* result = new char;
		char* remainder=new char;//余数
		divide2(numa, numb, result, remainder);
		Number restemp;
		restemp.num = A2T(result);
		FormatNum(restemp, n);
		for (int i = 0; i < 5; ++i)
		{
			if (strcmp(remainder,"0")==0)
				break;
			//numa=Addzero(remainder, 1);
			strcat(remainder, "0");
			numa = remainder;
			restemp.poz++;
			char* rt=new char;
			divide2(numa, numb, rt, remainder);
			strcat(result, rt);
		}
		restemp.num = A2T(result);
		res=relFormatNum(restemp);
	}
	else if (op == '%')
	{
		int n = max(firstnum.poz, secondnum.poz);
		if (n > 0||firstnum.isnega||secondnum.isnega)
		{
			MessageBox(_T("格式不正确，请输入正整数"), mess+ _T("提示"));
			return;
		}
		USES_CONVERSION;
		char* numa = T2A(firstnum.num);
		char* numb = T2A(secondnum.num);
		char* result = new char;
		mod(numa, numb, result);
		Number restemp;
		restemp.num = A2T(result);
		res = restemp.num;
	}

		m_Dis2 = m_Dis2+m_Dis+'=';
		m_Dis = res;
		UpdateData(FALSE);
		//Init
		firstnum.num.Empty();
		secondnum.num.Empty();
		op = 0;
		isend = true;
		if (res.Find('.'))
			point_flag = true;
}
/// <summary>
/// 初始化参数
/// </summary>
void Init()
{
	op = 0;
	point_flag = false;
	poz = 0;
	Number temp;
	temp.num.Empty();
	temp.isnega = false;
	temp.poz = 0;
	firstnum = temp;
	secondnum = temp;
}

/// <summary>
/// “保存”按钮处理
/// </summary>
void CCalculatorDlg::OnBnClickedButton26()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!isend)
		return;
	
	CString tempBuf = m_Dis2 + m_Dis + _T("\r\n");
	int nLength = tempBuf.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP, 0, tempBuf, nLength, NULL, 0, NULL, NULL);
	char* VoicePath = new char[nBytes + 1];
	memset(VoicePath, 0, nLength + 1);
	WideCharToMultiByte(CP_OEMCP, 0, tempBuf, nLength, VoicePath, nBytes, NULL, NULL);
	VoicePath[nBytes] = 0;
	FILE* pfile;
	pfile = fopen(FILE_NAME, "ab+");
	fwrite(VoicePath, sizeof(char), strlen(VoicePath), pfile);
	fclose(pfile);

	CFile file;
	if (file.Open(L"save\\data.txt", CFile::modeRead, NULL))
	{
		char* pBuf;
		DWORD dwFileLen;
		dwFileLen = file.GetLength();
		pBuf = new char[dwFileLen + 1];
		pBuf[dwFileLen] = 0;
		file.Read(pBuf, dwFileLen);
		file.Close();
		USES_CONVERSION;
		m_show = A2T(pBuf);
		delete[] pBuf;
		UpdateData(FALSE);
	}
}

/// <summary>
/// “清除”按钮处理
/// </summary>
void CCalculatorDlg::OnBnClickedButton25()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (MessageBox(_T("确定清除所有记录吗？"), mess + _T("提示"), MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}
	DeleteFile(L"save\\data.txt");
	m_show.Empty();
	UpdateData(FALSE);
	MessageBox(_T("已删除"), mess + _T("提示") );
	
}
