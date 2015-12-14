#include "StdAfx.h"
#include "_malaBase.h"
#include <math.h>

CmalaMouseAction::CmalaMouseAction()
{
	mBaseView = NULL;
}

CmalaMouseAction::~CmalaMouseAction(){}

void CmalaMouseAction::LButtonDown(UINT nFlags, malaPoint point){}

void CmalaMouseAction::LButtonUp(UINT nFlags, malaPoint point){}

void CmalaMouseAction::RButtonDown(UINT nFlags, malaPoint point){}

void CmalaMouseAction::RButtonUp(UINT nFlags, malaPoint point){}

void CmalaMouseAction::MouseMove(UINT nFlags, malaPoint point){}

void CmalaMouseAction::MouseWheel(UINT nFlags, short zDelta, malaPoint pt){}


/************************************************************************/
/* malaCDC类实现代码                                                    */
/************************************************************************/

/*
* 绘图类构造析构实现 
*/
malaCDC::malaCDC(CView* ptView)
{
	mView = ptView;
}

malaCDC::~malaCDC()
{
}
/*
* 绘制圆点
*/
void malaCDC::pointDrawCircle(malaPoint Point, malaPointPro PntPro)
{
	MessageBox(NULL, L"圆形", _T("提示"), MB_OK);
}
/*
* 绘制三角形点
*/
void malaCDC::pointDrawTriangle(malaPoint Point, malaPointPro PntPro)
{
	MessageBox(NULL, L"三角形", _T("提示"), MB_OK);
}
/*
* 绘制矩（方）形点
*/
void malaCDC::pointDrawRect(malaPoint Point, malaPointPro PntPro)
{
	MessageBox(NULL, L"方形", _T("提示"), MB_OK);

}