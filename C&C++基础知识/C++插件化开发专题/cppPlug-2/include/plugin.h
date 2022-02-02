/*
 * 插件框架通用的一些数据结构和函数指针
 */
#ifndef PLUGIN_H
#define PLUGIN_H

#ifdef __cplusplus
extern "C" {
#endif

//平台服务 向插件提供一些数据结构以及服务函数，这里使用前置声明，因为还有别的数据结构要使用
struct PF_PlatformServices;

//插件创建对象的函数指针
typedef void * (*PF_GetInstance)();

//插件销毁对象的函数指针
typedef int (*PF_DestroyFunc)(void *);

//插件版本参数
typedef struct PF_PluginAPI_Version
{
  int major; //主版本
  int minor; //副版本
} PF_PluginAPI_Version;

//注册参数  插件在初始化后，会向主体程序注册一些信息
typedef struct PF_RegisterParams
{
  PF_PluginAPI_Version version; //插件版本
  PF_GetInstance getInstance;   //插件的单例对象创建
  PF_DestroyFunc destroyFunc;   //插件的销毁对象函数
} PF_RegisterParams;

//注册函数的函数指针
typedef int (*PF_RegisterFunc)(const char * nodeType, const PF_RegisterParams * params);


//平台服务参数
typedef struct PF_PlatformServices
{
  PF_PluginAPI_Version version;       //插件版本
  PF_RegisterFunc registerObject;     //注册函数
} PF_PlatformServices;



//插件初始化函数指针，这个函数本体只有插件才有，但是主体程序中也会用到，所以在这里算是提前声明
typedef int (*PF_InitFunc)(const PF_PlatformServices *);


#ifdef  __cplusplus
}
#endif

#endif 

