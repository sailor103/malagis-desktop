#pragma once
#include "Resource.h"

// CDialogNewLabel 对话框

class CDialogNewLabel : public CDialog
{
	DECLARE_DYNAMIC(CDialogNewLabel)

public:
	CDialogNewLabel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogNewLabel();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEW_LABEL_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mLabelName;
};
