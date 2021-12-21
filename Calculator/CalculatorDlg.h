
// CalculatorDlg.h: 头文件
//
#pragma once
#include <afxpriv.h>
#include "atlconv.h"

#define FILE_DIR "save\\"
#define FILE_NAME "save\\data.txt"

const CString mess(_T("1912080045刘鑫昌1912080128刘亘"));

struct Number
{
	CString num = 0;//数字（正整数）
	int poz = 0;//小数点位置，初始值为0
	bool isnega = false;//是否为负
};
// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBackspace();
	afx_msg void OnCal();
	CString m_Dis;
	afx_msg void OnBnClickedNeg();
	afx_msg void OnBnClickedPt();
	afx_msg void OnBnClickedClear();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedMin();
	afx_msg void OnBnClickedMul();
	afx_msg void OnBnClickedDiv();
	afx_msg void OnBnClickedCe();
	afx_msg void OnBnClickedEqu();
	// IDC_DIS2显示的值
	CString m_Dis2;
	afx_msg void OnBnClickedMod();
	afx_msg void OnBnClickedButton26();
	// 从文件中读取的数据	// 从文件中读取的数据
	CString m_show;
	afx_msg void OnBnClickedButton25();
};
void Init();