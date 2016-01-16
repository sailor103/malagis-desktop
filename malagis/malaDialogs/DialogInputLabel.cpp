// DialogInputLabel.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogInputLabel.h"
#include "afxdialogex.h"


// CDialogInputLabel 对话框

IMPLEMENT_DYNAMIC(CDialogInputLabel, CDialog)

CDialogInputLabel::CDialogInputLabel(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogInputLabel::IDD, pParent)
	, mLabelHeight(30)
	, mLabelWidth(20)
	, mLabelAngle(0)
	, mTextAngle(0)
	, mTextOffset(5)
	, mTextFont(_T("宋体"))
	, mTextStr(_T(""))
	, mWeight(400)
{

}

CDialogInputLabel::~CDialogInputLabel()
{
}

void CDialogInputLabel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LABEL_HEIGHT, mLabelHeight);
	DDV_MinMaxInt(pDX, mLabelHeight, 1, 40);
	DDX_Text(pDX, IDC_EDIT_LABEL_WIDTH, mLabelWidth);
	DDV_MinMaxInt(pDX, mLabelWidth, 1, 40);
	DDX_Text(pDX, IDC_EDIT_LABEL_ANGLE, mLabelAngle);
	DDV_MinMaxInt(pDX, mLabelAngle, 0, 360);
	DDX_Text(pDX, IDC_EDIT_TEXT_ANGLE, mTextAngle);
	DDV_MinMaxInt(pDX, mTextAngle, 0, 360);
	DDX_Text(pDX, IDC_EDIT_TEXT_OFFSET, mTextOffset);
	DDV_MinMaxInt(pDX, mTextOffset, 0, 100000);
	DDX_Control(pDX, IDC_COMBO_FONT, mComFont);
	DDX_Text(pDX, IDC_COMBO_FONT, mTextFont);
	DDX_Text(pDX, IDC_EDIT_STR, mTextStr);
	DDX_Text(pDX, IDC_EDIT_WEIGHT, mWeight);
	DDV_MinMaxInt(pDX, mWeight, 0, 1000);
}


BEGIN_MESSAGE_MAP(CDialogInputLabel, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SET_COLOR, &CDialogInputLabel::OnBnClickedButtonSetColor)
END_MESSAGE_MAP()


// CDialogInputLabel 消息处理程序


void CDialogInputLabel::OnBnClickedButtonSetColor()
{
	// TODO:  在此添加控件通知处理程序代码
	CColorDialog MyCorDlg(mTextColor, CC_FULLOPEN);
	if (MyCorDlg.DoModal() == IDOK)
	{
		mTextColor = MyCorDlg.GetColor();
	}
}
