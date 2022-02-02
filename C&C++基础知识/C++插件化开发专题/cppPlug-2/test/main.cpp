#include <QCoreApplication>
#include "base.h"
#include <QString>
#include <QVector>
#include <QDir>
#include <QDebug>
#include "PlugManager.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    //动态库所在目录的路径
    QString path = "./plugins";

    //获取插件管理器对象(单例)
    PlugManager * pm = PlugManager::getInstance();

    //加载插件
    pm->loadAll(path.toStdString());

    //获取插件注册的信息
    QMap<QString, PF_RegisterParams> pluginMap = pm->getRegistrationMap();

    //获取插件对象指针
    //ps: 这里的"plug1" 是插件名称，其实可以提前准备一个json文件，里面写清楚要加载的插件名称、版本和其他信息
    //这里为了简单就没做
    Base *  pPlug = (Base *)pluginMap["plug1"].getInstance();

    if(pPlug == nullptr)
    {
       return a.exec();
    }

    //调用插件的功能
    pPlug->calc(12);
    pPlug->print();

    //主动销毁插件以及空间
    pm->Release();

    qDebug()<<"=========DONE=========";

    return a.exec();
}
