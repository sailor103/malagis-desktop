#pragma once
#include "Resource.h"

// CDialogNewPloyFile 对话框

class CDialogNewPloyFile : public CDialog
{
	DECLARE_DYNAMIC(CDialogNewPloyFile)

public:
	CDialogNewPloyFile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogNewPloyFile();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEW_PLOY_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mPloyFileName;
};
