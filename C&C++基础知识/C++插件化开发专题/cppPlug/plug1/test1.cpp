#include "test1.h"

void test1::print()
{
    cout <<" hello, this is test1 :-)"<<endl;
}

double test1::calc(double val)
{
    cout <<"0.0 val = "<<val<<endl;
    return val;
}

test1::~test1()
{
    cout <<"do  ~test1" << endl;
}
