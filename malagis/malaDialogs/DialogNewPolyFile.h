#pragma once
#include "Resource.h"

// CDialogNewPolyFile 对话框

class CDialogNewPolyFile : public CDialog
{
	DECLARE_DYNAMIC(CDialogNewPolyFile)

public:
	CDialogNewPolyFile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogNewPolyFile();

// 对话框数据
	enum { IDD = IDD_DIALOG_NEW_POLY_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mPolyFileName;
};
