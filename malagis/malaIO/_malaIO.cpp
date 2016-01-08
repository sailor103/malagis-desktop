#include "stdafx.h"
#include "_malaIO.h"
#include "_malaBase.h"

CProjectIO::CProjectIO()
{
	mPrjPath = L"";
}
CProjectIO::CProjectIO(CString paramPath)
{
	mPrjPath = paramPath;
}
CProjectIO::~CProjectIO(){}

//设置路径
void CProjectIO::setPrjPath(CString paramPath)
{
	mPrjPath = paramPath;
}

//新建工程
void CProjectIO::newPrj(malaTree pNode)
{
	CFile file;
	file.Open(LPCTSTR(mPrjPath), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	ar << pNode.itemnode << pNode.isOpen << pNode.isActive << pNode.filePath << pNode.fileType;
	ar.Close();
	file.Close();
}
//打开工程
void  CProjectIO::openPrj(vector<malaTree>&paraTree)
{
	CFile file;
	file.Open(LPCTSTR(mPrjPath), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	malaTree pNode;
	while (true)
	{
		try
		{
			ar >> pNode.itemnode >> pNode.isOpen >> pNode.isActive >> pNode.filePath >> pNode.fileType;
		}
		catch (CMemoryException* e)
		{
			break;
		}
		catch (CFileException* e)
		{
			break;
		}
		catch (CException* e)
		{
			break;
		}
		paraTree.push_back(pNode);
	}
	
	ar.Close();
	file.Close();
}

//新建文件
bool CProjectIO::newFile(vector<malaTree>&paraTree, CString fileName)
{
	if (writeAllNode(paraTree))
	{
		CFile file;
		file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		ar.Close();
		file.Close();
		return true;
	}
	else
	{
		return false;
	}
}

//更新整个节点树
bool CProjectIO::writeAllNode(vector<malaTree>&paraTree)
{
	if (paraTree.size()>0)
	{
		CFile file;
		file.Open(LPCTSTR(mPrjPath), CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		//ar << pNode.itemnode << pNode.isOpen << pNode.isActive << pNode.filePath << pNode.fileType;
		for (int i = 0; i < paraTree.size(); i++)
		{
			try
			{
				malaTree pNode = paraTree[i];
				ar << pNode.itemnode << pNode.isOpen << pNode.isActive << pNode.filePath << pNode.fileType;
			}
			catch (CException* e)
			{
				return false;
			}
		}
		ar.Close();
		file.Close();
		return true;	
	}
	else
	{
		return false;
	}
	
}
//写入文件头
/*bool CProjectIO::writeHeader(CString fPath, CString fHeader)
{
	CFile file;
	file.Open(LPCTSTR(fPath), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	try
	{
		ar << fHeader;
	}
	catch (CException* e)
	{
		return false;
	}
	ar.Close();
	file.Close();
	return true;
}*/

/************************************************************************/
/* 点文件相关函数实现                                                   */
/************************************************************************/
CPointIO::CPointIO(){}
CPointIO::~CPointIO(){}

//获取点的ID
long CPointIO::getMaxID(CString &fileName)
{
	int ID = 0;
	readPoints(fileName);
	
	int Size = mPoint.size();
	for (int i = 0; i < Size; i++)
	{
		if (mPoint[i].m_pointpro.pointId >= ID)
			ID = mPoint[i].m_pointpro.pointId;
	}
			
	return ID;
}
//读取所有的点
void CPointIO::readPoints(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);
	if (mPoint.size())
		mPoint.clear();
	malaPoint pnt;
	malaPointPro pntpro;
	while (1)
	{
		try
		{
			ar >> pntpro.pointId >> pntpro.pointRadio >> pntpro.pointStyle >> pntpro.pointColor;
			ar >> pnt.x >> pnt.y;
		}
		catch (CMemoryException* e)
		{
			break;
		}
		catch (CFileException* e)
		{
			break;
		}
		catch (CException* e)
		{
			break;
		}
		malaPointFile MyPoint(pnt, pntpro);
		mPoint.push_back(MyPoint);
	}
}

//写入所有的点
void CPointIO::savePoints(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	
	int Size = mPoint.size();
	for (int i = 0; i < Size; i++)
	{
		ar << mPoint[i].m_pointpro.pointId << mPoint[i].m_pointpro.pointRadio << mPoint[i].m_pointpro.pointStyle << mPoint[i].m_pointpro.pointColor;
		ar << mPoint[i].m_point.x << mPoint[i].m_point.y;
	}

	
	ar.Close();
	file.Close();
}

//获取某个文件中某一范围的所有的点
void CPointIO::getAllPoint(malaScreen &pScreen, vector<malaPointFile>&pAllPoints, CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);

	malaPoint pnt;
	malaPointPro pntpro;
	while (1)
	{
		try
		{
			ar >> pntpro.pointId >> pntpro.pointRadio >> pntpro.pointStyle >> pntpro.pointColor;
			ar >> pnt.x >> pnt.y;
		}
		catch (CMemoryException* e)
		{
			break;
		}
		catch (CFileException* e)
		{
			break;
		}
		catch (CException* e)
		{
			break;
		}
		malaLogic mylog;
		malaRect myrc;
		myrc.xmin = pScreen.lbx;
		myrc.ymin = pScreen.lby;
		ScreenToCoord(pScreen.wScreen, 0, pScreen, &myrc.xmax, &myrc.ymax);
		if (mylog.isPntInRect(pnt, myrc))
		{
			malaPointFile MyPoint(pnt, pntpro);
			pAllPoints.push_back(MyPoint);
		}
		
	}
}

//添加点实现
long CPointIO::pointAdd(malaPoint &Point, malaPointPro &PointPro, CString &fileName)
{
	int ID = getMaxID(fileName) + 1;
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::store);
	file.SeekToEnd();
	ar << ID << PointPro.pointRadio << PointPro.pointStyle << PointPro.pointColor;
	ar << Point.x << Point.y;
	ar.Close();
	file.Close();

	return ID;
}
//更新点实现
long CPointIO::pointUpdate(malaPoint &Point, malaPointPro &PointPro, CString &fileName)
{
	long ID = PointPro.pointId;
	readPoints(fileName);
	int Size = mPoint.size();
	for (int i = 0; i < Size; i++)
	{
		if (mPoint[i].m_pointpro.pointId == ID)
		{
			mPoint[i].m_point = Point;
			mPoint[i].m_pointpro = PointPro;
			break;
		}
	}
	savePoints(fileName);
	return ID;
}

