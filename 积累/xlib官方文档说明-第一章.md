
# 1 介绍 Xlib

&emsp;&emsp;X窗口系统是麻省理工学院(简称MIT)设计的网络透明窗口系统。X显示服务器运行在具有单色或彩色位图显示硬件的计算机上。 
  
&emsp;&emsp;服务器将用户输入分发到位于同一台机器上或网络中其他位置的各种客户端程序，并接受这些程序的输出请求。Xlib是一个C子程序库，应用程序（客户端）使用它通过流连接与窗口系统进行接口。尽管客户机通常与它正在交谈的X服务器在同一台机器上运行, **但情况并非如此。(this need not be the case)**   

&emsp;&emsp;Xlib---C语言X接口是X窗口系统协议的低级C语言接口的参考指南。它既不是编程X窗口系统的教程，也不是用户指南。相反，它提供了库中每个函数的详细描述以及相关背景信息的讨论。Xlib---C语言X接口假定对图形窗口系统和C编程语言有基本了解。其他高级抽象（例如，X工具包提供的抽象）构建在Xlib库之上。有关这些高级库的更多信息，请参阅相应的工具包文档。X窗口系统协议提供了关于X的行为的决定性词汇。虽然此处显示了其他信息，但协议文件是主导文件。

&emsp;&emsp;为了介绍X编程，本章讨论：

## 1.1 X窗口系统概述
&emsp;&emsp;本书中使用的一些术语是X所独有的，而其他窗口系统所共有的术语在X中有不同的含义。您可能会发现参考本书末尾的**词汇表(glossary)**很有帮助。  
&emsp;&emsp;X窗口系统支持一个或多个包含重叠窗口或子窗口的屏幕。**屏幕**是一个物理监视器和硬件，可以是彩色、灰度或单色。每个显示器或工作站可以有多个屏幕。单个X服务器可以为任意数量的屏幕提供显示服务。为单个用户提供的一组屏幕，带有一个键盘和一个指针（通常是鼠标），称为**显示器display(虽然是翻译成显示器但是，我感觉不对)**。  
&emsp;&emsp;X服务器中的所有窗口都按严格的层次结构排列。在每个层次结构的顶部是一个根窗口，它覆盖每个显示屏幕。每个根窗口部分或全部被子窗口覆盖。子窗口也可能有自己的子窗口。这样，应用程序可以在每个屏幕上创建任意深度的树。X为windows提供图形、文本和光栅操作。  
&emsp;&emsp;子窗口可以大于其父窗口。这意味着，子窗口的部分或者全部都可以超出其父窗口的边界，但是所有超出的部分都会被父窗口裁剪掉。如果一个窗口的多个子窗口具有重叠位置，则其中一个子窗口将被视为位于其他子窗口之上或高于其他子窗口，从而使其模糊。**输出到其他窗口覆盖的区域将被窗口系统抑制，除非该窗口具有后备存储。Output to areas covered by other windows is suppressed by the window system unless the window has backing store.感觉翻译的不到位**  **如果一个窗口被第二个窗口遮挡，则第二个窗口仅遮挡第二个窗口的祖先，这些祖先也是第一个窗口的祖先。If a window is obscured by a second window, the second window obscures only those ancestors of the second window, which are also ancestors of the first window.**  

&emsp;&emsp;窗口的边框宽度为零个或多个像素，可以是您喜欢的任何图案（像素贴图）或纯色。窗口通常（但不总是）具有背景图案，当打开时，背景图案将由窗口系统重新绘制。子窗口隐藏其父窗口，父窗口中的图形操作通常由子窗口剪裁。  

&emsp;&emsp;每个窗口和pixmap都有自己的坐标系。坐标系的X轴水平，Y轴垂直，原点[0，0]位于左上角。坐标是积分，以像素为单位，并与像素中心重合。对于窗口，原点位于左上角内侧的边框内。  

&emsp;&emsp;X不保证保留windows的内容。当一个窗口的部分或全部被隐藏，然后返回到屏幕上时，其内容可能会丢失。然后，服务器向客户端程序发送一个**Expose**事件，通知它部分或全部窗口需要重新绘制。程序必须准备好按需重新生成windows内容。 

&emsp;&emsp;X还提供图形对象的屏幕外存储，称为pixmaps。单平面（深度1）像素贴图有时称为位图。Pixmaps可以在大多数图形功能中与windows互换使用，并在各种图形操作中用于定义图案或平铺。Windows和pixmaps一起被称为Drawable。 

&emsp;&emsp;Xlib中的大多数函数只是将请求添加到输出缓冲区。这些请求稍后在X服务器上异步执行。返回存储在服务器中的信息值的函数在收到显式回复或发生错误之前不会返回（即，它们会阻塞）。您可以提供一个错误处理程序，在报告错误时将调用该处理程序。  

