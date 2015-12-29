#pragma once
#include "resource.h"

// CDialogFilePro 对话框

class CDialogFilePro : public CDialog
{
	DECLARE_DYNAMIC(CDialogFilePro)

public:
	CDialogFilePro(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogFilePro();

// 对话框数据
	enum { IDD = IDD_DIALOG_FILE_PRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString mFileName;
	CString mFilePath;
	CString mFileSize;
	CString mCreateTime;
	CString mModifyTime;
};
