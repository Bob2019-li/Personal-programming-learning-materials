#include "test1.h"


std::mutex test1::m_mutex;
void * test1::pInstance = nullptr;


void * test1::getInstance()
{
    m_mutex.lock();
    if(!pInstance)
    {
        pInstance = new test1();
    }
    m_mutex.unlock();
    return pInstance;
}

int test1::destroy(void *p)
{
    m_mutex.lock();
    if (p == nullptr)
    {
      return -1;
    }
    delete (test1 *)p;
    m_mutex.unlock();
    return 0;
}

void test1::print()
{
    qDebug()<<"hello this is plugin 1 :-)";
}

double test1::calc(double val)
{
    qDebug()<<"value = "<<val;
    return val;
}

