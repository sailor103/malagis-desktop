#ifndef _MALASTRUCT_H_
#define _MALASTRUCT_H_

#include <vector>
using namespace std;

//屏幕坐标系
typedef struct
{
	double scale;	//比例尺
	double lbx;	//屏幕左下角的横坐标
	double lby;	//屏幕左下角的纵坐标
	int wScreen;    //屏幕宽
	int hScreen;    //屏幕高
}malaScreen;

//点坐标
typedef struct
{
	double x;//x坐标
	double y;//y坐标
}malaPoint;

//点属性
typedef struct
{
	long      pointId;    //点序号
	int		  pointRadio; //点半径
	int		  pointStyle; //点类型
	COLORREF  pointColor; //点的颜色
}malaPointPro;

//线结构体
typedef struct
{
	vector<malaPoint>linePoints;
}malaLine;

//线属性
typedef struct
{
	long lineId;
	int  lineWidth;
	int  lineStyle;
	COLORREF lineColor;
}malaLinePro;

//区结构体
typedef struct
{
	vector<malaPoint> polyPoints;
}malaPoly;

//区属性
typedef struct
{
	long polyId;
	int polyStyle;//区类型 0 多边形 1 圆
	int borderStyle;//边框类型
	int borderWidth;//边框宽度
	COLORREF borderColor;//边框颜色
	COLORREF fillColor;//填充颜色
	int fillStyle;//填充方式
}malaPolyPro;

//目录树节点
typedef struct
{
	CString   itemnode;//节点名
	bool      isOpen; //打开状态
	bool      isActive;//激活状态
	CString   fileType;//文件类型
  CString   filePath;//文件路径
}malaTree;

//外接矩形
typedef struct
{
	double xmin;
	double xmax;
	double ymin;
	double ymax;
}malaRect;
#endif
