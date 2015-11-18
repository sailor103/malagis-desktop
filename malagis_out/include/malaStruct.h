#ifndef _MALASTRUCT_H_
#define _MALASTRUCT_H_

#include <vector>
using namespace std;

//点坐标
typedef struct
{
	double x;
	double y;
}malaPoint;

//点属性
typedef struct
{
	long      pointId;
	int		  pointRadio;
	int		  pointStyle;
	int       pointLayer;
	COLORREF  pointColor;
}malaPointPro;

//线结构体
typedef struct
{
	vector<malaPoint>Line;
}malaLine;

//线属性
typedef struct
{
	long     lineId;
	int      lineWidth;
	int      lineStyle;
	COLORREF lineColor;
	int      lineLayer;
}malaLinePro;

//区结构体
typedef struct
{
	vector<malaPoint>Poly;
}malaPoly;
//区属性
typedef struct
{
	long     polyId;
	int      polyStyle;
	COLORREF polyColor;
	int      polyLayer;
	double   polyArea;
	int      polyFillStyle;
}malaPolyPro;

//注记属性
typedef struct
{
	int      tagId;
	int      tagHeight; //字体高度
	int      tagWidth;  //字体宽度
	float    tagAngle;  //字体角度
	float    tagTextAngle; //文本角度
	COLORREF tagColor;  //字体颜色
	int      tagOffsite;  //字体间距
	CString  tagFont;   //字体类型
	CString  tagStr;    //字符串
	int	tagLayer; //注记图层
}malaTagPro;

#endif
