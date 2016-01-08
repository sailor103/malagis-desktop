// DialogLineInput.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogLineInput.h"
#include "afxdialogex.h"


// CDialogLineInput 对话框

IMPLEMENT_DYNAMIC(CDialogLineInput, CDialog)

CDialogLineInput::CDialogLineInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogLineInput::IDD, pParent)
	, mLineWidth(1), mLineStyle(0), mLineColor(0)
{
}

CDialogLineInput::~CDialogLineInput()
{
}

void CDialogLineInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LINE_STYLE, mComLineStyle);
	DDX_CBIndex(pDX, IDC_COMBO_LINE_STYLE, mLineStyle);
	DDX_Text(pDX, IDC_EDIT_LINE_WIDTH, mLineWidth);
	DDV_MinMaxInt(pDX, mLineWidth, 1, 20);
}


BEGIN_MESSAGE_MAP(CDialogLineInput, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogLineInput::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDialogLineInput 消息处理程序


void CDialogLineInput::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CColorDialog MyCorDlg(mLineColor, CC_FULLOPEN);
	if (MyCorDlg.DoModal() == IDOK)
	{
		mLineColor = MyCorDlg.GetColor();
	}
}
