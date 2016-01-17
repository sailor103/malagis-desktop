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

#ifndef _MALAANALYSIS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaAnalysis.lib")
#else
#pragma comment(lib,"malaAnalysis.lib")
#endif
#endif

#endif