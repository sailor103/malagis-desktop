#ifndef _MALAPOLYGON_H_
#define _MALAPOLYGON_H_

#ifndef _MALAPOLYGON_EXPORT
#define malapolygondll  __declspec(dllimport)
#else
#define malapolygondll  __declspec(dllexport)
#endif
#include "_malaBase.h"
/*
*输入区
*/
class malapolygondll  CmalaPolysInput : public CmalaMouseAction
{
public:
	CmalaPolysInput(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPolysInput();
	void LButtonDown(UINT nFlags, malaPoint point);
	void RButtonDown(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
	void GetPolyPro();//获取线的属性
private:
	bool mIsDraw;
	malaPoint mPerPoint; //临时点
	malaPolyPro mPolyPro;//区属性
	vector<malaPoint>mPoly;//线

	malaScreen *mScreen;
	CString mPath;//文件路径
};

/*
* 选择区
*/
class malapolygondll CmalaPolysSelect :public CmalaMouseAction
{
public:
	CmalaPolysSelect();
	CmalaPolysSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPolysSelect();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);

public:
	malaRect m_rect;
	malaPoint m_ptOrigin;
	malaPoint m_perPoint;
	static vector<malaPoint> mSPoly;//存放当前编辑的区；
	static malaPolyPro mSPolyPro;//存放当前编辑的区属性
	static malaScreen *m_Screen;
	static CView* m_StaticView;

	CString mPath;//文件路径
	bool m_bDraw;
	bool m_Selected;
public:

	inline static void CALLBACK TimerPoly(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
	{
		malaCDC dc(m_StaticView, *m_Screen);
		dc.polyDrawAutoX(mSPoly, mSPolyPro);
	}
};

#ifndef _MALAPOLYGON_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaPolygon.lib")
#else
#pragma comment(lib,"malaPolygon.lib")
#endif
#endif

#endif