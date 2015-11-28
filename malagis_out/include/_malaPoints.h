#ifndef _MALAPOINTS_H_
#define _MALAPOINTS_H_

#ifndef _MALAPOINTS_EXPORT
#define malapointsdll  __declspec(dllimport)
#else
#define malapointsdll  __declspec(dllexport)
#endif

#include "_malaBase.h"

/*
*  ‰»Îµ„ 
*/
class malapointsdll CmalaPointsInput : public CmalaMouseAction
{
public:
	CmalaPointsInput(CView* mView);
	~CmalaPointsInput();
	void LButtonDown(UINT nFlags, malaPoint point);
private:
	malaPoint mPont;
	malaPointPro mPointPro;
};


#ifndef _MALAPOINTS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaPoints.lib")
#else
#pragma comment(lib,"malaPoints.lib")
#endif
#endif

#endif