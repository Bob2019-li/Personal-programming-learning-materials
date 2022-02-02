#ifndef PLUGEXPORT_H
#define PLUGEXPORT_H

//对象模型
#include "base.h"

//导出类型声明
#include "dllExportDefine.h"

//通用插件会使用到的数据结构
#include "../include/plugin.h"

//插件程序主体的头文件
#include "test1.h"

#include <iostream>
#include <ostream>
using namespace  std;

const int MAJOR = 1;
const int MINOR = 0;
const char * PLUGIN_NAME = "plug1";


// 定义了插件DLL导出函数
#ifdef __cplusplus
extern "C" {
#endif

    DLLAPI int PF_initPlugin(const PF_PlatformServices * params);

#ifdef __cplusplus
}
#endif


#endif // PLUGEXPORT_H
