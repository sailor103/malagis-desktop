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

/*
* 选择线
*/
class malalinesdll CmalaLinesSelect :public CmalaMouseAction
{
public:
	CmalaLinesSelect();
	CmalaLinesSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesSelect();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);

public:
	malaRect m_rect;
	malaPoint m_ptOrigin;
	malaPoint m_perPoint;
	static vector<malaPoint> mLine;//存放当前编辑的点；
	static malaLinePro mLinePro;//存放当前编辑的点属性
	static malaScreen *m_Screen;
	static CView* m_StaticView;

	CString mPath;//文件路径
	bool m_bDraw;
	bool m_Selected;
public:

	inline static void CALLBACK TimerLine(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
	{
		malaCDC dc(m_StaticView, *m_Screen);
		dc.lineDrawAllX(mLine, mLinePro); 
	}
};
/*
* 移动线
*/
class malalinesdll  CmalaLinesMove :public CmalaMouseAction
{
public:
	CmalaLinesMove(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesMove();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	vector<malaPoint> mSLine;//选择的线
	malaLinePro mSLinePro;//选择的点的属性
	CmalaLinesSelect m_SelectLine;

	CString mPath;//文件路径

	bool m_bDraw;
	malaPoint m_ptOrigin;//起点
	vector<malaPoint> m_perLine;//临时线
	malaScreen *m_Screen;
};

/*
* 复制线
*/
class malalinesdll  CmalaLinesCopy :public CmalaMouseAction
{
public:
	CmalaLinesCopy(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesCopy();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	vector<malaPoint> mSLine;//选择的线
	malaLinePro mSLinePro;//选择的点的属性
	CmalaLinesSelect m_SelectLine;

	CString mPath;//文件路径

	bool m_bDraw;
	malaPoint m_ptOrigin;//起点
	vector<malaPoint> m_perLine;//临时线
	malaScreen *m_Screen;
};

/*
* 修改线属性
*/
class malalinesdll  CmalaLinesModify :public CmalaMouseAction
{
public:
	CmalaLinesModify(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesModify();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	vector<malaPoint> mSLine;//选择的线
	malaLinePro mSLinePro;//选择的点的属性
	CmalaLinesSelect m_SelectLine;

	CString mPath;//文件路径

	bool m_bDraw;
	malaScreen *m_Screen;
};
#ifndef _MALALINES_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaLines.lib")
#else
#pragma comment(lib,"malaLines.lib")
#endif
#endif

#endif