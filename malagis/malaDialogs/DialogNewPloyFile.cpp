// DialogNewPloyFile.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogNewPloyFile.h"
#include "afxdialogex.h"


// CDialogNewPloyFile 对话框

IMPLEMENT_DYNAMIC(CDialogNewPloyFile, CDialog)

CDialogNewPloyFile::CDialogNewPloyFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogNewPloyFile::IDD, pParent)
	, mPloyFileName(_T(""))
{

}

CDialogNewPloyFile::~CDialogNewPloyFile()
{
}

void CDialogNewPloyFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_PLOY_FILE, mPloyFileName);
}


BEGIN_MESSAGE_MAP(CDialogNewPloyFile, CDialog)
END_MESSAGE_MAP()


// CDialogNewPloyFile 消息处理程序
