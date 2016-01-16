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

/*
* 移动注释
*/
class malalabeldll  CmalaLabelsMove :public CmalaMouseAction
{
public:
	CmalaLabelsMove(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLabelsMove();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	malaPoint m_Point;//选择的注释
	malaLabelPro m_LabelPro;//选择的注释的属性
	malaPointPro m_PointPro;//选择的点的属性
	CmalaLabelsSelect m_SelectPnt;

	CString mPath;//文件路径
	bool m_bDraw;
	malaPoint m_ptOrigin;//起点
	malaPoint m_perPoint;//临时点
	malaScreen *m_Screen;
};

/*
* 复制注释
*/
class malalabeldll  CmalaLabelsCopy :public CmalaMouseAction
{
public:
	CmalaLabelsCopy(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLabelsCopy();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	malaPoint m_Point;//选择的点
	malaPointPro m_PointPro;//选择的点的属性
	malaLabelPro m_LabelPro;//选择的注释的属性
	CmalaLabelsSelect m_SelectPnt;

	CString mPath;//文件路径

	bool m_bDraw;
	malaPoint m_ptOrigin;//起点
	malaPoint m_perPoint;//临时点
	malaScreen *m_Screen;
};

/*
* 修改注释参数
*/
class malalabeldll  CmalaLabelsModify :public CmalaMouseAction
{
public:
	CmalaLabelsModify(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLabelsModify();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	malaPoint m_Point;//选择的点
	malaPointPro m_PointPro;//选择的点的属性
	malaLabelPro m_LabelPro;//选择的注释的属性
	CmalaLabelsSelect m_SelectPnt;

	CString mPath;//文件路径
	malaScreen *m_Screen;
};


#ifndef _MALALABEL_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaLabel.lib")
#else
#pragma comment(lib,"malaLabel.lib")
#endif
#endif

#endif