#pragma once

#include "resource.h"
// CDialogNewPointFile 对话框

class CDialogNewPointFile : public CDialog
{
	DECLARE_DYNAMIC(CDialogNewPointFile)

public:
	CDialogNewPointFile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogNewPointFile();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEW_POINT_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mPointFileName;
};
