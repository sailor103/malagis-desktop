// DialogNewPolyFile.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogNewPolyFile.h"
#include "afxdialogex.h"


// CDialogNewPolyFile 对话框

IMPLEMENT_DYNAMIC(CDialogNewPolyFile, CDialog)

CDialogNewPolyFile::CDialogNewPolyFile(CWnd* pParent /*=NULL*/)
: CDialog(CDialogNewPolyFile::IDD, pParent)
, mPolyFileName(_T(""))
{

}

CDialogNewPolyFile::~CDialogNewPolyFile()
{
}

void CDialogNewPolyFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_POLY_FILE, mPolyFileName);
}


BEGIN_MESSAGE_MAP(CDialogNewPolyFile, CDialog)
END_MESSAGE_MAP()


// CDialogNewPolyFile 消息处理程序