&emsp;&emsp;如果客户机不希望异步执行请求，它可以在请求之后调用**XSync（）**，直到发送并执行所有先前缓冲的异步事件为止。作为一个重要的副作用，Xlib中的输出缓冲区总是通过调用从服务器返回值或等待输入的任何函数来刷新。

&emsp;&emsp;许多Xlib函数将返回整数资源ID，这允许您引用存储在X服务器上的对象。这些类型可以是**Window、Font、Pixmap、Colormap、Cursor和GContext**，如文件<X11/X.h>中定义的。这些资源由请求创建，并在请求或连接关闭时被销毁（或释放）。这些资源中的大多数可能在应用程序之间共享，事实上，窗口是由窗口管理器程序显式操作的。字体和光标在多个屏幕上自动共享。字体根据需要加载和卸载，并由多个客户端共享。字体通常缓存在服务器中。Xlib不支持在应用程序之间共享图形上下文。

&emsp;&emsp;将事件通知客户端程序。事件可能是请求的副作用（例如，重新加载窗口会生成公开事件），也可能是完全异步的（例如，来自键盘）。客户端程序要求通知事件。因为其他应用程序可以向您的应用程序发送事件，所以程序必须准备好处理（或忽略）所有类型的事件。

&emsp;&emsp;输入事件（例如，按下的键或移动的指针）从服务器异步到达并排队，直到显式调用（例如，**XNextEvent（）**或**XWindowEvent（）**）。此外，一些库函数（例如，**XRaiseWindow（）**）会生成**Expose**和**ConfigureRequest**事件。这些事件也以异步方式到达，但是客户端希望当调用一些可使服务器生产事件的函数时能够通过调用**Xsync()**显示的等待这些事件

## 1.2 错误
&emsp;&emsp;一些函数返回状态，一个整数错误指示。如果函数失败，则返回零。**如果函数返回的状态为零，则它没有更新返回参数。**由于C不提供多个返回值，许多函数必须通过写入客户端传递的存储来返回结果。默认情况下，错误由标准库函数或您提供的函数处理。返回字符串指针的函数在字符串不存在时返回空指针。  

&emsp;&emsp;X服务器在检测到协议错误时会报告这些错误。如果给定的请求可能生成多个错误，服务器可以报告其中任何一个错误。  

&emsp;&emsp;由于Xlib通常不会立即将请求传输到服务器（即，它会对请求进行缓冲），因此报告错误的时间可能比实际发生的时间晚得多。但是，出于调试目的，Xlib提供了一种强制同步行为的机制（请参阅**启用或禁用同步 Enabling or Disabling Synchronization**）。启用同步后，将在生成错误时报告错误。

&emsp;&emsp;当Xlib检测到错误时，它调用一个错误处理程序，您的程序可以提供该程序。如果不提供错误处理程序，则会打印错误，程序将终止。

## 1.3 标准头文件
&emsp;&emsp;以下包含文件是Xlib标准的一部分：  

### X11/Xlib.h  
&emsp;&emsp;这是Xlib的主头文件。大多数Xlib符号都是通过包含此文件来声明的。此文件还包含预处理器符号XlibSpecificationRelease。此符号定义为本标准版本中的6。（Xlib的第5版是第一个具有此符号的版本。）  

### X11/X.h  
&emsp;&emsp;此文件声明应用程序要使用的X协议的类型和常量。它被X11/Xlib.h头文件自动包含了，所以应用程序代码永远不需要直接引用这个文件。

### X11/Xcms.h
&emsp;&emsp;该文件包含**颜色管理功能(Color Management Functions)**中描述的许多颜色管理设施的符号。此文件中声明了前缀为“XCM”的所有函数、类型和符号，以及颜色转换上下文宏。在包含此文件之前必须先包含X11/Xlib.h文件  

### X11/Xutil.h
&emsp;&emsp;该文件声明了用于客户端间通信和应用程序实用程序功能的各种功能、类型和符号，这些在**客户端间通信功能(Inter-Client Communication Functions)**和**应用程序实用程序功能(Application Utility Functions)**中有描述。X11/Xlib。在包含此文件之前必须先包含X11/Xlib.h文件。

### X11/Xresource.h
&emsp;&emsp;此文件声明资源管理器设施的所有函数、类型和符号，这些在**资源管理器函数(Resource Manager Functions)**中有描述。

### X11/Xatom.h
&emsp;&emsp;该文件声明了所有前缀为“XA_”**预定义的原子 predefined atoms**

### X11/cursorfont.h
&emsp;&emsp;此文件声明标准光标字体的光标符号，这些符号都列在**X字体光标 X Font Cursors**中。所有光标符号都有前缀“XC”。

### X11/keysymdef.h
&emsp;&emsp;该文件声明了所有标准的KeySym值，这些值是前缀为“XK”的符号。键符号按组排列，预处理器符号控制每个组的包含。必须在包含文件之前定义预处理器符号，以获取相关值。预处理器符号是**XK_MISCELLANY, XK_LATIN1, XK_LATIN2, XK_LATIN3, XK_LATIN4, XK_KATAKANA, XK_ARABIC, XK_CYRILLIC, XK_GREEK, XK_TECHNICAL, XK_SPECIAL, XK_PUBLISHING, XK_APL, XK_HEBREW, XK_THAI, and XK_KOREAN.**

