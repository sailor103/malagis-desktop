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
* 根据点型自动绘制点
*/
void malaCDC::pointDrawAuto(malaPoint Point, malaPointPro PntPro)
{
	switch (PntPro.pointStyle)
	{
	case 0:
		pointDrawRect(Point, PntPro);
		break;
	case 1:
		pointDrawTriangle(Point, PntPro);
		break;
	case 2:
		pointDrawCircle(Point, PntPro);
		break;
	default:
		break;
	}
}

/*
* 根据点型自动绘制点(橡皮)
*/
void malaCDC::pointDrawAutoX(malaPoint Point, malaPointPro PntPro)
{
	switch (PntPro.pointStyle)
	{
	case 0:
		pointDrawRectX(Point, PntPro);
		break;
	case 1:
		pointDrawTriangleX(Point, PntPro);
		break;
	case 2:
		pointDrawCircleX(Point, PntPro);
		break;
	default:
		break;
	}
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
//圆点（橡皮）
void malaCDC::pointDrawCircleX(malaPoint Point, malaPointPro PntPro)
{
	//MessageBox(NULL, L"绘制圆形", _T("提示"), MB_OK);
	CClientDC dc(mView);
	dc.SetROP2(R2_NOTXORPEN);
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
//三角形（橡皮）
void malaCDC::pointDrawTriangleX(malaPoint Point, malaPointPro PntPro)
{
	//MessageBox(NULL, L"绘制三角形", _T("提示"), MB_OK);
	CClientDC dc(mView);
	dc.SetROP2(R2_NOTXORPEN);
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
//方形点（橡皮）
void malaCDC::pointDrawRectX(malaPoint Point, malaPointPro PntPro)
{
	//MessageBox(NULL, L"绘制方形", _T("提示"), MB_OK);
	CClientDC dc(mView);
	dc.SetROP2(R2_NOTXORPEN);
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

/*
* 绘制空心矩形
*/
void malaCDC::drawRectNULLFill(malaPoint Point1, malaPoint point2)
{
	CClientDC dc(mView);
	dc.SetROP2(R2_NOTXORPEN);
	CPen pen(PS_DASH, 1, RGB(255, 0, 0));
	CPen* OldPen = dc.SelectObject(&pen);

	CPoint MyPoint1;
	CPoint MyPoint2;
	CoordToScreen(Point1.x, Point1.y, mScreen, &MyPoint1.x, &MyPoint1.y);
	CoordToScreen(point2.x, point2.y, mScreen, &MyPoint2.x, &MyPoint2.y);
	CRect re(MyPoint1, MyPoint2);
	dc.Rectangle(re);
	dc.SelectObject(OldPen);
}
/*
* 绘制选中状态的外接矩形
*/
void malaCDC::drawSelectRectPoint(malaPoint Point, malaPointPro PntPro)
{
	PntPro.pointRadio++;
	
	CClientDC dc(mView);

	LOGBRUSH log;
	log.lbColor = RGB(0 ,139, 139);
	log.lbStyle = BS_SOLID;

	CPen pen(PS_GEOMETRIC | PS_DASH, 2, &log);
	CPen* OldPen = dc.SelectObject(&pen);
	
	CPoint Point1, Point2;
	CoordToScreen(Point.x - PntPro.pointRadio, Point.y + PntPro.pointRadio, mScreen, &Point1.x, &Point1.y);
	CoordToScreen(Point.x + PntPro.pointRadio, Point.y - PntPro.pointRadio, mScreen, &Point2.x, &Point2.y);

	dc.Rectangle(CRect(Point1, Point2));
	dc.SelectObject(OldPen);

}

/*
* 绘制直线实现
*/
void malaCDC::lineDraw(malaPoint PointStart, malaPoint PointEnd, malaLinePro LinePro)
{
	CClientDC dc(mView);

	COLORREF cor = LinePro.lineColor;
	int LineWide = ceil((double)LinePro.lineWidth / mScreen.scale);
	int LineStyle = LinePro.lineStyle;

	LOGBRUSH log;
	log.lbColor = cor;
	log.lbStyle = BS_SOLID;
	CPen Pen(PS_GEOMETRIC | LineStyle, LineWide, &log);

	CPen* OldPen = dc.SelectObject(&Pen);
	CPoint Point1;
	CPoint Point2;
	CoordToScreen(PointStart.x, PointStart.y, mScreen,&Point1.x, &Point1.y);
	CoordToScreen(PointEnd.x, PointEnd.y, mScreen, &Point2.x, &Point2.y);
	dc.MoveTo(Point1);
	dc.LineTo(Point2);
	dc.SelectObject(OldPen);
}

/*
* 绘制直线实现（橡皮）
*/
void malaCDC::lineDrawX(malaPoint PointStart, malaPoint PointEnd, malaLinePro LinePro)
{
	CClientDC dc(mView);
	dc.SetROP2(R2_NOTXORPEN);
	COLORREF cor = LinePro.lineColor;
	int LineWide = ceil((double)LinePro.lineWidth / mScreen.scale);
	int LineStyle = LinePro.lineStyle;
	
	LOGBRUSH log;
	log.lbColor = cor;
	log.lbStyle = BS_SOLID;
	CPen Pen(PS_GEOMETRIC | LineStyle, LineWide, &log);

	CPen* OldPen = dc.SelectObject(&Pen);
	CPoint Point1;
	CPoint Point2;
	CoordToScreen(PointStart.x, PointStart.y, mScreen, &Point1.x, &Point1.y);
	CoordToScreen(PointEnd.x, PointEnd.y, mScreen, &Point2.x, &Point2.y);
	dc.MoveTo(Point1);
	dc.LineTo(Point2);
	dc.SelectObject(OldPen);
}

/*
* 绘制一条折线
*/
void malaCDC::lineDrawAll(vector<malaPoint>& Line, malaLinePro LinePro)
{
	int LineNum = Line.size();
	for (int i = 1; i < LineNum; i++)
		lineDraw(Line[i - 1], Line[i], LinePro);
}

/*
* 绘制一条折线（橡皮）
*/
void malaCDC::lineDrawAllX(vector<malaPoint>& Line, malaLinePro LinePro)
{
	int LineNum = Line.size();
	for (int i = 1; i < LineNum; i++)
		lineDrawX(Line[i - 1], Line[i], LinePro);
}


/*
* 逻辑运算基类实现
*/
malaLogic::malaLogic(){}
malaLogic::~malaLogic(){}

//判断点是否在矩形内
bool malaLogic::isPntInRect(malaPoint &Point, malaRect& rc)
{
	if ((Point.x >= (rc.xmin - 4)) && (Point.x <= (rc.xmax + 4)) && (Point.y >= (rc.ymin - 4)) && (Point.y <= (rc.ymax + 4)))
		return true;
	return false;
}
/*
*返回一个图元的外接矩形
*/
malaRect malaLogic::getRect(vector<malaPoint>& Point)
{
	int LineNum = Point.size();
	malaRect rect;
	rect.xmax = getMaxX(Point);
	rect.ymax = getMaxY(Point);
	rect.xmin = getMinX(Point);
	rect.ymin = getMinY(Point);
	return rect;
}
/*
* 获取最大的X
*/
double malaLogic::getMaxX(vector<malaPoint>& Point)
{
	int LineNum = Point.size();
	int pos = 0;
	for (int i = 1; i < LineNum; i++)
	{
		if (Point[pos].x < Point[i].x)
			pos = i;
	}
	return Point[pos].x;
}
/*
* 获取最大的Y
*/
double malaLogic::getMaxY(vector<malaPoint>& Point)
{
	int LineNum = Point.size();
	int pos = 0;
	for (int i = 1; i < LineNum; i++)
	{
		if (Point[pos].y < Point[i].y)
			pos = i;
	}
	return Point[pos].y;
}
/*
* 获取最小的X
*/
double malaLogic::getMinX(vector<malaPoint>& Point)
{

	int LineNum = Point.size();
	int pos = 0;
	for (int i = 1; i < LineNum; i++)
	{
		if (Point[pos].x >= Point[i].x)
			pos = i;
	}
	return Point[pos].x;
}
/*
* 获取最小的Y
*/
double malaLogic::getMinY(vector<malaPoint>& Point)
{
	int LineNum = Point.size();
	int pos = 0;
	for (int i = 1; i < LineNum; i++)
	{
		if (Point[pos].y >= Point[i].y)
			pos = i;
	}
	return Point[pos].y;
}
/*
* 判断两个矩形是否相交（不能判断包含）
*/
bool malaLogic::isRectIntersect(malaRect &r1, malaRect &r2)
{
	if (abs((r1.xmin + r1.xmax) / 2.0 - (r2.xmin + r2.xmax) / 2.0) < ((r1.xmax + r2.xmax - r1.xmin - r2.xmin) / 2.0) && abs((r1.ymin + r1.ymax) / 2.0 - (r2.ymin + r2.ymax) / 2.0) < ((r1.ymax + r2.ymax - r1.ymin - r2.ymin) / 2.0))
		return true;
	return false;
}