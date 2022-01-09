# 读DCLP文章浅尝辄止

<span style='font-size:18px; font-family:微软雅黑;'>

&emsp;&emsp;先以一段传统的单例代码为开始，文章首先肯定下面的代码在单线程中会执行的不错，但是在多线程中则会出现问题，当两个线程中开始执行下面的代码时，会容易出现两个线程中 pInstance 变量指向的不是同一个地址。假设线程A进入instance()函数，执行第15行代码，此时线程被挂起(suspended)。在A被挂起时，它刚判断出pInstance是空值，也就是说Singleton的对象还未被创建。现在线程B开始运行，进入instance()函数，并执行第15行代码。线程B也判断出pInstance为空，因此它继续执行第17行，创建出一个Singleton对象，并将pInstance指向该对象，然后把pInstance返回给instance()函数的调用者。之后的某一时刻，线程A恢复执行，它接着做的第一件事就是执行第17行：创建出另一个Singleton对象，并让pInstance指向新对象。这显然违反了“单例(singleton)”的本意，因为现在我们有了两个Singleton对象。  

```
class Singleton {
public :

static Singleton * instance ( ) ;

 
 . . .


 private :

 static Singleton * pInstance ;

} ;


// from the implementation file 以下代码来自实现文件

Singleton * Singleton :: pInstance = 0 ;

Singleton * Singleton :: instance ( ) 
{

    if ( pInstance == 0 ) 
    {

          pInstance = new Singleton ;

    }

    return pInstance ;
    }
```

&emsp;&emsp;接下来文章中又给出了解决多线程问题的一个常规解法。使用锁实现对变量的控制,这个解决办法的缺点在于可能会导致昂贵的程序执行代价：每次访问该函数都需要进行一次加锁操作。但实际中，我们只有pInstance初始化时需要加锁。也就是说加锁操作只有instance()第一次被调用时才是必要的。如果在程序运行过程中，intance()被调用了n次，那么只有第一次调用锁起了作用。既然另外的n-1次锁操作都是没必要的，那么我们为什么还要付出n次锁操作的代价呢？DCLP就是设计来解决这个问题的。
```
Singleton * Singleton :: instance ( ) 
{
     // acquire lock (params omitted for simplicity) 加锁（为了简便起见，代码中忽略了加锁所需要的参数）

    Lock lock ;   //局部变量

    if ( pInstance == 0 ) 
    {

       pInstance = new Singleton ;

    }

return pInstance ;

} // release lock (via Lock destructor) // 解锁（通过Lock的析构函数实现）


//接着这个话题，文章又引出了DCLP(双重检查锁定模式)这个概念。其实这个检查模式是在上面代码的基础上实现的，就是为了减少锁的使用。
Singleton * Singleton :: instance ( ) 
{

  if ( pInstance == 0 ) 
  { // 1st test 第一次检查  这是新增加的判断

      Lock lock ;

      if ( pInstance == 0 ) 
      { // 2nd test 第二次检查   这是原来的基础

          pInstance = new Singleton ;

      }
  }

      return pInstance ;

}
```



&emsp;&emsp;文章又向着计算机世界的更深处继续，DCLP的执行过程中必须确保机器指令是按一个可接受的顺序执行的这中间的一段我就简化了，文章的大致意思编译器会自动的优化代码，这会导致DCLP代码最终的执行顺序与程序实际编写的执行顺序不一样，这就会导致代码不可靠，然后文章又指出，一般人是不可能战胜编译器优化的结果(毕竟是一伙大佬几十年的努力)。那么DCLP就不能用了吗？


&emsp;&emsp;好吧，我摊牌了，后面我是基本看不懂了，直接芭比Q了......  不过我最后还是把结论贴一下吧


&emsp;&emsp;从以上讨论中我们可以得出许多经验。首先，请记住一点：基于分时的单处理机并行机制与真正跨多处理器的并行是完全不同的。这就是为什么在单处理器架构下针对某个编译器的线程安全的解决办法，在多处理器架构下就不可用了。即使你使用相同的编译器，也可能导致这个问题（这是个一般性结论，不仅仅存在于DCLP中）。DCLP以及它在C/C++语言中的问题证实了这么一个结论： **想使用一种没有线程概念的语言来实现具有线程安全性的代码(或者其他形式的并发式代码)有着固有的困难。编程中对多线程的考虑很普遍，因为它们是代码生成中的核心问题。**

</span>