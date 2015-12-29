// DialogFilePro.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogFilePro.h"
#include "afxdialogex.h"


// CDialogFilePro 对话框

IMPLEMENT_DYNAMIC(CDialogFilePro, CDialog)

CDialogFilePro::CDialogFilePro(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFilePro::IDD, pParent)
	, mFileName(_T(""))
	, mFilePath(_T(""))
	, mFileSize(_T(""))
	, mCreateTime(_T(""))
	, mModifyTime(_T(""))
{

}

CDialogFilePro::~CDialogFilePro()
{
}

void CDialogFilePro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mFileName);
	DDX_Text(pDX, IDC_EDIT2, mFilePath);
	DDX_Text(pDX, IDC_EDIT3, mFileSize);
	DDX_Text(pDX, IDC_EDIT4, mCreateTime);
	DDX_Text(pDX, IDC_EDIT5, mModifyTime);
}


BEGIN_MESSAGE_MAP(CDialogFilePro, CDialog)
END_MESSAGE_MAP()


// CDialogFilePro 消息处理程序
