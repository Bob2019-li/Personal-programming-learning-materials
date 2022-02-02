#include "PlugExport.h"


#ifdef __cplusplus
extern "C" {
#endif

    DLLAPI int PF_initPlugin(const PF_PlatformServices * params)
    {
        int res = 0;

        PF_RegisterParams rp;
        rp.version.major = MAJOR;
        rp.version.minor = MINOR;

        rp.getInstance = test1::getInstance;
        rp.destroyFunc = test1::destroy;

        //插件向主体程序注册信息
        res = params->registerObject((const char *)PLUGIN_NAME, &rp);

        return res;
    }

#ifdef __cplusplus
}
#endif
