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


bool PlugManager::Load(QString qstrPlugName)
{
    Base * pbase = nullptr;
    pbase = mapPlug[qstrPlugName].pbase;
    qDebug()<<__LINE__<<" pbase = "<<pbase;

    if(pbase != nullptr)
    {
        return true;
    }

    // 在plugins目录中查找dll文件并将文件信息保存在qstrList中
    QStringList qstrList = TraversalFile(qstrPlugPath);  //这里直接输入目录

    if(qstrList.isEmpty())
    {// 没有找到任何dll文件，返回空vector
         return false;
    }


    bool blexitPlug = false;
    for(int i = 0; i < qstrList.size(); ++i)
    {
        QString fileName = QFileInfo(qstrList[i]).baseName(); //这里只是过滤出dll文件的名字
        if(fileName == qstrPlugName)
        {
            blexitPlug = true;
        }
    }


    if(blexitPlug == false)
    {
        return false;
    }


    QString qstrPath = qstrPlugPath+"/"+qstrPlugName;
    QLibrary * plib = new QLibrary();

    plib->setFileName(qstrPath);
    ObjProc objproc = (ObjProc) plib->resolve("getObj");
    NameProc nameproc = (NameProc) plib->resolve("getName");

    if(objproc == nullptr || nameproc == nullptr)
    {
        return false;
    }

    if(nameproc() != qstrPlugName)
    {
        return false;
    }

    PlugInfo pluginfo;
    pluginfo.pbase = objproc();
    pluginfo.plib  = plib;

    mapPlug.insert(nameproc(),pluginfo);
    return true;
}

bool PlugManager::UnLoad(QString qstrPlugName)
{
    Base * pbase = nullptr;
    QLibrary * plib = nullptr;

    pbase = mapPlug[qstrPlugName].pbase;
    plib  = mapPlug[qstrPlugName].plib;

    qDebug()<<"unload pbase = "<<pbase;
    qDebug()<<"unload plib  = "<<plib;

    if(pbase == nullptr && plib == nullptr)
    {
        qDebug()<<__FUNCTION__<<" "<<__LINE__<<" pbase = nullptr  plib = nullptr";
        return true;
    }
    else
    {
        //==============================================
        //这两个必须先销毁pbase 再进行unload 不能反过来，我在想是不是只需要执行unload即可
        if(pbase != nullptr)
        {
            delete  pbase;
            mapPlug[qstrPlugName].pbase = nullptr;
        }

        //卸载lib
        plib->unload();
        //==============================================
        //销毁空间
        if(plib != nullptr)
        {
            delete  plib;
            mapPlug[qstrPlugName].plib = nullptr;
        }

        //删除插件的名称
        auto iterator = mapPlug.find(qstrPlugName);
        mapPlug.erase(iterator);
    }
    return true;
}

void PlugManager::UnLoadAll()
{
    auto iter = mapPlug.begin();
    while (iter != mapPlug.end())
    {
         UnLoad(iter.key());
    }
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

void PlugManager::SetPlugLoadPath(QString qstrPath)
{
    qstrPlugPath = qstrPath;
}

Base *PlugManager::GetPlugInstance(QString qstrPlugName)
{
    return mapPlug[qstrPlugName].pbase;
}
