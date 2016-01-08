#pragma once

#include "afxwin.h"
#include "resource.h"
// CDialogLineInput 对话框

class CDialogLineInput : public CDialog
{
	DECLARE_DYNAMIC(CDialogLineInput)

public:
	CDialogLineInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogLineInput();

// 对话框数据
	enum { IDD = IDD_DIALOG_INPUT_LINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mComLineStyle;
	int mLineWidth;
	int mLineStyle;
	COLORREF mLineColor;
	afx_msg void OnBnClickedButton1();
};
