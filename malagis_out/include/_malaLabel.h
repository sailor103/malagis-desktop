#ifndef _MALALABEL_H_
#define _MALALABEL_H_

#ifndef _MALALABEL_EXPORT
#define malalabeldll  __declspec(dllimport)
#else
#define malalabeldll  __declspec(dllexport)
#endif

#include "_malaBase.h"

/*
* 输入注释
*/
class malalabeldll CmalaLabelsInput : public CmalaMouseAction
{
public:
	CmalaLabelsInput(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLabelsInput();
	void LButtonDown(UINT nFlags, malaPoint point);
	void getLabelPro();

private:
	malaLabelPro mLabelPro;
	malaScreen *mScreen;
	CString mPath;//文件路径
	bool mIsInput;//判断有没有输入完
};

/*
* 选择注释
*/
class malalabeldll CmalaLabelsSelect :public CmalaMouseAction
{
public:
	CmalaLabelsSelect();
	CmalaLabelsSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLabelsSelect();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);

public:
	malaRect m_rect;
	malaPoint m_ptOrigin;
	malaPoint m_perPoint;
	malaLabelPro mLablePro;//存放注释的属性
	static malaPoint m_pnt;//存放当前编辑的注释；
	static malaPointPro m_PntPro;//默认点属性
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

#ifndef _MALALABEL_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaLabel.lib")
#else
#pragma comment(lib,"malaLabel.lib")
#endif
#endif

#endif