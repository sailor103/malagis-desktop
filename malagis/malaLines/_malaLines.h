#ifndef _MALALINES_H_
#define _MALALINES_H_

#ifndef _MALALINES_EXPORT
#define malalinesdll  __declspec(dllimport)
#else
#define malalinesdll  __declspec(dllexport)
#endif


#ifndef _MALALINES_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaLines.lib")
#else
#pragma comment(lib,"malaLines.lib")
#endif
#endif

#endif