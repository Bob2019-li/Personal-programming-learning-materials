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

### 2.2.1 Display 的宏定义
&emsp;&emsp;应用程序不应该直接修改Display和Screen结构体中任何部分。他们的成员应该被认为是只读的，尽管它们可能会因显示器上的其他操作而改变。下面列出了C语言宏、它们对应的用于其他语言绑定的函数等价物，以及它们都可以返回的数据。 

&emsp;&emsp;下面以表格的形式列出宏定义以及解释

|宏定义|简单解释|
|----|----|
|AllPlanes|返回一个值，所有位都设置为1，适合在过程的平面参数中使用。(没看懂Both return a value with all bits set to 1 suitable for use in a plane argument to a procedure.)|
|BlackPixel WhitePixel | 获取屏幕的黑色、白色像素值，但是按照解释来说**实际RGB（红色、绿色和蓝色）值可在某些屏幕上设置，并且在任何情况下，实际上可能不是黑色或白色**|
|ConnectionNumber|返回指定连接到Xserver的连接号，如果是POSIX系统，那返回的参数是文件描述符|
|DefaultColormap|返回指定屏幕上分配的默认颜色映射ID(返回值大概是一个map值)大多数常规的颜色分配都应该使用这个颜色映射。|
|DefaultDepth|返回指定屏幕的默认根窗口的深度(平面数)|
|XListDepths|返回给定屏幕上可用的深度数|
|DefaultGC|返回指定屏幕根窗口的默认图形环境|
|DefaultRootWindow|返回默认屏幕的根窗口|
|DefaultScreenOfDisplay|返回指向默认屏幕的指针|
|ScreensOfDisplay|返回一个指向指定编号的屏幕指针|
|DefaultScreen|返回XOpenDisplay()函数引用的默认屏幕编号，此宏或函数应用于检索仅使用单个屏幕的应用程序中的屏幕编号|
|DefaultVisual|返回指定屏幕的默认视觉类型|
|DisplayCells|返回默认颜色映射中的条目数|
|DisplayPlanes|返回指定屏幕的根窗口的深度|
|DisplayString|返回当前显示打开时传递给XOpenDisplay（）的字符串。在符合POSIX的系统上，如果传递的字符串为NULL，则在当前显示打开时，这些字符串将返回显示环境变量的值。对于调用fork系统调用并希望从子进程打开到相同显示的新连接的应用程序以及打印错误消息的应用程序来说，这些都很有用。|
|XExtendedMaxRequestSize|如果指定的显示不支持扩展长度协议编码，则XExtendedMaxRequestSize（）函数返回零；否则，它将返回使用扩展长度编码的服务器支持的最大请求大小（以4字节为单位）。|
|XMaxRequestSize||
|LastKnownRequestProcessed||
|NextRequest|提取用于下一个请求的完整序列号。每个显示器连接的序列号都单独维护。|
|ProtocolVersion|返回与所连接显示器关联的X协议的主要版本号（11）
|ProtocolRevision|返回X服务器的次要协议修订号。|
|QLength|回所连接显示器的事件队列长度。|
|RootWindow|返回根窗口。对于需要绘制特定屏幕的函数和创建顶级窗口，这些函数非常有用。|
|ScreenCount|返回可用屏幕的数量|
|ServerVendor|返回指向以null结尾的字符串的指针，该字符串提供X服务器实现所有者的某种标识。如果服务器返回的数据采用拉丁可移植字符编码，则字符串采用主机可移植字符编码。否则，字符串的内容取决于实现。|
|VendorRelease|返回一个与供应商发布的X服务器相关的数字。|  

### 2.2.2图片格式的宏定义
&emsp;&emsp; 略
### 2.2.3屏幕的宏定义
&emsp;&emsp; 略

&emsp;&emsp;显示结构的所有其他成员（即未定义宏的成员）都是Xlib专用的，不得使用。应用程序不得直接修改或检查显示结构的这些私有成员。  

&emsp;&emsp;**XDisplayWidth(), XDisplayHeight(), XDisplayCells(), XDisplayPlanes(), XDisplayWidthMM(), and XDisplayHeightMM()** 这几个函数在下一章节命名是错误的，正确的命名形式是**ScreenXXXXX或者XScreenXXXXX**， 所以下一章节我会注意这个的。

<br/>


## 2.3 生成一个 **无操作(NoOperation)** 协议请求

&emsp;&emsp;使用函数**XNoOp(Display *display);**  
&emsp;&emsp;display参数是一个指定的Xserver链接。函数的作用是向X服务器发送NoOperation协议请求，从而执行连接。


## 2.4 释放客户端创建的数据

