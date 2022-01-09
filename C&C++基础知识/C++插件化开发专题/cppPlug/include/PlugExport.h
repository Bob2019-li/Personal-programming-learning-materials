#ifndef PLUGEXPORT_H
#define PLUGEXPORT_H

#define EXPORT_WIN

#include "base.h"

#ifdef EXPORT_WIN
    #define DLLAPI __declspec(dllexport)
#endif


#ifdef EXPORT_LINUX
    #define DLLAPI
#endif

// 定义了所有插件DLL导出函数
#ifdef __cplusplus
extern "C" {
#endif

    DLLAPI Base *      __cdecl getObj(void);
    DLLAPI const char* __cdecl getName(void);

#ifdef __cplusplus
}
#endif


#endif // PLUGEXPORT_H
