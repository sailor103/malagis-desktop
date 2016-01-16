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


#ifndef _MALALABEL_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaLabel.lib")
#else
#pragma comment(lib,"malaLabel.lib")
#endif
#endif

#endif