//删除点实现
long CPointIO::pointDelete(malaPointPro &PointPro, CString &fileName)
{
	long ID = PointPro.pointId;
	readPoints(fileName);

	vector<malaPointFile>tempPoints;

	int Size = mPoint.size();
	for (int i = 0; i < Size; i++)
	{
		if (mPoint[i].m_pointpro.pointId != ID)
		{
			tempPoints.push_back(mPoint[i]);
		}
	}
	mPoint.clear();
	mPoint = tempPoints;
	savePoints(fileName);
	return ID;
}

//删除所有点实现
void CPointIO::pointDeleteAll(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate);
	file.Close();
}

/************************************************************************/
/* 线文件相关函数实现                                                   */
/************************************************************************/
CLineIO::CLineIO(){}
CLineIO::~CLineIO(){}

//获取线的最大id
long CLineIO::getMaxID(CString &fileName)
{
	int ID = 0;
	readLines(fileName);

	int Size = mLine.size();
	for (int i = 0; i < Size; i++)
	{
		if (mLine[i].mLinePro.lineId >= ID)
			ID = mLine[i].mLinePro.lineId;
	}

	return ID;
}

//读取所有的线
void CLineIO::readLines(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);
	if (mLine.size())
		mLine.clear();

	vector<malaPoint> tLine;
	malaLinePro tLinePro;
	malaPoint tPoint;
	int pointNum;
	while (1)
	{
		try
		{
			ar >> tLinePro.lineId >> tLinePro.lineStyle >> tLinePro.lineWidth >> tLinePro.lineColor;
			ar >> pointNum;
		}
		catch (CException* e)
		{
			break;
		}
		
		for (int i = 0; i < pointNum; i++)
		{
			try
			{
				ar >> tPoint.x >> tPoint.y;
			}
			catch (CException* e)
			{
				break;
			}
			tLine.push_back(tPoint);
		}
		malaLineFile MyLine(tLine, tLinePro);
		mLine.push_back(MyLine);
		tLine.clear();
	}
}

//获取某个文件中某一范围的所有的线
void CLineIO::getAllLines(malaScreen &pScreen, vector<malaLineFile>&pAllLines, CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);
	if (pAllLines.size())
		pAllLines.clear();

	vector<malaPoint> tLine;
	malaLinePro tLinePro;
	malaPoint tPoint;
	int pointNum;
	while (1)
	{
		try
		{
			ar >> tLinePro.lineId >> tLinePro.lineStyle >> tLinePro.lineWidth >> tLinePro.lineColor;
			ar >> pointNum;
		}
		catch (CException* e)
		{
			break;
		}

		for (int i = 0; i < pointNum; i++)
		{
			try
			{
				ar >> tPoint.x >> tPoint.y;
			}
			catch (CException* e)
			{
				break;
			}
			tLine.push_back(tPoint);
		}
		//检查是否在可视范围内
		
		malaLogic mylog;
		malaRect lineRc = mylog.getRect(tLine);
		malaRect screenRc;
		screenRc.xmin = pScreen.lbx;
		screenRc.ymin = pScreen.lby;
		ScreenToCoord(pScreen.wScreen, 0, pScreen, &screenRc.xmax, &screenRc.ymax);

		if (mylog.isRectIntersect(lineRc,screenRc))
		{
			malaLineFile MyLine(tLine, tLinePro);
			pAllLines.push_back(MyLine);
		}
		tLine.clear();
	}
}

//添加线
long CLineIO::lineAdd(vector<malaPoint> &pLine, malaLinePro &linePro, CString &fileName)
{
	int ID = getMaxID(fileName) + 1;
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::store);
	file.SeekToEnd();
	
	//写入文件
	int pointnum = pLine.size();
	ar << ID << linePro.lineStyle << linePro.lineWidth << linePro.lineColor;
	ar << pointnum;
	for (int i = 0; i < pointnum; i++)
		ar << pLine[i].x << pLine[i].y;

	ar.Close();
	file.Close();

	return ID;
}