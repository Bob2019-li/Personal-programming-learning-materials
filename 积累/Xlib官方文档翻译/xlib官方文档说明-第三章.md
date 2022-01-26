#  3 窗口函数

&emsp;&emsp;在X窗口系统中，窗口是屏幕上的一个矩形区域，用于查看图形输出。客户端应用程序通过X服务能够在一个或者多个机器上的一个或多个显示器上显示层叠以及嵌套的窗口。想在屏幕上创建窗口的用户必须将其程序通过**XOpenDisplay()**连接到X服务。本章首先讨论视觉类型和窗口属性。首先列举一下你会用到的Xlib功能:

# 功能列举

* 创建窗口
* 销毁窗口
* Map Windows
* Umap Windows
* 配置窗口
* 修改栈顺序
* 修改窗口属性

# 总结
&emsp;&emsp;本章还确定了可能产生事件的窗口操作。  

&emsp;&emsp;请注意，应用程序必须遵守与窗口管理器通信的既定约定，才能与使用中的各种窗口管理器很好地协作(请参阅**Client to Window Manager Communication**一节)。工具箱通常会为您遵守这些约定，从而减轻您的负担。工具箱通常也会用自己的版本取代本章中的许多功能。有关更多信息，请参阅所用工具包的文档。


# 3.1 视觉类型(Visual Types)
&emsp;&emsp;在某些显示硬件上，可以用多种方式处理颜色资源。例如，您可能能够处理12位深度的屏幕，该屏幕具有像素到颜色的任意映射（伪彩色），或24位深度，其中8位像素专用于红色、绿色和蓝色。 **这些处理屏幕视觉方面的不同方式称为视觉效果。** 对于显示器的每个屏幕，可能有一个屏幕不同深度支持的有效视觉类型列表。因为默认窗口和视觉类型是为每个屏幕定义的，所以大多数简单的应用程序不需要处理这种复杂性。Xlib提供宏和函数，返回默认根窗口、默认根窗口的默认深度和默认视觉类型(请参阅 **Display Macros** 和 **Determining the Appropriate Visual Type 确定适当的视觉类型**)。   

&emsp;&emsp;Xlib使用不透明的视觉(Visual)结构，其中包含有关可能的颜色映射的信息。可视化实用程序函数(参见 **Determining the Appropriate Visual Type 确定适当的可视化类型**)使用**XVisualInfo**结构将此信息返回给应用程序。与本次讨论相关的结构成员是类、红色遮罩、绿色遮罩、蓝色遮罩、每rgb位和彩色贴图大小。类成员指定屏幕的一个可能的视觉类，可以是**StaticGray、StaticColor、TrueColor、GrayScale、PseudoColor或DirectColor。**  

&emsp;&emsp;以下概念可能有助于更清楚地解释视觉类型。屏幕可以是彩色或者灰度，可以具有可写或只读的颜色映射，还可以有一个彩色地图，其索引被分解为单独的RGB片段，前提是在一个不是灰度的屏幕上。如下图所示: 这个表格完全看不懂
||颜色||灰度||
|----|----|----|----|----|
||只读模式|读写模式|只读模式|读写模式|
|未分解颜色映射 Undecomposed Colormap|静态颜色 Static Color|伪彩色 Pseudo Color|静态灰度 Static Gray|灰度 Gray Scale|
|分解颜色映射 Decomposed Colormap|真是色彩 True Color|直接着色 Direct Color|||

&emsp;&emsp;从概念上讲，当每个像素从视频内存中读出并显示在屏幕上时，它会经历一个通过索引到颜色map来查找阶段。颜色map索引可以在某些硬件上任意操作，在其他硬件上以有限的方式操作，而在其他硬件上则完全不能。视觉类型通过以下方法影响颜色map和RGB数值:
* 对于伪彩色**PseudoColor**，一个像素值通过颜色map进行索引，生成一个独立的RGB值，而且这个RGB值可以动态更改。
* 除了驱动屏幕的主色调未定义外，灰度**GrayScale**的处理方式与伪色**PseudoColor**相同。因此，客户机应该始终在颜色map中存储相同的红色、绿色和蓝色值。
* 对于**DirectColor**，像素值被分解为单独的RGB子域，而且每个子域分别地在颜色map中建立映射关系。RGB值可以动态更改。
* 除了颜色map具有预定义，只读的RGB值，**TrueColor**的处理方式和**DirectColor**相同。这些RGB值取决于服务器，但在每个主服务器中提供线性或接近线性的斜坡(These RGB values are server-dependent but provide linear or near-linear ramps in each primary.)。
* 除了颜色map具有预定义、只读、依赖服务的RGB数值，**StaticColor**和**PseudoColor**的处理方式相同。
* 除了对于任何像素值都是相等的RGB(因此会产生灰度阴影)，**StaticGray**与**StaticColor**的处理方式相同。带有两个颜色map入口的**StaticGray**可以被认为是单色。

&emsp;&emsp;红色遮罩、绿色遮罩和蓝色遮罩成员仅为**DirectColor**和**TrueColor**定义。每个都有一组连续的位，没有交叉点。bits_per_rgb成员指定红色、绿色和蓝色的不同颜色值（分别）的对数基数2。实际RGB值是无符号16位数字。colormap_size成员定义新创建的colormap中可用colormap条目的数量。对于**DirectColor**和**TrueColor**，这是单个像素子字段的大小。 (完全看不懂，硬着头皮翻译的)
