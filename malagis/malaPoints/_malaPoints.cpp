#include "stdafx.h"
#include "_malaPoints.h"
#include "_malaDialogs.h"

/*
* 输入点
*/
CmalaPointsInput::CmalaPointsInput(CView* mView)
{
	mBaseView = mView;
	GetPointPro();
}
 
CmalaPointsInput::~CmalaPointsInput(){}

void CmalaPointsInput::LButtonDown(UINT nFlags, malaPoint point)
{
	CString a;
	a.Format(_T("%f"), point.x);
	MessageBox(NULL, a, _T("测试输入点"), MB_OK);
}
void CmalaPointsInput::GetPointPro()
{
	if (dlgInputPoint(mPointPro)==false)
	{
		mPointPro.pointStyle = 0;
		mPointPro.pointLayer = -1;
		mPointPro.pointRadio = 1;
		mPointPro.pointColor = RGB(0,0,0);
	}
	//==========debug=====
	CString a;
	a.Format(_T("%d"), mPointPro.pointRadio);
	MessageBox(NULL, a, _T("半径"), MB_OK);
	a.Format(_T("%d"), mPointPro.pointStyle);
	MessageBox(NULL, a, _T("类型"), MB_OK);
	a.Format(_T("%d"), mPointPro.pointLayer);
	MessageBox(NULL, a, _T("图层"), MB_OK);
}