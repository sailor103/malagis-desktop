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
	
	bool newPointFile(vector<malaTree>&paraTree, CString pointFileName);//新建点文件
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

#ifndef _MALAIO_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaIO.lib")
#else
#pragma comment(lib,"malaIO.lib")
#endif
#endif

#endif