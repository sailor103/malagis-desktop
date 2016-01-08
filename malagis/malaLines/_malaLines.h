#ifndef _MALALINES_H_
#define _MALALINES_H_

#ifndef _MALALINES_EXPORT
#define malalinesdll  __declspec(dllimport)
#else
#define malalinesdll  __declspec(dllexport)
#endif
#include "_malaBase.h"

/*
*输入线
*/
class malalinesdll  CmalaLinesInput : public CmalaMouseAction
{
public:
	CmalaLinesInput(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesInput();
	void LButtonDown(UINT nFlags, malaPoint point);
	void RButtonDown(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
	void GetLinePro();//获取线的属性
private:
	bool m_bDraw;
	malaPoint m_PtOrigin; //起点
	malaPoint m_PerPoint; //临时点
	malaLinePro m_LinePro;//线属性
	vector<malaPoint>m_Line;//线

	malaScreen *mScreen;
	CString mPath;//文件路径
};


#ifndef _MALALINES_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaLines.lib")
#else
#pragma comment(lib,"malaLines.lib")
#endif
#endif

#endif