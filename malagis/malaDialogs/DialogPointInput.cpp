// DialogPointInput.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogPointInput.h"
#include "afxdialogex.h"


// CDialogPointInput 对话框

IMPLEMENT_DYNAMIC(CDialogPointInput, CDialog)

CDialogPointInput::CDialogPointInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPointInput::IDD, pParent)
	, mPointRadio(0)
{
	mPointLayer = -1;
	mPointRadio = 1;
	mPointStyle = 0;
	mPointColor = RGB(0, 0, 0);
}

CDialogPointInput::~CDialogPointInput()
{
}

void CDialogPointInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POINT_RADIO, mPointRadio);
	DDX_Control(pDX, IDC_COMBO_POINT_TYPE, mComboxType);
	DDX_CBIndex(pDX, IDC_COMBO_POINT_TYPE, mPointStyle);
	DDV_MinMaxInt(pDX, mPointRadio, 1, 20);
}


BEGIN_MESSAGE_MAP(CDialogPointInput, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_POINT_COLOR, &CDialogPointInput::OnBnClickedButtonPointColor)
END_MESSAGE_MAP()


// CDialogPointInput 消息处理程序


void CDialogPointInput::OnBnClickedButtonPointColor()
{
	// TODO:  在此添加控件通知处理程序代码
	CColorDialog MyCorDlg;
	if (MyCorDlg.DoModal() == IDOK)
	{
		mPointColor = MyCorDlg.GetColor();
	}
}
