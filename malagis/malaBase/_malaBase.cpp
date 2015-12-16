#include "StdAfx.h"
#include "_malaBase.h"
#include <math.h>

/************************************************************************/
/* 屏幕坐标转换函数                                                     */
/************************************************************************/

//屏幕坐标系转换为平面坐标系
void malabasedll ScreenToCoord(long inX, long inY, malaScreen pScreen, double *outX, double *outY)
{
	*outX = pScreen.lbx + inX*pScreen.scale;
	*outY = pScreen.lby + (pScreen.hScreen - inY)*pScreen.scale;
}

//平面坐标系转换为屏幕坐标系
void malabasedll CoordToScreen(double inX, double inY, malaScreen pScreen, long *outX, long *outY)
{
	*outX = (long)(inX - pScreen.lbx) / pScreen.scale;
	*outY = pScreen.hScreen - (long)(inY - pScreen.lby) / pScreen.scale;
}

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
malaCDC::malaCDC(CView* ptView,malaScreen pScreen)
{
	mView = ptView;
	mScreen = pScreen;
}

malaCDC::~malaCDC()
{
}
/*
* 绘制圆点
*/
void malaCDC::pointDrawCircle(malaPoint Point, malaPointPro PntPro)
{
	//MessageBox(NULL, L"绘制圆形", _T("提示"), MB_OK);
	CClientDC dc(mView);

	CPen pen(0, 1, PntPro.pointColor);
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PntPro.pointColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint Point1, Point2;
	CoordToScreen(Point.x - PntPro.pointRadio, Point.y + PntPro.pointRadio, mScreen, &Point1.x, &Point1.y);
	CoordToScreen(Point.x + PntPro.pointRadio, Point.y - PntPro.pointRadio, mScreen, &Point2.x, &Point2.y);
	dc.Ellipse(CRect(Point1, Point2));
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}
/*
* 绘制三角形点
*/
void malaCDC::pointDrawTriangle(malaPoint Point, malaPointPro PntPro)
{
	//MessageBox(NULL, L"绘制三角形", _T("提示"), MB_OK);
	CClientDC dc(mView);
	CPen pen(0, 1, PntPro.pointColor);
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PntPro.pointColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	double radio = PntPro.pointRadio;
	double r1 = sqrtf(3.0) / 2.0 * radio;
	CPoint* MyArray = new CPoint[3];
	
	CoordToScreen(Point.x - r1, Point.y - (double)radio / 2, mScreen, &MyArray[0].x, &MyArray[0].y);
	CoordToScreen(Point.x + r1, Point.y - (double)radio / 2, mScreen, &MyArray[1].x, &MyArray[1].y);
	CoordToScreen(Point.x, Point.y + radio, mScreen, &MyArray[2].x, &MyArray[2].y);

	dc.Polygon(MyArray, 3);
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}
/*
* 绘制矩（方）形点
*/
void malaCDC::pointDrawRect(malaPoint Point, malaPointPro PntPro)
{
	//MessageBox(NULL, L"绘制方形", _T("提示"), MB_OK);
	CClientDC dc(mView);

	CPen pen(0, 1, PntPro.pointColor);
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PntPro.pointColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint Point1, Point2;
	CoordToScreen(Point.x - PntPro.pointRadio, Point.y + PntPro.pointRadio, mScreen, &Point1.x, &Point1.y);
	CoordToScreen(Point.x + PntPro.pointRadio, Point.y - PntPro.pointRadio, mScreen, &Point2.x, &Point2.y);

	dc.Rectangle(CRect(Point1, Point2));
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);

}