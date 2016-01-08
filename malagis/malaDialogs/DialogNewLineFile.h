#pragma once

#include "resource.h"
// CDialogNewLineFile 对话框

class CDialogNewLineFile : public CDialog
{
	DECLARE_DYNAMIC(CDialogNewLineFile)

public:
	CDialogNewLineFile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogNewLineFile();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEW_LINE_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mLineFileName;
};
