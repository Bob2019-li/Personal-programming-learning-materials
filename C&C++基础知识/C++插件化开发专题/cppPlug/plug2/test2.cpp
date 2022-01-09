#include "test2.h"

void test2::print()
{
    cout <<" hello, this is test2 :-)"<<endl;
}

double test2::calc(double val)
{
    cout <<"0.0 val = "<<val<<endl;
    return val;
}

test2::~test2()
{
    cout <<"do  ~test2" << endl;
}
