# QScrollBar
&emsp;&emsp;是一个滚动区域控件，当内置的界面大于外部窗口的范围时会出现横向和纵向的滚动条，下面介绍一下对滚动条样式的设置
&emsp;&emsp;详见项目QScrollBar

# 滚动条的组成部分
&emsp;&emsp;下面列出经常使用的部分，**sub-line包含了up-arrow，而add-line则包含了down-arrow区域。**并且配置子控件的qss的时候需要在子控件中设置**Subcontrol-Origin**，在设置父控件中设置margin or padding or content or border
```
    up-arrow 
    sub-line 
    sub-page
    handle
    add-page
    down-arrow
    add-line
```

## 什么是 subcontrol
&emsp;&emsp;一个复杂的 widget 由多个部分组成，它们可以是一个 widget，也可以是逻辑上的部件例如 QCheckBox 由 icon 和 text 两个部分组成，不仅可以定义 text 的样式，还可以定义 icon 相关的样式，icon 部分就是 QCheckBox 的 subcontrol ::indicator。Subcontrol 的 QSS 和大多数 widget 的差不多，也支持盒子模型，可以自定义 color, background, background-color, background-image, border, padding, margin, width, height 等，也支持 **Pseudo-States(伪装态)**。Subcontrol 的绘制位置由 subcontrol-origin，subcontrol-position, top, left 来指定，就先从这几个属性开始入手。


## Subcontrol-Origin--要将子控件放在哪个区域
&emsp;&emsp;subcontrol-origin 定义在 parent widget 中绘制 subcontrol 的参考矩形，默认在 padding 的矩形中绘制。subcontrol-origin 有 4 个值可选：margin、border、padding、content。**下面是使用方法，需要注意你要将子控件放在margin中。那么父控件就要去设置margin的大小。**

``` CSS
  QScrollBar::up-arrow:vertical
  {
    subcontrol-origin:margin;
    min-height: 10px;
    background-color:deeppink;
  }
```

## Subcontrol-Position--具体要在这个矩形的哪个位置绘制
&emsp;&emsp;使用subcontrol-position 来指定，不同的 subcontrol 的 subcontrol-position 默认值不同，例如 QSlider 的 handle 的默认值是 center center，QSpinBox 的 up-button 的默认值是 right top。subcontrol-position 水平方向有 3 个值可选：left、center、rightsubcontrol-position 垂直方向有 3 个值可选：top、center、bottom



## Top 和 Left 微调 Subcontrol 的位置
&emsp;&emsp;Top 和 left 的主要作用是 :hover，:pressed 等发生时，用 top 和 left 偏移一点 subcontrol，这样就看到 subcontrol 的鼠标动作了，偏移是相对于 subcontrol-orign 和 subcontrol-position 确定的位置，top 和 left 的默认值是 0。
``` CSS
QSpinBox::up-button 
{
    subcontrol-origin: margin;
    subcontrol-position: left center;
}
 
QSpinBox::up-button:hover 
{
    top: 1px;
    left: 1px;
}
```


# 样式表一览
``` CSS

/*竖直滚动条主体*/
QScrollBar:vertical
{
    background: #309AB8;
    min-width: 30px;
    border-radius: 15px;
    margin-top: 20px;      /*设置这个是为了上下箭头位置 属于子控件知识点*/
    margin-bottom: 20px;
}

/*鼠标点击的滑块*/
QScrollBar::handle:vertical
{
    background: red;
    border-radius: 13px;
    min-height: 30px;
}


/* 翻页区域 这个一般设置成透明就行*/
QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical
{
    background:transparent;
}

/* 箭头区域 */
QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical
{
    height: 20px;
    background: transparent;
    subcontrol-origin:margin; /*设置箭头放置在父控件的区域*/
}

QScrollBar::add-line:vertical
{
    border-bottom-left-radius: 15px;
    border-bottom-right-radius: 15px;
}

QScrollBar::sub-line:vertical
{
    border-top-left-radius: 15px;
    border-top-right-radius: 15px;
}




/*上拉箭头 下拉箭头*/
QScrollBar::down-arrow:vertical,QScrollBar::up-arrow:vertical
{
    max-height: 10px;
}

QScrollBar::down-arrow:vertical
{
    image:url(./up.svg);
}
    
/*上拉箭头*/
QScrollBar::up-arrow:vertical
{
    image:url(./down.svg);
}

/*微调子控件*/
QScrollBar::up-arrow:vertical:hover,QScrollBar::up-arrow:vertical:pressed
{
    top: 1px;
    left: 1px;
}

QScrollBar::down-arrow:vertical:hover,QScrollBar::down-arrow:vertical:pressed
{
    top: 1px;
    left: 1px;
}


/*其他控件样式*/
QWidget
{
    border: none;
}

QPushButton
{
    background-color:brown;
}
```