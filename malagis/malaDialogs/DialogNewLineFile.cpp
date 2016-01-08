// DialogNewLineFile.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogNewLineFile.h"
#include "afxdialogex.h"


// CDialogNewLineFile 对话框

IMPLEMENT_DYNAMIC(CDialogNewLineFile, CDialog)

CDialogNewLineFile::CDialogNewLineFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogNewLineFile::IDD, pParent)
	, mLineFileName(_T(""))
{

}

CDialogNewLineFile::~CDialogNewLineFile()
{
}

void CDialogNewLineFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mLineFileName);
}


BEGIN_MESSAGE_MAP(CDialogNewLineFile, CDialog)
END_MESSAGE_MAP()


// CDialogNewLineFile 消息处理程序
