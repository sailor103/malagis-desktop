#ifndef _MALADIALOGS_H_
#define _MALADIALOGS_H_

#ifndef _MALADIALOGS_EXPORT
#define maladialogsdll  __declspec(dllimport)
#else
#define maladialogsdll  __declspec(dllexport)
#endif

#include "malaStruct.h"

/*
 *输入点的对话框
*/
bool maladialogsdll dlgInputPoint(malaPointPro& paramPointPro);

/*
* 新建工程对话框
*/
bool maladialogsdll dlgNewPrj(CString &paramPrjPath,CString&prjName,CString&prjExt);

/*
* 打开工程对话框
*/
bool maladialogsdll dlgOpenPrj(CString &paramPrjPath);

/*
* 新建点文件对话框
*/
bool maladialogsdll dlgNewPointFile(CString &pointName);

/*
* 文件属性对话框
*/
void maladialogsdll dlgGraphFilePro(malaTree fileNode);

/*
* 载入文件对话框
*/
bool maladialogsdll dlgLoadGraphFile(malaTree & tmpTree);

/*
* 修改点属性对话框
*/
bool maladialogsdll dlgModifyPointPro(malaPointPro& pro);

/*
* 新建线文件对话框
*/
bool maladialogsdll dlgNewLineFile(CString &lineName);

/*
*输入线的对话框
*/
bool maladialogsdll dlgInputLine(malaLinePro& paramPro);

/*
* 修改线属性对话框
*/
bool maladialogsdll dlgModifyLinePro(malaLinePro& paramPro);

/*
* 新建区文件对话框
*/
bool maladialogsdll dlgNewPolyFile(CString &polyName);

/*
* 输入区对话框
*/
bool maladialogsdll dlgInputPoly(malaPolyPro &paramPro);

#ifndef _MALADIALOGS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaDialogs.lib")
#else
#pragma comment(lib,"malaDialogs.lib")
#endif
#endif

#endif