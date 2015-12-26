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
	
	void newPrj(malaTree pNode);//新建工程文件
	void openPrj(vector<malaTree>&paraTree);//打开工程文件
	
	bool newPointFile(vector<malaTree>&paraTree, CString pointFileName);
	
	void setPrjPath(CString paramPath);
	bool writeAllNode(vector<malaTree>&paraTree);//更新整个节点树
	bool writeHeader(CString fPath,CString fHeader);//写入文件头

	
private:
	CString mPrjPath;
};

#ifndef _MALAIO_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaIO.lib")
#else
#pragma comment(lib,"malaIO.lib")
#endif
#endif

#endif