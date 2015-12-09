#pragma once
#include "afxwin.h"

#include "resource.h"

// CDialogPointInput 对话框

class CDialogPointInput : public CDialog
{
	DECLARE_DYNAMIC(CDialogPointInput)

public:
	CDialogPointInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogPointInput();

// 对话框数据
	enum { IDD = IDD_DIALOG_INPUT_POINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int mPointRadio;
	int mPointStyle;
	int mPointLayer;
	COLORREF mPointColor;
	CComboBox mComboxType;
	afx_msg void OnBnClickedButtonPointColor();
};
