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
	int       pointLayer; //图层编号
	COLORREF  pointColor; //点的颜色
}malaPointPro;

#endif
