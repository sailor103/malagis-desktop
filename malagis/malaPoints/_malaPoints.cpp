#include "stdafx.h"
#include "_malaPoints.h"

/*
* 输入点
*/
CmalaPointsInput::CmalaPointsInput(CView* mView)
{
	mBaseView = mView;
}

CmalaPointsInput::~CmalaPointsInput(){}

void CmalaPointsInput::LButtonDown(UINT nFlags, malaPoint point)
{
	CString a;
	a.Format(_T("%f"), point.x);
	MessageBox(NULL, a, _T("测试输入点"), MB_OK);
}