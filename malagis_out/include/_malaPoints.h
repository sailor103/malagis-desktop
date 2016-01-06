#ifndef _MALAPOINTS_H_
#define _MALAPOINTS_H_

#ifndef _MALAPOINTS_EXPORT
#define malapointsdll  __declspec(dllimport)
#else
#define malapointsdll  __declspec(dllexport)
#endif

#include "_malaBase.h"

/*
* 输入点 
*/
class malapointsdll CmalaPointsInput : public CmalaMouseAction
{
public:
	CmalaPointsInput(CView* mView,malaScreen *pScreen,CString &fileFullPath);
	~CmalaPointsInput();
	void LButtonDown(UINT nFlags, malaPoint point);
	void GetPointPro();//获取点的参数
private:
	malaPoint mPont;
	malaPointPro mPointPro;
	malaScreen *mScreen;
	CString mPath;//文件路径
};
/*
* 选择点
*/
class malapointsdll CmalaPointsSelect :public CmalaMouseAction
{
public:
	CmalaPointsSelect();
	CmalaPointsSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPointsSelect();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);

public:
	malaRect m_rect;
	malaPoint m_ptOrigin;
	malaPoint m_perPoint;
	static malaPoint m_pnt;//存放当前编辑的点；
	static malaPointPro m_PntPro;//存放当前编辑的点属性
	static malaScreen *m_Screen;
	static CView* m_StaticView;

	CString mPath;//文件路径
	bool m_bDraw;
	bool m_Selected;
public:

	inline static void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
	{
		malaCDC dc(m_StaticView, *m_Screen);
		dc.pointDrawAutoX(m_pnt, m_PntPro);
	}
};

/*
* 移动点
*/
class malapointsdll  CmalaPointsMove :public CmalaMouseAction
{
public:
	CmalaPointsMove(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPointsMove();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	malaPoint m_Point;//选择的点
	malaPointPro m_PointPro;//选择的点的属性
	CmalaPointsSelect m_SelectPnt;

	CString mPath;//文件路径

	bool m_bDraw;
	malaPoint m_ptOrigin;//起点
	malaPoint m_perPoint;//临时点
	malaScreen *m_Screen;
};

/*
* 复制点
*/
class malapointsdll  CmalaPointsCopy :public CmalaMouseAction
{
public:
	CmalaPointsCopy(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPointsCopy();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	malaPoint m_Point;//选择的点
	malaPointPro m_PointPro;//选择的点的属性
	CmalaPointsSelect m_SelectPnt;

	CString mPath;//文件路径

	bool m_bDraw;
	malaPoint m_ptOrigin;//起点
	malaPoint m_perPoint;//临时点
	malaScreen *m_Screen;
};

/*
* 修改点参数
*/
class malapointsdll  CmalaPointsModify :public CmalaMouseAction
{
public:
	CmalaPointsModify(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPointsModify();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	malaPoint m_Point;//选择的点
	malaPointPro m_PointPro;//选择的点的属性
	CmalaPointsSelect m_SelectPnt;

	CString mPath;//文件路径
	malaScreen *m_Screen;
};

#ifndef _MALAPOINTS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaPoints.lib")
#else
#pragma comment(lib,"malaPoints.lib")
#endif
#endif

#endif