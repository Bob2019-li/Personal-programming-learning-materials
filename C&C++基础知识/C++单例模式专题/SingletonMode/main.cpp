//#pragma execution_character_set("utf-8")

#include <QCoreApplication>
#include <thread>
#include <Windows.h>
#include <iostream>
#include <mutex>
#include <QDebug>
using namespace std;

//=======================下面列举的是一些测试的开关=========================

//验证单例实现的线程是否安全
#define test 1


/*=======================第一种单例实现方法(懒汉式)=========================
存在的问题
1 内存无法正常释放   如果这个类的生存周期时整个程序的生存周期，那么可以让系统帮忙销毁
2 多线程不安全      如果程序是单线程，那么就没事了
*/
class SingleLevelOne
{
  private:
    SingleLevelOne() = default;
    SingleLevelOne(const SingleLevelOne &) = delete ;
    SingleLevelOne & operator=(const SingleLevelOne &) = delete;
    ~SingleLevelOne() = default;

  public:
    static SingleLevelOne * pInstance;
    static SingleLevelOne *getInstance();
};

SingleLevelOne * SingleLevelOne::pInstance = nullptr;
SingleLevelOne * SingleLevelOne::getInstance()
{
    if(!pInstance)
    {
#ifdef test
        Sleep(2000);
#endif
        pInstance = new SingleLevelOne();
    }
    return pInstance;
}



/*=======================第二种单例实现方法(懒汉式)=========================
 利用锁解决单例实现会有的线程安全问题

目前存在的问题
(1) 高频率的使用 getInstance 会导致多次使用锁，造成资源浪费

 */
class SingleLevelTwo
{
private:
    SingleLevelTwo() = default;
    ~SingleLevelTwo() = default;
    SingleLevelTwo(const SingleLevelTwo &) = delete;
    SingleLevelTwo & operator=(const SingleLevelTwo &) = delete;


public:
    static mutex m_mutex;
    static void Release(); //主动回收单例对象的资源
    static SingleLevelTwo * getInstance();
    static SingleLevelTwo * pInstance;

private:
    /*
     * GarbageCollect的析构函数释放静态实例时，也是在程序结束时才会调用的。
     * 所以这里写的内存释放意义不大。当然对于那些在程序结束后不自动回收空间的系统，还是需要写空间回收的。
     */
    class GarbageCollect //自动回收单例对象的资源
    {
        ~GarbageCollect()
        {
            if (pInstance)
            {
                cout <<"GarbageCollect 资源回收";
                delete pInstance;
                pInstance = nullptr;
            }
        }
    };
};

mutex SingleLevelTwo::m_mutex;
SingleLevelTwo * SingleLevelTwo::pInstance = nullptr;
SingleLevelTwo * SingleLevelTwo::getInstance()
{
      lock_guard<std::mutex> lock_(m_mutex);
      //m_mutex.lock();  这样加锁也可以
      if(!pInstance)
      {
#ifdef test
          Sleep(2000);
#endif
          pInstance = new SingleLevelTwo();
      }

//    为了减少锁的无效使用 还可以用 DCLP 来实现 但是这个也是线程不安全的
//      if(!pInstance)
//      {
//          lock_guard<std::mutex> lock_(m_mutex);
//          if(!pInstance)
//          {
//              pInstance = new SingleLevelTwo();
//          }
//      }


      //m_mutex.unlock();
      return pInstance;
}

void SingleLevelTwo::Release()
{
    std::lock_guard<std::mutex> lock_(m_mutex);
    if (pInstance)
    {
        delete pInstance;
        pInstance = nullptr;
    }
}







/*=======================第三种单例实现方法(懒汉式)=========================
 * 使用 once_flag 控制 单例类中的new SingleLevelThree 只能执行一次
 * 这个版本应该算是性能比较好的了
 */
class SingleLevelThree
{
private:
    SingleLevelThree() = default;
    ~SingleLevelThree() = default;
    SingleLevelThree(const SingleLevelThree &) = delete;
    SingleLevelThree * operator= (const SingleLevelThree &) = delete;

public:
    static mutex m_mutex;
    static SingleLevelThree * pInstance;
    static SingleLevelThree * getInstance();
    static void Release();
    static once_flag flag_new;

private:
    class gc
    {
        ~gc()
        {
            if (pInstance)
            {
                cout <<"GarbageCollect 资源回收";
                delete pInstance;
                pInstance = nullptr;
            }
        }
    };
};

mutex  SingleLevelThree::m_mutex;
once_flag SingleLevelThree::flag_new;
SingleLevelThree * SingleLevelThree::pInstance = nullptr;
SingleLevelThree * SingleLevelThree::getInstance()
{
    std::call_once(flag_new, [&]()
    {
        if(!pInstance)
        {
#ifdef test
           Sleep(2000);
#endif
           pInstance = new SingleLevelThree();
        }

    });
    return pInstance;
}
void SingleLevelThree::Release()
{
    //一直到lock_生命周期结束前都保持着互斥 我感觉用 m_mutex.lock()也一样
    std::lock_guard<std::mutex> lock_(m_mutex);
    if (pInstance)
    {
#ifdef test
        Sleep(2000);
#endif
        cout<<"SingleLevelThree::Release()   pInstance = "<<pInstance<<endl;
        delete pInstance;
        pInstance = nullptr;
    }
}


/*=======================第四种单例实现方法(饿汉式)=========================
 *   由于要进行线程同步，所以在访问量比较大，
 *   或者可能访问的线程比较多时，采用饿汉实现，可以实现更好的性能。这是以空间换时间。
 */
class SingleLevelFour
{
private:
    SingleLevelFour() = default;
    ~SingleLevelFour() = default;
    SingleLevelFour(const SingleLevelFour &) = delete;
    SingleLevelFour * operator= (const SingleLevelFour &) = delete;

    static SingleLevelFour * pInstance;
public:
    static SingleLevelFour *getInstance();
};

// 饿汉模式的关键：初始化即实例化
SingleLevelFour * SingleLevelFour::pInstance = new SingleLevelFour();

SingleLevelFour *SingleLevelFour::getInstance()
{
        return pInstance;
}


//=======================线程函数验证单例实现方法是否线程安全=================
void threadFun(int type)
{
    switch (type)
    {
        case 1:
        {
           SingleLevelOne * pOne = SingleLevelOne::getInstance();
           cout <<"[线程ID]"<< std::this_thread::get_id()<<" 线程函数获取单例地址 = "<<pOne<<endl;
           break;
        }

        case 2:
        {
           SingleLevelTwo * pTwo = SingleLevelTwo::getInstance();
           cout <<"[线程ID]"<< std::this_thread::get_id()<<" 线程函数获取单例地址 = "<<pTwo<<endl;
           break;
        }

        case 3:
        {
            SingleLevelThree * pThree = SingleLevelThree::getInstance();
            cout <<"[线程ID]"<< std::this_thread::get_id()<<" 线程函数获取单例地址 = "<<pThree<<endl;
            pThree->Release();
            break;
        }

        default:
        break;
    }
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //演示哪种单例实现的方式
    int type = -1;
    cout<<"输入要演示的单例实现方法 ";
    cin>>type;


    thread t1(threadFun,type);
    thread t2(threadFun,type);

    t1.join();
    t2.join();

    cout<<"====end====";
    return a.exec();
}
