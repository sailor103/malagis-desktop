#ifndef _MALABASE_H_
#define _MALABASE_H_

#ifndef _MALABASE_EXPORT
#define malabasedll  __declspec(dllimport)
#else
#define malabasedll  __declspec(dllexport)
#endif

#include "malaStruct.h"
#include "_malaBase.h"
#include <vector>
using namespace std;

/*
* 屏幕坐标转换函数
*/

void malabasedll ScreenToCoord(long inX, long inY, malaScreen pScreen, double *outX, double *outY);//屏幕坐标系转换为平面坐标系
void malabasedll CoordToScreen(double inX, double inY, malaScreen pScreen, long *outX, long *outY);//平面坐标系转换为屏幕坐标系

/*
* 鼠标操作基类
*/
class malabasedll CmalaMouseAction
{
public:
	CmalaMouseAction();
	virtual ~CmalaMouseAction();
	virtual void LButtonDown (UINT nFlags, malaPoint point);
	virtual void LButtonUp(UINT nFlags, malaPoint point);
	virtual void RButtonDown(UINT nFlags, malaPoint point);
	virtual void RButtonUp(UINT nFlags, malaPoint point);
	virtual void MouseMove(UINT nFlags, malaPoint point);
	virtual void MouseWheel(UINT nFlags, short zDelta, malaPoint pt);

	CView* mBaseView;
};

/*
* 绘图类
*/
class malabasedll malaCDC
{
public:
	malaCDC(CView* ptView,malaScreen pScreen);
	~malaCDC();
public:
	void pointDrawAuto(malaPoint Point, malaPointPro PntPro);//根据点型自动绘制点
	void pointDrawAutoX(malaPoint Point, malaPointPro PntPro);//根据点型自动绘制点(橡皮)

	void pointDrawCircle(malaPoint Point, malaPointPro PntPro);//绘制一个圆点
	void pointDrawCircleX(malaPoint Point, malaPointPro PntPro);//绘制一个圆点(橡皮)
	void pointDrawRect(malaPoint Point, malaPointPro PntPro);//绘制一个矩形点
	void pointDrawRectX(malaPoint Point, malaPointPro PntPro);//绘制一个矩形点(橡皮)
	void pointDrawTriangle(malaPoint Point, malaPointPro PntPro);//绘制一个三角形点
	void pointDrawTriangleX(malaPoint Point, malaPointPro PntPro);//绘制一个三角形点(橡皮)

	void lineDraw(malaPoint PointStart, malaPoint PointEnd, malaLinePro LinePro); //绘制直线
	void lineDrawX(malaPoint PointStart, malaPoint PointEnd, malaLinePro LinePro);//绘制直线（橡皮）
	void lineDrawAll(vector<malaPoint>& Line, malaLinePro LinePro);//绘制一条折线
	void lineDrawAllX(vector<malaPoint>& Line, malaLinePro LinePro);//绘制一条折线（橡皮）
	
	void drawSelectRectPoint(malaPoint Point, malaPointPro PntPro);//绘制选中状态的外接矩形
	void drawSelectCirclePoint(malaPoint Point, malaPointPro PntPro);//绘制选中状态的外接圆

	void drawRectNULLFill(malaPoint Point1, malaPoint point2);//绘制空心矩形

private:
	CView* mView;//绘图指针
	malaScreen mScreen;

};

/*
*逻辑运算基类
*/
class malabasedll malaLogic
{
public:
	malaLogic();
	~malaLogic();
public:
	
	double getMaxX(vector<malaPoint>& Point);//从所有的点中找到最大的x
	double getMaxY(vector<malaPoint>& Point);//从所有的点中找到最大的y
	double getMinX(vector<malaPoint>& Point);//从所有的点中找到最小的x
	double getMinY(vector<malaPoint>& Point);//从所有的点中找到最小的y
	
	malaRect getRect(vector<malaPoint>& Point);//返回一个图元的外接矩形
public:
	bool isPntInRect(malaPoint &Point, malaRect& rc);//点是否在矩形内部
	bool isRectIntersect(malaRect &r1, malaRect &r2);//判断两个矩形是否相交（不能判断包含）

	bool isLineIntersect(malaPoint startPointA, malaPoint endPointA, malaPoint startPointB, malaPoint endPointB);//判断两条直线是否相交
	bool isLinePolylineIntersect(malaPoint startPointA, malaPoint endPointA, vector<malaPoint>& Line);//判断线是否与折线相交
	bool isLineInRect(malaRect& rc, vector<malaPoint>& Line);//判断线与线是否相交

	bool cutLine(malaPoint point, vector<malaPoint>& Line1, vector<malaPoint>& Line2);//剪断线
	bool isPointInLine(malaPoint point, malaPoint startPoint, malaPoint endPoint);//判断点是否在线上

};

#ifndef _MALABASE_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaBase.lib")
#else
#pragma comment(lib,"malaBase.lib")
#endif
#endif

#endif