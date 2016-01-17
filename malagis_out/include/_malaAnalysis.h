#ifndef _MALAANALYSIS_H_
#define _MALAANALYSIS_H_

#ifndef _MALAANALYSIS_EXPORT
#define malaanalysisdll  __declspec(dllimport)
#else
#define malaanalysisdll  __declspec(dllexport)
#endif

#include "_malaBase.h"
#include "_malaIO.h"
#include "_malaLines.h"
#include "_malaPoints.h"
#include "_malaPolygon.h"

/*
* 拓扑分析
*/
class malaanalysisdll CmalaTopo :public CmalaMouseAction
{
public:
	CmalaTopo(CView* mView, malaScreen *pScreen, CString &fileFullPath, int topoType);
	virtual ~CmalaTopo();
	static vector<malaTopoCell> m_TopoObject;
	void topoAnalysis(vector<malaTopoCell>TopoObject);
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void  MouseMove(UINT nFlags, malaPoint point);
private:

	malaScreen *mScreen;
	CString mPath;//文件路径
	bool m_Selected;

	malaPoint m_Point;
	CmalaPointsSelect m_SelectPnt;

	vector<malaPoint>m_line;
	CmalaLinesSelect m_SelectLine;

	malaPoint m_ptOrigin;
	CmalaPolysSelect m_SelectePoly;

	int m_SelectStyle;

};

/*
* 自定义线段量算
*/
class malaanalysisdll CmalaLineMeasureCustom :public CmalaMouseAction
{
public:
	CmalaLineMeasureCustom(CView* ptView, malaScreen *Screen);
	~CmalaLineMeasureCustom();
	void LButtonDown(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
	void RButtonDown(UINT nFlags, malaPoint point);
private:
	bool m_bDraw;
	malaPoint m_PtOrigin;
	malaPoint m_PerPoint;
	malaLinePro m_LinePro;
	vector<malaPoint>m_Line;
	
	malaScreen *m_Screen;
};

/*
* 已知线段量算
*/
class malaanalysisdll CmalaLineMeasure :public CmalaMouseAction
{
public:
	CmalaLineMeasure(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLineMeasure();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	malaLinePro m_linepro;
	vector<malaPoint>m_line;
	CmalaLinesSelect m_SelectLine;
	bool m_Selected;
	bool m_bDraw;
	malaLinePro m_LinePro;
	malaPoint m_ptOrigin;
	malaPoint m_perPoint;
	malaScreen *m_Screen;
	CString mPath;//文件路径
};

#ifndef _MALAANALYSIS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaAnalysis.lib")
#else
#pragma comment(lib,"malaAnalysis.lib")
#endif
#endif

#endif