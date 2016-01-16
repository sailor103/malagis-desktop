#include "stdafx.h"
#include "_malaLabel.h"
#include "_malaDialogs.h"
#include "_malaIO.h"

/*
* 输入注释
*/
CmalaLabelsInput::CmalaLabelsInput(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;
	getLabelPro();
	mIsInput = false;
}
CmalaLabelsInput::~CmalaLabelsInput()
{
}
void CmalaLabelsInput::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!mIsInput)
	{
		if (mLabelPro.textStr != L"")
		{
			malaCDC dc(mBaseView, *mScreen);
			dc.textDraw(point, mLabelPro);
			CLabelIO lio;
			lio.labelAdd(point, mLabelPro,mPath);
		}
		else
		{
			MessageBox(mBaseView->m_hWnd, L"输入内容不得为空", L"提示", MB_ICONQUESTION);
		}
		mIsInput = true;
	}
	
}

void CmalaLabelsInput::getLabelPro()
{
	//字体对话框
	if (dlgInputLabel(mLabelPro) == FALSE)
	{
		mLabelPro.labelHeight = 20;    //字体高度
		mLabelPro.labelHeight = 10;     //字体宽度
		mLabelPro.labelAngle = 0;  //字体角度
		mLabelPro.textAngle = 0; //文本角度
		mLabelPro.textColor = RGB(0, 0, 0);//字体颜色
		mLabelPro.textOff = 1;  //字体间距
		mLabelPro.textFont = L"华文楷体";  //字体类型
		mLabelPro.fontWeight = 400;
	}
}