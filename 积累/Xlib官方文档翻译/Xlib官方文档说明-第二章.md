 # 显示函数
 &emsp;&emsp; **在您的程序可以使用显示器之前，您必须建立到X服务器的连接.**一旦建立了连接，就可以使用本章讨论的Xlib宏和函数返回有关显示器的信息。本章讨论如何：

 * 打开连接到显示器
 * 获取有关显示器、图像格式和屏幕的信息
 * 释放客户端创建的数据
 * 关闭断开显示器

<br/>

 &emsp;&emsp;本章最后对与X服务器的连接关闭时发生的情况进行了一般性讨论。

 ## 2.1打开Display(这是个结构体)
 &emsp;&emsp;为了打开一个为了控制显示器的X服务链接，使用**XOpenDisplay()**  

```
Display *XOpenDisplay(display_name)  
                char *display_name; //指定要作为连接的硬件显示器名称，在符合POSIX的系统上，如果display_名称为**NULL**，则默认为 **DISPLAY** 环境变量的值。
```

### 描述
&emsp;&emsp;显示名称的编码和解释取决于实现。支持主机可移植字符编码中的字符串；对其他字符的支持取决于实现。在符合POSIX标准的系统上，显示名称或显示环境变量可以是以下格式的字符串：
```
hostname:number.screen_number

```
* hostname      指定物理连接显示器的主机的名称。主机名后面可以是单冒号（：）或双冒号（：：）。
* number        指定该主机上显示服务器的编号。您可以选择在该显示编号后面加句点（.）。一个CPU可以有多个显示器。多个显示器通常从零开始编号。
* screen_number 指定要在该服务器上使用的屏幕。多个屏幕可以由单个X服务器控制。screen_编号设置一个内部变量，如果您使用的是C以外的语言，则可以使用**DefaultScreen()宏**或**XDefaultScreen()**函数访问该变量（请参见 **Display Macros**）。

&emsp&emsp;例如，下面将指定名为 “dual-headed” 的计算机上显示0的屏幕1：
```
dual-headed:0.1
```

&emsp;&emsp;函数的作用是：返回一个**Display**结构体，该结构用作与X服务器的连接，并包含有关该X服务器的所有信息。**XOpenDisplay()**通过TCP或DECnet通信协议，或通过某些本地进程间通信协议，将应用程序连接到X服务器。如果主机名是主机机器名，并且主机名和显示号之间用一个冒号（：）分隔，那么**XOpenDisplay()**将使用TCP流进行连接。如果未指定主机名，Xlib将使用它认为最快的传输。如果主机名是主机机器名，并且主机名和显示号之间用一个双冒号（：：）分隔，那么XOpenDisplay（）将使用DECnet进行连接。单个X服务器可以同时支持任何或所有这些传输机制。一个特定的Xlib实现可以支持更多这样的传输机制。  

&emsp;&emsp;如果成功，**XOpenDisplay（）** 将返回指向X11/Xlib中定义的 **Display** 结构的指针。如果**XOpenDisplay（）**未成功，则返回NULL。成功调用**XOpenDisplay（）**后，客户端可以使用显示器中的所有屏幕。**display_name参数**中指定的屏幕编号由**DefaultScreen（）宏 或者 XDefaultScreen（）函数**返回。只能使用信息宏或函数访问**Display**和**Screen**结构的元素。有关使用宏和函数从**Display**结构获取信息的信息，请参见**Display Macros**。

&emsp;&emsp;X服务器可以实现各种类型的访问控制机制（请参阅**Controlling Host Access**）。

*** 

<br/>


# 2.2 获取有关Display、图片格式以及屏幕的信息
&emsp;&emsp;Xlib的库提供了大量可以从Display结构体中返回数据的宏定义和 **函数(corresponding functions)**, 宏定义用于C语言编程，其对应的函数等价物用于其他语言绑定。本节讨论的内容有:

* Display 的宏定义
* 图片格式的宏定义
* 屏幕的宏定义
