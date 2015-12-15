#include "StdAfx.h"
#include "_malaBase.h"
#include <math.h>

/************************************************************************/
/* 屏幕坐标转换函数                                                     */
/************************************************************************/

//屏幕坐标系转换为平面坐标系
void malabasedll ScreenToCoord(int inX, int inY, malaScreen pScreen, double *outX, double *outY)
{
	*outX = pScreen.lbx + inX*pScreen.scale;
	*outY = pScreen.lby + (pScreen.hScreen - inY)*pScreen.scale;
}

//平面坐标系转换为屏幕坐标系
void malabasedll CoordToScreen(double inX, double inY, malaScreen pScreen, int *outX, int *outY)
{
	*outX = (int)(inX - pScreen.lbx) / pScreen.scale;
	*outY = pScreen.hScreen - (int)(inY - pScreen.lby) / pScreen.scale;
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
	//MessageBox(NULL, L"绘制圆形", _T("提示"), MB_OK);
	CClientDC dc(mView);

	CPen pen(0, 1, PntPro.pointColor);
	CPen* OldPen = dc.SelectObject(&pen);
	CBrush MyBrush(PntPro.pointColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);
	CPoint Point1, Point2;
	Point1.x = Point.x - PntPro.pointRadio;
	Point1.y = Point.y - PntPro.pointRadio;
	Point2.x = Point.x + PntPro.pointRadio;
	Point2.y = Point.y + PntPro.pointRadio;
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
	double r1 = sqrtf(3) / 2 * radio;
	CPoint* MyArray = new CPoint[3];
	MyArray[0].x = Point.x - r1;
	MyArray[0].y = Point.y + (double)radio/2;
	MyArray[1].x = Point.x + r1;
	MyArray[1].y = Point.y + (double)radio / 2;
	MyArray[2].x = Point.x;
	MyArray[2].y = Point.y-radio;

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
	Point1.x = Point.x - PntPro.pointRadio;
	Point1.y = Point.y - PntPro.pointRadio;
	Point2.x = Point.x + PntPro.pointRadio;
	Point2.y = Point.y + PntPro.pointRadio;

	dc.Rectangle(CRect(Point1, Point2));
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);

}