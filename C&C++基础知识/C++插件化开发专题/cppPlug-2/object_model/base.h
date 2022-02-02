#ifndef BASE_H_
#define BASE_H_

//插件的抽象基类在这里声明
class Base {
public:
    virtual ~Base() = default;
    virtual void print(void) = 0;
    virtual double calc(double val) = 0;
};

#endif
