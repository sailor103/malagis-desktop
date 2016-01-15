#ifndef _MALAIO_H_
#define _MALAIO_H_

#ifndef _MALAIO_EXPORT
#define malaio  __declspec(dllimport)
#else
#define malaio  __declspec(dllexport)
#endif

#include "malaStruct.h"

/*
*工程文件操作类
*/
class malaio CProjectIO
{
public:
	CProjectIO();
	CProjectIO(CString paramPath);
	~CProjectIO();
	void setPrjPath(CString paramPath);
	
	void newPrj(malaTree pNode);//新建工程文件
	void openPrj(vector<malaTree>&paraTree);//打开工程文件
	
	bool newFile(vector<malaTree>&paraTree, CString fileName);//新建文件
	bool writeAllNode(vector<malaTree>&paraTree);//更新整个节点树
	//bool writeHeader(CString fPath,CString fHeader);//写入文件头

	
private:
	CString mPrjPath;
};

/*
* 点文件存取类
* 用来定义一个点的存取
*/
class malaPointFile
{
public:
	malaPoint m_point;
	malaPointPro m_pointpro;
public:
	malaPointFile(malaPoint point, malaPointPro pntpro)
	{
		m_point = point;
		m_pointpro = pntpro;
	}
	~malaPointFile(){};
};

/*
* 线文件存取类
* 用来定义一条线的存取
*/
class malaLineFile
{
public:
	malaLineFile(vector<malaPoint>& Line, malaLinePro LinePro)
	{
		mLine = Line;
		mLinePro = LinePro;
	}
	~malaLineFile()
	{
		if (mLine.size())
			mLine.clear();
	}
public:
	vector<malaPoint> mLine;
	malaLinePro mLinePro;

};

/*
* 区文件存取类
* 用来定义一个区的存取
*/
class malaPolyFile
{
public:
	malaPolyFile(vector<malaPoint>& Poly, malaPolyPro PolyPro)
	{
		mPoly = Poly;
		mPolyPro = PolyPro;
	}
	~malaPolyFile()
	{
		if (mPoly.size())
			mPoly.clear();
	}
public:
	vector<malaPoint> mPoly;
	malaPolyPro mPolyPro;

};

/*
* 点文件操作类
*/
class malaio CPointIO
{
public:
	CPointIO();
	virtual ~CPointIO();
public:
	long getMaxID(CString &fileName);//获取点ID
	void readPoints(CString &fileName);//读取所有的点
	void savePoints(CString &fileName);//写入所有的点
	void getAllPoint(malaScreen &pScreen, vector<malaPointFile>&pAllPoints, CString &fileName);//获取某个文件中某一范围的所有的点
public:
	long pointAdd(malaPoint &Point, malaPointPro &PointPro, CString &fileName);//添加点
	long pointUpdate(malaPoint &Point, malaPointPro &PointPro, CString &fileName);//更新点
	long pointDelete(malaPointPro &PointPro, CString &fileName);//删除点
	void pointDeleteAll(CString &fileName);//删除所有点

private:
	vector<malaPointFile> mPoint;//临时数据变量
};

/*
* 线文件操作类
*/
class malaio CLineIO
{
public:
	CLineIO();
	virtual ~CLineIO();
public:
	long getMaxID(CString &fileName);//获取线ID
	void readLines(CString &fileName);//读取所有的线
	void saveLines(CString &fileName);//保存所有的线
	void getAllLines(malaScreen &pScreen, vector<malaLineFile>&pAllLines, CString &fileName);//获取某个文件中某一范围的所有的线

public:
	long lineAdd(vector<malaPoint> &pLine, malaLinePro &linePro, CString &fileName);//添加线
	long lineUpdate(vector<malaPoint> &pLine, malaLinePro &linePro, CString &fileName);//更新线
	long lineDelete(long ID, CString &fileName);//删除一条线
	void lineDeleteAll(CString &fileName);//删除所有线

private:
	vector<malaLineFile> mLine;//临时数据变量

};

/*
* 区文件操作类
*/
class malaio CPolyIO
{
public:
	CPolyIO();
	virtual ~CPolyIO();
public:
	long getMaxID(CString &fileName);//获取区ID
	void readPolys(CString &fileName);//读取所有的区
	void savePolys(CString &fileName);//保存所有的区
	void getAllPolys(malaScreen &pScreen, vector<malaPolyFile>&pAllPolys, CString &fileName);//获取某个文件中某一范围的所有的区

public:
	long polyAdd(vector<malaPoint> &Poly, malaPolyPro &PolyPro, CString &fileName);//添加区
	long polyUpdate(vector<malaPoint> &Poly, malaPolyPro &PolyPro, CString &fileName);//更新区
	long polyDelete(long ID, CString &fileName);//删除一条区
	void polyDeleteAll(CString &fileName);//删除所有区

private:
	vector<malaPolyFile> mPoly;//临时数据变量
};

#ifndef _MALAIO_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaIO.lib")
#else
#pragma comment(lib,"malaIO.lib")
#endif
#endif

#endif