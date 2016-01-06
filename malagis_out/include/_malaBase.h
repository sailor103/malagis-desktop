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
	
	void drawSelectRectPoint(malaPoint Point, malaPointPro PntPro);//绘制选中状态的外接矩形

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
	bool isPntInRect(malaPoint &Point, malaRect& rc);
};

#ifndef _MALABASE_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaBase.lib")
#else
#pragma comment(lib,"malaBase.lib")
#endif
#endif

#endif