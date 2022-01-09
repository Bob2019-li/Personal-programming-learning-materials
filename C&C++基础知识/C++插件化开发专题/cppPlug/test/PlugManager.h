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

//dll导出的函数
typedef Base* (__cdecl *ObjProc)(void);
typedef const char* (__cdecl *NameProc)(void);


struct PlugInfo
{
    Base * pbase;
    QLibrary * plib;

    PlugInfo()
    {
        pbase = nullptr;
        plib = nullptr;
    }
};






class PlugManager
{
private:
    PlugManager() = default;
    ~PlugManager() = default;
    PlugManager(const PlugManager &) = delete;
    PlugManager & operator=(const PlugManager &) = delete;

public:
    static std::mutex m_mutex;
    static void Release(); //主动回收单例对象的资源
    static PlugManager * getInstance();
    static PlugManager * pInstance;

public:
    bool Load(QString qstrPlugName);
    bool UnLoad(QString qstrPlugName);
    void UnLoadAll();

    QStringList TraversalFile(const QString &path);
    void SetPlugLoadPath(QString qstrPath);

    Base * GetPlugInstance(QString qstrPlugName);

private:

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

    QMap<QString,PlugInfo> mapPlug;
    QString qstrPlugPath; 
};


#endif // PLUGMANAGER_H
