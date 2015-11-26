#ifndef _MALASTRUCT_H_
#define _MALASTRUCT_H_

#include <vector>
using namespace std;

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
