#ifndef _MALABASE_H_
#define _MALABASE_H_

#ifndef _MALABASE_EXPORT
#define malabase  __declspec(dllimport)
#else
#define malabase  __declspec(dllexport)
#endif


#ifndef _MALABASE_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaBase.lib")
#else
#pragma comment(lib,"malaBase.lib")
#endif
#endif

#endif