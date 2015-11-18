#ifndef _MALABASE_H_
#define _MALABASE_H_

#ifndef _MALABASE_EXPORT
#define Logic  __declspec(dllimport)
#else
#define Logic  __declspec(dllexport)
#endif

#include "malaStruct.h"
#include <vector>
using namespace std;



#ifndef _CoLogic_EXPORT_
#ifdef _DEBUG
#pragma comment(lib,"CoLogic.lib")
#else
#pragma comment(lib,"CoLogic.lib")
#endif
#endif

#endif