### X11/keysym.h
&emsp;&emsp;此文件定义预处理器符号**XK_MISCELLANY, XK_LATIN1, XK_LATIN2, XK_LATIN3, XK_LATIN4, and XK_GREEK**，并且它包含了X11/keysymdef.h

### X11/Xlibint.h
&emsp;&emsp;此文件声明**扩展名 Extensions**中描述的用于扩展名的所有函数、类型和符号。此文件自动包含X11/Xlib.h。

### X11/Xproto.h
&emsp;&emsp;此文件声明基本X协议的类型和符号，用于实现扩展。它自动被X11/Xlibint.h文件所包含,所以应用程序和扩展代码永远不需要直接引用这个文件。

### X11/Xprotostr.h
&emsp;&emsp;此文件声明基本X协议的类型和符号，用于实现扩展。它自动被X11/Xproto.h文件所包含，所以应用程序和扩展代码永远不需要直接引用这个文件。

### X11/X10.h
&emsp;&emsp;此文件声明用于X10兼容函数的所有函数、类型和符号，这些在**兼容函数 Compatibility Functions**中有描述。


## 1.4 通用的值和类型
&emsp;&emsp;以下符号由Xlib定义，并在整个手册中使用：  
* Xlib定义类型**Bool**为布尔值，值为**True**或**False**。
* **None**是通用的空资源ID或atom。
* **XID**类型用于通用资源**ID们 IDs 这里应该是复数的意思吧**。
* 类型**XPointer**被定义为char*并用作指向数据的通用不透明指针。 



## 1.5 Xlib中的命名和参数约定
&emsp;&emsp;Xlib在函数的命名和语法方面遵循许多约定。考虑到您还记得函数需要什么信息，这些约定旨在使函数的语法更可预测。主要的命名约定有:  
*  为了将X符号与其他符号区分开来，库对外部符号使用混合大小写。根据现有惯例，变量保留小写，用户宏保留所有大写。
*  Xlib的函数名都以X字符开头
*  所有函数名和符号的开头都大写。
*  所有用户可见的数据结构都以大写X开头。更通常地说，用户可能使用的任何**解引用 dereference**都是以X字符开头的。
*  宏和其他符号不以大写X开头。为了将它们与所有用户符号区分开来，宏中的每个单词都大写。
*  数据结构中的所有元素或变量都是小写的。在需要的地方，复合词是用下划线（_）构成的。
*  被使用的显示参数，始终位于参数列表的第一位。
*  使用的所有资源对象都出现在参数列表的开头，紧跟在显示参数之后。
*  当图形上下文与其他类型的资源（最常见的是可绘制资源）一起出现时，图形上下文出现在参数列表中其他资源之后。绘制资源优先于其他资源  **(这个完全没看懂When a graphics context is present together with another type of resource (most commonly, a drawable), the graphics context occurs in the argument list after the other resource. Drawables outrank all other resources.)**

*  在参数列表中，源参数始终位于目标参数之前。
*  在参数列表中，x参数始终位于y参数之前。
*  在参数列表中，宽度参数始终位于高度参数之前。
*  如果同时使用x、y、width和height参数，则x和y参数始终位于width和height参数之前。
*  当掩码与结构一起出现时，掩码始终位于参数列表中指向该结构的指针之前。


## 1.6 编程注意事项
* 在X中(我想应该是Xlib中)的坐标和大小实际上是16位的变量(就是2个字节)。做出此决定是为了将给定性能级别所需的带宽降至最低。坐标通常在接口中声明为int。大于16位的值会自动截断。尺寸（宽度和高度）声明为无符号量。
* 键盘是不同制造商工作站之间最大的变量。如果你希望你的程序是可移植的，你应该在这里特别保守。**Keyboards are the greatest variable between different manufacturers' workstations. If you want your program to be portable, you should be particularly conservative here. 我想这个意思就是对应键盘外设的支持吧**
* 许多显示系统的屏幕外内存有限。如果可以，您应该尽量减少使用像素贴图和备份存储。
* **用户应该控制他自己的屏幕空间he user should have control of his screen real estate. 我感觉就是要对自己的屏幕负责**。因此，您应该编写对窗口管理做出反应的应用程序，而不是假定控制整个屏幕。但是，在顶级窗口中执行的操作取决于应用程序。有关更多信息，请参阅**客户端间通信功能 Inter-Client Communication Functions**和**客户端间通信约定手册 Inter-Client Communication Conventions Manual**。
  


## 1.7 字符集和编码
&emsp;&emsp;这个就不翻译

## 1.8 格式约定
&emsp;&emsp;主要讲的是，xlib官方说明中对函数变量的说明方法，以便读者使用和理解，就是叫你怎么看文档

