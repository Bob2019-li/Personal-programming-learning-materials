#ifndef TEST1_H
#define TEST1_H

//插件实际实现的位置

#include "base.h"
#include <iostream>


using namespace  std;

class test2:public Base
{
public:
    void   print(void);
    double calc(double val);
    ~test2();
};

#endif // TEST1_H
