**Qt属性系统** : Q_PROPERTY()是一个宏，用来在一个类中声明一个属性property，由于该宏是qt特有的，需要用moc进行编译，故必须继承于QObject类。

> 此宏用于在继承QObject的类中声明属性。属性的行为类似于类数据成员，但它们具有可通过元对象系统访问的附加功能。


```
类型，属性名和READ（读）方法是必须的

Q_PROPERTY(
            type  //变量类型
            name  //变量名称
            (READ getFunction [WRITE setFunction] |   //向函数赋值或者从函数中读取
            MEMBER memberName [(READ getFunction | WRITE setFunction)])
            [RESET resetFunction]
            [NOTIFY notifySignal]
            [REVISION int]
            [DESIGNABLE bool]
            [SCRIPTABLE bool]
            [STORED bool]
            [USER bool]
            [CONSTANT]
            [FINAL])
```       


这是写在.h文件中 类的定义  
```
Q_PROPERTY(QString text READ getText WRITE setText)        getText 和 setText  都是在类中写好的函数
```
Qt中类的属性是给脚本和元对象系统用的，比如QtScript，QML，或者QObject::property/setProperty……，主要就是用来进行属性封装，在具体的脚本，库，qml开发中必须使用