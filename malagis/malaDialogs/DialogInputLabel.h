#pragma once
#include "Resource.h"
#include "afxwin.h"

// CDialogInputLabel 对话框

class CDialogInputLabel : public CDialog
{
	DECLARE_DYNAMIC(CDialogInputLabel)

public:
	CDialogInputLabel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogInputLabel();

// 对话框数据
	enum { IDD = IDD_DIALOG_INPUT_LABEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int mLabelHeight;
	int mLabelWidth;
	int mLabelAngle;
	int mTextAngle;
	int mTextOffset;
	CComboBox mComFont;
	CString	mTextFont;
	COLORREF mTextColor;
	afx_msg void OnBnClickedButtonSetColor();
	CString mTextStr;
	int mWeight;
};
