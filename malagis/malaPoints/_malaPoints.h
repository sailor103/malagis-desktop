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

		switch (m_PntPro.pointStyle)
		{
		case 0:
			dc.pointDrawRectX(m_pnt, m_PntPro);
			break;
		case 1:
			dc.pointDrawTriangleX(m_pnt, m_PntPro);
			break;
		case 2:
			dc.pointDrawCircleX(m_pnt, m_PntPro);
			break;
		default:
			break;
		}
	}
};

#ifndef _MALAPOINTS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaPoints.lib")
#else
#pragma comment(lib,"malaPoints.lib")
#endif
#endif

#endif