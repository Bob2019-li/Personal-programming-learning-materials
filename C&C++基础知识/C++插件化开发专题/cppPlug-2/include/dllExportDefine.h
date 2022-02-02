/*
 * 定义导出函数的导出方式，这里以后可以根据不同的平台定义不同的导出方式
 */

#ifndef DLLEXPORTDEFINE_H
#define DLLEXPORTDEFINE_H


#ifdef __cplusplus

    #define DLLAPI __declspec(dllexport)
	
#endif


#endif // DLLEXPORTDEFINE_H
