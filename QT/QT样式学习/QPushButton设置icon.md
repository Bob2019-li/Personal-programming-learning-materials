
* 第一种方法  使用代码
``` CSS
 QIcon icon;
 icon.addFile("./imgs/test.png");
 QPushButton *delBtn=new QPushButton(icon,"测试",optWidget);
```



* 第二种方法  使用qss
``` css
QPushButton#Btn_Print
{
    qproperty-icon:url(./qss/steady/PrintPreView/ButtonPrintPreViewNormal.png);  //就是这句
    max-width: 70px; 
    min-width: 70px;
    max-height: 20px; 
    min-height: 20px; 

    font-family: "微软雅黑";
    font-size: 17px;
    color: #657496;
    text-align: right;
    border: none;
}
```