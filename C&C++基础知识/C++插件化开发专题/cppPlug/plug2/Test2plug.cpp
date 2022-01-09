#include "PlugExport.h"
#include "test2.h"


//插件对导出函数的实现

#ifdef __cplusplus
extern "C" {
#endif

    Base* __cdecl getObj(void)
    {
        return new test2;
    }

    const char*  __cdecl getName(void)
    {
        return "plug2";
    }

#ifdef __cplusplus
}
#endif
