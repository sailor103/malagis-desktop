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

#ifndef _MALADIALOGS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaDialogs.lib")
#else
#pragma comment(lib,"malaDialogs.lib")
#endif
#endif

#endif