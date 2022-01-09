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
    // 单例实现 插件管理类对象
    PlugManager * plugManager = PlugManager::getInstance();

    // 设置dll路径
    plugManager->SetPlugLoadPath("./plugins");

    // 通过插件名称进行加载
    plugManager->Load("plug1");
    plugManager->Load("plug2");

    // 获取插件中的对象  执行操作 然后卸载
    Base * plug = plugManager->GetPlugInstance("plug1");
    if(plug != nullptr)
    {
        plug->calc(123);
        plug->print();
    }

    // 如法炮制上面的操作
    plug = plugManager->GetPlugInstance("plug2");
    if(plug != nullptr)
    {
        plug->calc(456);
        plug->print();
    }

    //卸载所有插件
    plugManager->Release();


    qDebug()<<"=========DONE=========";

    return a.exec();
}
