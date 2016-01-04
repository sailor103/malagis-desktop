#ifndef _MALATOOLS_H_
#define _MALATOOLS_H_

#ifndef _MALATOOLS_EXPORT
#define malatoolsdll  __declspec(dllimport)
#else
#define malatoolsdll  __declspec(dllexport)
#endif

#include "_malaBase.h"

/*
* ·Å´óµØÍ¼
*/
class malatoolsdll malaZoonIn :public CmalaMouseAction
{
public:
	malaZoonIn();
	malaZoonIn(CView* ptView, malaScreen *Screen);
	~malaZoonIn();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	malaPoint m_PtOrigin;
	malaPoint m_perPoint;
	bool m_bDraw;
public:
	malaScreen *m_Screen;
};

#ifndef _MALATOOLS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaTools.lib")
#else
#pragma comment(lib,"malaTools.lib")
#endif
#endif

#endif