#include "stdafx.h"
#include "_malaPoints.h"
#include "_malaDialogs.h"
#include "_malaIO.h"

/*
*  ‰»Îµ„
*/
CmalaPointsInput::CmalaPointsInput(CView* mView, malaScreen *pScreen,CString &fileFulPath)
{
	mBaseView = mView;
	mScreen = pScreen;
	mPath = fileFulPath;
	GetPointPro();
}
 
CmalaPointsInput::~CmalaPointsInput(){}

void CmalaPointsInput::LButtonDown(UINT nFlags, malaPoint point)
{
	malaCDC dc(mBaseView, *mScreen);
	switch (mPointPro.pointStyle)
	{
	case 0:
		dc.pointDrawRect(point, mPointPro);
		break;
	case 1:
		dc.pointDrawTriangle(point, mPointPro);
		break;
	case 2:
		dc.pointDrawCircle(point, mPointPro);
		break;
	default:
		break;
	}
	CPointIO pio;
	pio.pointAdd(point, mPointPro, mPath);

}
void CmalaPointsInput::GetPointPro()
{
	if (dlgInputPoint(mPointPro)==false)
	{
		mPointPro.pointStyle = 0;
		mPointPro.pointRadio = 1;
		mPointPro.pointColor = RGB(0,0,0);
	}
}