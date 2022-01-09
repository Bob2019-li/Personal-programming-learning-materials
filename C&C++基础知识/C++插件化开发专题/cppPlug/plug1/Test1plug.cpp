#include "PlugExport.h"
#include "test1.h"


//插件对导出函数的实现

#ifdef __cplusplus
extern "C" {
#endif

    Base* __cdecl getObj(void)
    {
        return new test1;
    }

    const char*  __cdecl getName(void)
    {
        return "plug1";
    }

#ifdef __cplusplus
}
#endif
