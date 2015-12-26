// DialogNewPointFile.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogNewPointFile.h"
#include "afxdialogex.h"


// CDialogNewPointFile 对话框

IMPLEMENT_DYNAMIC(CDialogNewPointFile, CDialog)

CDialogNewPointFile::CDialogNewPointFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogNewPointFile::IDD, pParent)
	, mPointFileName(_T(""))
{

}

CDialogNewPointFile::~CDialogNewPointFile()
{
}

void CDialogNewPointFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mPointFileName);
}


BEGIN_MESSAGE_MAP(CDialogNewPointFile, CDialog)
END_MESSAGE_MAP()


// CDialogNewPointFile 消息处理程序