&emsp;&emsp;要释放由Xlib函数创建的内存中数据，请使用XFree(void * data)
&emsp;&emsp;data 是指定要被释放的数据
&emsp;&emsp;一般情况下使用此函数来释放由Xlib分配的空间，除非你使用的Xlib对象指定了用哪个函数去释放。**注意函数参数不能为NULL。**


## 2.5 关闭Display结构体
&emsp;&emsp;使用**XCloseDisplay()**来关闭一个display或者断开Xserver的链接。
&emsp;&emsp;Xlib提供了一个功能，允许客户端拥有的资源在客户端连接关闭后继续存在。可以使用**XSetCloseDownMode()**来改变客户端关闭的模式。

## 2.6 Xserver连接关闭操作
&emsp;&emsp;当通过显式调用XCloseDisplay（）或通过退出的进程关闭X服务器与客户端的连接时，X服务器将执行以下自动操作：  
* 它否认客户端拥有者的所有选择(**It disowns all selections owned by the client 参见 XSetSelectionOwner()**)，我认为这是一种安全机制，就是断开连接后，再恢复，但是这个拥有者已经失效

* 如果客户端已主动抓取指针或键盘。则会执行**XUngrabPointer()**和**XUngrabKeyboard()**
* 如果客户端抓取了服务器则会执行**XUngrabServer()**
* 它将释放客户进行的所有被动抓取
* 它将标记由客户端永久或临时方式分配的所有资源(包括 颜色映射条目(**colormap entries**))，具体取决于关闭模式是**RetainPermanent**还是**RetainTemporary**。但是，这并不阻止其他客户端应用程序显式销毁资源(请参阅**XSetCloseDownMode()**)。  

&emsp;&emsp;关闭模式为**DestroyAll**时，X服务器将销毁客户端的所有资源，如下所示：
* 它检查客户机存储集中的每个窗口，以确定它是否是客户机创建的窗口的次窗口（子窗口）。（存储集是其他客户端窗口的列表，称为存储集窗口。）如果是这样，X服务器会将存储集窗口重新分配给最近的祖先，以便该存储集窗口不会低于客户端创建的窗口。重新分页保留存储集窗口左上角外角的绝对坐标（相对于根窗口）不变。
* 如果存储集窗口未映射，它将在存储集窗口上执行MapWindow请求。即使存储集窗口不是客户端创建的窗口的下级窗口，X服务器也会执行此操作。
* 它将销毁客户端创建的所有窗口。
* 它对客户端在服务器中创建的每个非窗口资源（例如字体、Pixmap、光标、Colormap和GContext）执行适当的空闲请求。
* 它释放客户端应用程序分配的所有颜色和颜色映射项。

&emsp;&emsp;当与X服务器的最后一个连接关闭时，会发生附加处理。X服务器经历了一个无连接和有连接的循环。当使用DestroyAll的模式关闭与X服务器的最后一个连接时，X服务器会执行以下操作：

* 它将重置其状态，就像它刚刚启动一样。X服务器首先销毁以**RetainPermanent**或**RetainTemporary**模式终止的客户端的所有延迟资源。
* 它删除除预定义的atom标识符之外的所有标识符。
* 它删除所有根窗口上的所有属性。
* 它重置所有设备映射和属性（例如，按键、铃声音量和加速度）以及访问控制列表。
* 它将恢复标准的根平铺(root tiles 应该是界面展示的一种方式)和光标。
* 它将恢复默认字体路径。
* 它将输入焦点恢复为状态**PointErrorot**。

&emsp;&emsp;但是，如果关闭模式设置为**RetainPermanent**或**RetainTemporary**，则不会重置X服务器。


## 2.7 Xlib多线程使用
&emsp;&emsp;在具有线程的系统上，可以提供支持以允许多个线程同时使用Xlib。要初始化对并发线程的支持，请使用**XInitThreads()**。 **XLockDisplay()**和**XUnlockDisplay()**两个函数应该是和互斥量一样的作用，用于锁住Display这个东西。

## 2.8 内部连接
&emsp;&emsp;除了与X服务器的连接之外，Xlib实现可能还需要与其他类型的服务器的连接(比如输入法服务器 参见Locales and Internationalized Text Functions)。使用多个显示器的工具
程序或者客户端，或者使用结合了其他输入的显示器，需要获得这些额外的连接并正确地阻塞直到输入可用，并且需要在输入可用时处理该输入。在Xlib事件函数中使用单个显示和块进行输入的简单客户端不需要使用这些功能。
&emsp;要跟踪显示器的内部连接，**XAddConnectionWatch()**
&emsp;要停止跟踪显示器的内部连接，**XRemoveConnectionWatch()**
&emsp;&emsp;处理内部连接上的输入,**XProcessInternalConnection()**
&emsp;&emsp;要获取显示器的所有当前内部连接，**XInternalConnectionNumbers()**
