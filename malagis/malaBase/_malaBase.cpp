#include "StdAfx.h"
#include "_malaBase.h"
#include <math.h>

const double pi = 3.1415926;

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
* 绘制选中状态的外接圆
*/
void malaCDC::drawSelectCirclePoint(malaPoint Point, malaPointPro PntPro)
{
	PntPro.pointRadio++;

	CClientDC dc(mView);

	LOGBRUSH log;
	log.lbColor = RGB(255, 0, 0);
	log.lbStyle = BS_SOLID;

	CPen pen(PS_GEOMETRIC | PS_DASH, 2, &log);
	CPen* OldPen = dc.SelectObject(&pen);

	CPoint Point1, Point2;
	CoordToScreen(Point.x - PntPro.pointRadio, Point.y + PntPro.pointRadio, mScreen, &Point1.x, &Point1.y);
	CoordToScreen(Point.x + PntPro.pointRadio, Point.y - PntPro.pointRadio, mScreen, &Point2.x, &Point2.y);

	dc.Ellipse(CRect(Point1, Point2));
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
* 绘制一个多边形实现
*/
void malaCDC::polyDraw(vector<malaPoint>& Poly, malaPolyPro PolyPro)
{
	int PolyNum = Poly.size();
	CClientDC dc(mView);

	CBrush MyBrush(PolyPro.fillStyle, PolyPro.fillColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);

	LOGBRUSH log;
	log.lbColor = PolyPro.borderColor;
	log.lbStyle = BS_SOLID;
	CPen Pen(PS_GEOMETRIC | PolyPro.borderStyle, PolyPro.borderWidth, &log);

	CPen* OldPen = dc.SelectObject(&Pen);
	CPoint* PointArray = new CPoint[PolyNum];
	for (int i = 0; i < PolyNum; i++)
	{
		CoordToScreen(Poly[i].x, Poly[i].y, mScreen, &PointArray[i].x, &PointArray[i].y);
	}
	dc.Polygon(PointArray, PolyNum);
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
	delete[]PointArray;
}

/*
* 绘制一个多边形实现（橡皮）
*/
void malaCDC::polyDrawX(vector<malaPoint>& Poly, malaPolyPro PolyPro)
{
	int PolyNum = Poly.size();
	CClientDC dc(mView);
	dc.SetROP2(R2_NOTXORPEN);

	CBrush MyBrush(PolyPro.fillStyle, PolyPro.fillColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);

	LOGBRUSH log;
	log.lbColor = PolyPro.borderColor;
	log.lbStyle = BS_SOLID;
	CPen Pen(PS_GEOMETRIC | PolyPro.borderStyle, PolyPro.borderWidth, &log);

	CPen* OldPen = dc.SelectObject(&Pen);
	CPoint* PointArray = new CPoint[PolyNum];
	for (int i = 0; i < PolyNum; i++)
	{
		CoordToScreen(Poly[i].x, Poly[i].y, mScreen, &PointArray[i].x, &PointArray[i].y);
	}
	dc.Polygon(PointArray, PolyNum);
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
	delete[]PointArray;
}

/*
* 根据一个多边形的外包矩形绘制一个椭圆实现
*/
void malaCDC::ellipseDraw(vector<malaPoint>& Poly, malaPolyPro PolyPro)
{
	CClientDC dc(mView);

	CBrush MyBrush(PolyPro.fillStyle, PolyPro.fillColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);

	LOGBRUSH log;
	log.lbColor = PolyPro.borderColor;
	log.lbStyle = BS_SOLID;
	CPen Pen(PS_GEOMETRIC | PolyPro.borderStyle, PolyPro.borderWidth, &log);
	CPen* OldPen = dc.SelectObject(&Pen);

	malaLogic tmplog;
	malaRect polyrect = tmplog.getRect(Poly);
	CPoint A, B;
	CoordToScreen(polyrect.xmin, polyrect.ymin, mScreen, &A.x, &A.y);
	CoordToScreen(polyrect.xmax, polyrect.ymax, mScreen, &B.x, &B.y);
	dc.Ellipse(CRect(A,B));
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}

/*
* 根据一个多边形的外包矩形绘制一个椭圆实现（橡皮）
*/
void malaCDC::ellipseDrawX(vector<malaPoint>& Poly, malaPolyPro PolyPro)
{
	CClientDC dc(mView);
	dc.SetROP2(R2_NOTXORPEN);
	CBrush MyBrush(PolyPro.fillStyle, PolyPro.fillColor);
	CBrush* OldBrush = dc.SelectObject(&MyBrush);

	LOGBRUSH log;
	log.lbColor = PolyPro.borderColor;
	log.lbStyle = BS_SOLID;
	CPen Pen(PS_GEOMETRIC | PolyPro.borderStyle, PolyPro.borderWidth, &log);
	CPen* OldPen = dc.SelectObject(&Pen);

	malaLogic tmplog;
	malaRect polyrect = tmplog.getRect(Poly);
	CPoint A, B;
	CoordToScreen(polyrect.xmin, polyrect.ymin, mScreen, &A.x, &A.y);
	CoordToScreen(polyrect.xmax, polyrect.ymax, mScreen, &B.x, &B.y);
	dc.Ellipse(CRect(A, B));
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
}

/*
* 自动绘制一个多边形
*/
void malaCDC::polyDrawAuto(vector<malaPoint>& Poly, malaPolyPro PolyPro)
{
	if (PolyPro.polyStyle == 0)
		polyDraw(Poly, PolyPro);
	if (PolyPro.polyStyle == 1)
		ellipseDraw(Poly, PolyPro);
}
/*
* 自动绘制一个多边形(橡皮)
*/
void malaCDC::polyDrawAutoX(vector<malaPoint>& Poly, malaPolyPro PolyPro)
{
	if (PolyPro.polyStyle == 0)
		polyDrawX(Poly, PolyPro);
	if (PolyPro.polyStyle == 1)
		ellipseDrawX(Poly, PolyPro);
}
/*
* 绘制文字
*/
void malaCDC::textDraw(malaPoint Point, malaLabelPro &labelPro)
{
	CClientDC dc(mView);

	CFont cjcf;								//定义一个字模
	long high, wide, cc1, cc2, cd, angg;
	float x1, y1, ang1;
	CString tmpStr;

	high =labelPro.labelHeight/mScreen.scale; //得到字体的点阵高度

	ang1 = (float)(labelPro.labelAngle*pi / 180);
	angg = (int)(labelPro.textAngle * 10);
	wide = labelPro.labelWidth / mScreen.scale;;//得到字体的点阵宽度

	//起始点的屏幕点阵坐标
	x1 = Point.x; y1 = Point.y;
	CoordToScreen(x1, y1, mScreen, &cc1, &cc2);

	//创建字模
	cjcf.CreateFont(high, wide, angg, 0, labelPro.fontWeight, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, labelPro.textFont);
	
	//选中字模
	CFont* cjcbakf = dc.SelectObject(&cjcf);
	dc.SetBkMode(TRANSPARENT);				//设定显示方式
	dc.SetTextColor(labelPro.textColor);   //设定文本颜色
	tmpStr = labelPro.textStr;              //文本内容
	cd = tmpStr.GetLength();			    //文本字符长度
	int textPos = 0;
	while (cd > 0)								
	{
		CString outStr = tmpStr.Mid(textPos, 1 );
		dc.TextOut(cc1, cc2, outStr);		//在屏幕上写这个汉字
		cd--;						//字符数减1
		textPos++;
		//下一个字符的显示位置
		x1 = x1 + (labelPro.labelWidth * 2 + labelPro.textOff)*(float)cos(ang1);
		y1 = y1 + (labelPro.labelWidth * 2 + labelPro.textOff)*(float)sin(ang1);
		//下一个字符显示位置的屏幕坐标
		CoordToScreen(x1, y1,mScreen, &cc1, &cc2);

	}
	dc.SelectObject(cjcbakf);				//恢复字模
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

/*
* 判断两条直线是否相交
*/
bool  malaLogic::isLineIntersect(malaPoint startPointA, malaPoint endPointA, malaPoint startPointB, malaPoint endPointB)
{
	double x1 = startPointA.x;
	double y1 = startPointA.y;
	double x2 = endPointA.x;
	double y2 = endPointA.y;
	double x3 = startPointB.x;
	double y3 = startPointB.y;
	double x4 = endPointB.x;
	double y4 = endPointB.y;
	double result = (x2 - x1)*(y4 - y3) - (x4 - x3)*(y2 - y1);
	if (result)
	{
		double G_x1y1 = (y1 - y3)*(x4 - x3) - (y4 - y3)*(x1 - x3);
		double G_x2y2 = (y2 - y3)*(x4 - x3) - (y4 - y3)*(x2 - x3);
		double F_x3y3 = (y3 - y1)*(x2 - x1) - (y2 - y1)*(x3 - x1);
		double F_x4y4 = (y4 - y1)*(x2 - x1) - (y2 - y1)*(x4 - x1);
		if (F_x3y3*F_x4y4 <= 0 && G_x1y1*G_x2y2 <= 0)
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}

/*
* 判断折线是否和矩形相交
*/
bool malaLogic::isLineInRect(malaRect& rc, vector<malaPoint>& Line)
{
	malaPoint A, B, C, D;
	A.x = rc.xmin - 2;
	A.y = rc.ymin - 2;
	B.x = rc.xmax + 2;
	B.y = rc.ymin + 2;
	C.x = rc.xmax + 2;
	C.y = rc.ymax + 2;
	D.x = rc.xmin - 2;
	D.y = rc.ymax + 2;
	if (isLinePolylineIntersect(A, B, Line))
		return TRUE;
	if (isLinePolylineIntersect(B, C, Line))
		return TRUE;
	if (isLinePolylineIntersect(C, D, Line))
		return TRUE;
	if (isLinePolylineIntersect(A, D, Line))
		return TRUE;
	return FALSE;
}

/*
* 判断直线是否与折线相交
*/
bool malaLogic::isLinePolylineIntersect(malaPoint startPointA, malaPoint endPointA, vector<malaPoint>& Line)
{
	int Size = Line.size();
	for (int i = 1; i < Size; i++)
	{
		if (isLineIntersect(startPointA, endPointA, Line[i - 1], Line[i]))
			return TRUE;
	}
	return FALSE;
}

/*
* 判断区是否和矩形相交
*/
bool malaLogic::isPolyInRect(malaRect& rc, vector<malaPoint>& Poly)
{
	malaPoint A, B, C, D;
	A.x = rc.xmin - 2;
	A.y = rc.ymin - 2;
	B.x = rc.xmax + 2;
	B.y = rc.ymin + 2;
	C.x = rc.xmax + 2;
	C.y = rc.ymax + 2;
	D.x = rc.xmin - 2;
	D.y = rc.ymax + 2;
	if (isLinePolyIntersect(A, B, Poly))
		return TRUE;
	if (isLinePolyIntersect(B, C, Poly))
		return TRUE;
	if (isLinePolyIntersect(C, D, Poly))
		return TRUE;
	if (isLinePolyIntersect(A, D, Poly))
		return TRUE;
	return FALSE;
}

/*
* 判断直线是否与多边形相交
*/
bool malaLogic::isLinePolyIntersect(malaPoint startPointA, malaPoint endPointA, vector<malaPoint>& Poly)
{
	int Size = Poly.size();
	for (int i = 1; i < Size; i++)
	{
		if (isLineIntersect(startPointA, endPointA, Poly[i - 1], Poly[i]))
			return TRUE;
	}
	//判断起点和终点的线是否相交
	if (isLineIntersect(startPointA, endPointA, Poly[0], Poly[Size-1]))
		return TRUE;
	return FALSE;
}

/*
* 剪断线
*/
bool malaLogic::cutLine(malaPoint point, vector<malaPoint>& Line1, vector<malaPoint>& Line2)
{
	vector<malaPoint>Line;
	Line = Line1;
	int length = Line1.size();
	int pos = 0;
	bool cutflag = FALSE;
	for (int i = 1; i < length; i++)
	{
		if (isPointInLine(point, Line[i - 1], Line[i]))
		{
			pos = i;
			cutflag = TRUE;
			break;
		}
	}

	if (cutflag)
	{
		Line1.clear();
		int j;
		for (j = 0; j < pos; j++)
			Line1.push_back(Line[j]);
		Line1.push_back(point);

		Line2.push_back(point);
		for (j = pos; j < length; j++)
			Line2.push_back(Line[j]);

		return TRUE;
	}

	return FALSE;

}

/*
* 判断点是否在线上
*/
bool  malaLogic::isPointInLine(malaPoint point, malaPoint startPoint, malaPoint endPoint)
{
	long AX = startPoint.x;
	long AY = startPoint.y;
	long BX = endPoint.x;
	long BY = endPoint.y;
	long PX = point.x;
	long PY = point.y;

	double dx_AB = AX - BX;
	double dy_AB = AY - BY;
	double dx_PA = PX - AX;
	double dy_PA = PY - AY;
	double dx_PB = PX - BX;
	double dy_PB = PY - BY;

	double AB = sqrt(dx_AB*dx_AB + dy_AB*dy_AB);
	double PA = sqrt(dx_PA*dx_PA + dy_PA*dy_PA);
	double PB = sqrt(dx_PB*dx_PB + dy_PB*dy_PB);
	double rate = abs(PA + PB - AB) / AB;
	if (rate < 0.001)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
* 线上加点实现
*/
bool malaLogic::addPointInLine(malaPoint point, vector<malaPoint>& Line)
{
	bool Tug = FALSE;
	int length = Line.size();
	vector<malaPoint>MyLine;
	int pos = 0;
	for (int i = 1; i < length; i++)
	{
		if (isPointInLine(point, Line[i - 1], Line[i]))
		{
			Tug = TRUE;
			pos = i;
		}
		MyLine.push_back(Line[i - 1]);
		if (Tug)
			break;
	}

	if (Tug)
	{
		MyLine.push_back(point);
		for (int j = pos; j < length; j++)
		{
			MyLine.push_back(Line[j]);
		}
		Line = MyLine;
		MyLine.clear();
		return TRUE;
	}
	return FALSE;
}

/*
* 计算两点之间距离
*/
double malaLogic::distancePointToPoint(malaPoint point1, malaPoint point2)
{
	double x1, y1;
	double x2, y2;
	double dis(0.0);
	x1 = point1.x; y1 = point1.y;
	x2 = point2.x; y2 = point2.y;
	dis = sqrt(double((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
	return dis;
}

/*
* 得到点在线的位置
*/
int malaLogic::getPointPosInLine(malaPoint point, vector<malaPoint>& Line)
{
	int length = Line.size();
	double dis = 0.0;
	for (int i = 0; i < length; i++)
	{
		dis = distancePointToPoint(point, Line[i]);
		if (dis <= 5)
			return i;
	}
	return -1;
}

/*
* 边界加点实现
*/
bool malaLogic::addPointPoly(malaPoint point, vector<malaPoint>& Poly)
{
	if (Poly.size() >= 2)
	{
		bool Tug = FALSE;
		int length = Poly.size();
		if (isPointInLine(point, Poly[0], Poly[length - 1]))
		{
			Poly.push_back(point);
			return TRUE;
		}
		vector<malaPoint>MyPoly;
		int pos = 0;
		for (int i = 1; i < length; i++)
		{
			if (isPointInLine(point, Poly[i - 1], Poly[i]))
			{
				Tug = TRUE;
				pos = i;
			}
			MyPoly.push_back(Poly[i - 1]);
			if (Tug)
				break;
		}

		if (Tug)
		{
			MyPoly.push_back(point);
			for (int j = pos; j < length; j++)
			{
				MyPoly.push_back(Poly[j]);
			}
			Poly = MyPoly;
			MyPoly.clear();
			return TRUE;
		}
		return FALSE;
	}
	else
		return false;
	
}

/*
* 边界删点实现
*/
bool malaLogic::delPointPoly(malaPoint point, vector<malaPoint>& Poly)
{
	bool tug = FALSE;
	int length = Poly.size();
	if (length <= 3)
		return FALSE;
	double dis = 0.0;
	vector<malaPoint>MyPoints;
	int pos = 0;
	int i;
	for (i = 0; i < length; i++)
	{
		dis = distancePointToPoint(point, Poly[i]);
		if (dis <= 3)
		{
			tug = TRUE;
			pos = i;
			break;
		}
		MyPoints.push_back(Poly[i]);
	}
	if (tug)
	{
		if (pos < length - 1)
		{
			for (i = pos + 1; i < length; i++)
				MyPoints.push_back(Poly[i]);
		}
		Poly = MyPoints;
		MyPoints.clear();
		return TRUE;
	}
	return FALSE;
}