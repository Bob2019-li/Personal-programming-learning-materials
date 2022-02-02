#include "PlugManager.h"

std::mutex PlugManager::m_mutex;

PlugManager * PlugManager::pInstance = nullptr;

PlugManager * PlugManager::getInstance()
{
      m_mutex.lock();
      if(!pInstance)
      {
          pInstance = new PlugManager();
      }

      m_mutex.unlock();
      return pInstance;
}

int PlugManager::initializePlugin(PF_InitFunc initFunc)
{
    PlugManager * pm = PlugManager::getInstance();
    int res = initFunc(&(pm->platformServices_));
    if (res < 0)
    {
        qDebug()<<" "<<__LINE__<<" "<<__FUNCTION__<<" initializePlugin fail "<<endl;
        return -1;
    }
    return 0;
}

int PlugManager::loadAll(const std::string &pluginDirectory)
{
    if (pluginDirectory.empty()) //如果参数为空就返回
    {
        return -1;
    }

    //赋值函数指针
    QString qstrPath = QString(pluginDirectory.data());

    QDir dir;
    dir.setPath(qstrPath);

    if (!dir.exists())
    {
       return -1;
    }

    // 在plugins目录中查找dll文件并将文件信息保存在qstrList中
    QStringList qstrList = TraversalFile(qstrPath);  //这里直接输入目录

    if(qstrList.isEmpty())
    {// 没有找到任何dll文件，返回空vector
         return -1;
    }


    auto iter = qstrList.begin();

    while(iter != qstrList.end())
    {
        //完整路径拼接
        QString qstrFullPath = qstrPath + "/" + (*iter);

        if (dynamicLibraryMap_.find(qstrFullPath) != dynamicLibraryMap_.end())
        {//检查即将加载的动态库是否已加载
            ++iter;
            continue;
        }

        //加载插件动态库
        QLibrary * lib = new QLibrary();
        lib->setFileName(qstrFullPath);

        PF_InitFunc dllFunction = (PF_InitFunc) lib->resolve("PF_initPlugin");
        if (dllFunction == nullptr)
        {
            return -1;
        }

        //存储动态库对象指针
        dynamicLibraryMap_[qstrFullPath] = lib;

        //初始化插件
        int res = initializePlugin(dllFunction);

        if (res < 0)
        {
           return res;
        }
        ++iter;
    }
    return 0;
}


int PlugManager::registerPlugin(const char * objectType, const PF_RegisterParams *params)
{
    //参数有效性检测
    if (!objectType || !(*objectType))
    {
        return -1;
    }

    if (!params ||!params->getInstance || !params->destroyFunc)
    {
        return -1;
    }


    PlugManager * pm = PlugManager::getInstance();
    if(pm == nullptr)
    {
        return -1;
    }

    // 验证版本是否匹配
    PF_PluginAPI_Version v = pm->platformServices_.version;
    if (v.major != params->version.major)
    {
       qDebug()<<" "<<__LINE__<<" "<<__FUNCTION__<<endl;
       return -1;
    }


    std::string key((const char *)objectType);


    // exactMatchMap_ 数据结构中只能存放唯一一个
    if (pm->exactMatchMap_.find(QString(key.data())) != pm->exactMatchMap_.end())
    {
        return -1;
    }


    pm->exactMatchMap_[QString(key.data())] = *params;
    return 0;
}

const PlugManager::RegistrationMap &PlugManager::getRegistrationMap()
{
   return exactMatchMap_;
}

PF_PlatformServices &PlugManager::getPlatformServices()
{
    return platformServices_;
}


PlugManager::PlugManager()
{
    platformServices_.version.major = 1;
    platformServices_.version.minor = 0;
    platformServices_.registerObject = registerPlugin;
}

void PlugManager::Release()
{
    m_mutex.lock();
    if (pInstance)
    {
        pInstance->UnLoadAll(); //卸载所有的插件
        delete pInstance;
        pInstance = nullptr;
    }
    m_mutex.unlock();
}

void PlugManager::UnLoadAll()
{
//  销毁插件对象 以及 销毁动态库对象  清除其他信息
    if(exactMatchMap_.isEmpty())
    {
        return;
    }

    auto iter = exactMatchMap_.begin();

    while(iter != exactMatchMap_.end())
    {
        void * p = iter.value().getInstance();
        if(p)
        {
            int res = iter.value().destroyFunc(p);
            p = nullptr;
            qDebug()<<" "<<__LINE__<<" "<<__FUNCTION__<<" DestroyObject res = "<<res;
        }
        ++iter;
    }
    exactMatchMap_.clear();


    if(dynamicLibraryMap_.isEmpty())
    {
        return;
    }
    auto iterLib = dynamicLibraryMap_.begin();
    while(iterLib != dynamicLibraryMap_.end())
    {
       QLibrary * plib = iterLib.value();
       if(plib)
       {
           bool res = plib->unload();
           plib = nullptr;
           qDebug()<<" "<<__LINE__<<" "<<__FUNCTION__<<" UnloadLibrary res = "<<res;
       }
       ++iterLib;
    }
    dynamicLibraryMap_.clear();
}

QStringList PlugManager::TraversalFile(const QString &path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.dll";  //查找目录下的dll类型文件
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    qDebug()<<files;
    return files;
}
