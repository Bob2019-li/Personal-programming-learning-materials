#ifndef BASE_H_
#define BASE_H_

//所有插件继承的基类
class Base {
public:
    virtual ~Base() = default;
    virtual void print(void) = 0;
    virtual double calc(double val) = 0;
};

#endif
