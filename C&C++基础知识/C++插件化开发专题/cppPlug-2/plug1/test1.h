#ifndef TEST1_H
#define TEST1_H

//插件实际实现的位置

#include "base.h"
#include <mutex>
#include <QDebug>

using namespace  std;

class test1:public Base
{
public:

    static std::mutex m_mutex;
    static void * getInstance();
    static int destroy(void *p);
    static void * pInstance;

    virtual void print(void);
    virtual double calc(double val);

private:
    test1() = default;
    ~test1() = default;
    test1(const test1 &) = delete;
    test1 & operator=(const test1 &) = delete;
};

#endif // TEST1_H
