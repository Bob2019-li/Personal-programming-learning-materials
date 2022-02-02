/*
 *  插件管理器
 */

#ifndef PLUGMANAGER_H
#define PLUGMANAGER_H

#include "base.h"
#include <QString>
#include <QVector>
#include <QStringList>
#include <QDir>
#include <QLibrary>
#include <QDebug>
#include <QCoreApplication>
#include <QMap>
#include <mutex>
#include "plugin.h"


class PlugManager
{
    //key 是插件名称  value 是插件注册信息
    typedef QMap<QString, PF_RegisterParams> RegistrationMap;

    //key 是动态库文件路径   value 是加载动态库的指针
    typedef QMap<QString, QLibrary*> DynamicLibraryMap;

    PF_PlatformServices platformServices_;
    DynamicLibraryMap   dynamicLibraryMap_;
    RegistrationMap     exactMatchMap_;

    //构造 析构  拷贝构造  重载赋值操作符
    PlugManager();
    ~PlugManager() = default;
    PlugManager(const PlugManager &) = delete;
    PlugManager & operator=(const PlugManager &) = delete;

public:

    //初始化插件函数
    static int initializePlugin(PF_InitFunc initFunc);

    //插件注册函数
    static int registerPlugin(const char * nodeType, const PF_RegisterParams * params);

    //全部加载函数
    int loadAll(const std::string & pluginDirectory);

    //返回插件注册信息map
    const RegistrationMap & getRegistrationMap();

    //返回平台服务参数
    PF_PlatformServices & getPlatformServices();

    //单例会用到
    static std::mutex m_mutex;
    static void Release(); //主动回收单例对象的资源
    static PlugManager * getInstance();
    static PlugManager * pInstance;


private:

    //遍历目录 有瑕疵，不能遍历有子目录的
    QStringList TraversalFile(const QString &path);

    void UnLoadAll();

    class GarbageCollect
    {//自动回收单例对象的资源
        ~GarbageCollect()
        {
            if (pInstance)
            {
                pInstance->UnLoadAll(); //卸载所有的插件
                delete pInstance;
                pInstance = nullptr;
            }
        }
    };
};


#endif // PLUGMANAGER_H
