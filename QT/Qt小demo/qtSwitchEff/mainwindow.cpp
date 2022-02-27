#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pAnimgroup = new QParallelAnimationGroup;
    connect(m_pAnimgroup,SIGNAL(finished()),this,SLOT(SlotFinished()));

    m_vecbtn.push_back(ui->btn_1);
    m_vecbtn.push_back(ui->btn_2);
    m_vecbtn.push_back(ui->btn_3);
    m_vecbtn.push_back(ui->btn_4);
    m_vecbtn.push_back(ui->btn_5);
    m_vecbtn.push_back(ui->btn_6);
    m_vecbtn.push_back(ui->btn_7);

    int icount = QPushButton::staticMetaObject.propertyCount();
    for(int i = 0; i < icount; ++i)
    {
        qDebug()<<QPushButton::staticMetaObject.property(i).name();
    }

    for(int i = 0; i < m_vecbtn.size(); ++i)
    {
        QPropertyAnimation * p = new QPropertyAnimation;
        m_mapbtn[m_vecbtn[i]] = p;
        m_pAnimgroup->addAnimation(p);
    }

    SetSkin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetAnimation(QPushButton * pbtn, int xoffset,int yoffset)
{

    QPropertyAnimation * porpAnim = m_mapbtn[pbtn];

    porpAnim->setEasingCurve(QEasingCurve::InCirc);
    porpAnim->setDuration(500);
    porpAnim->setTargetObject(pbtn);
    porpAnim->setPropertyName("geometry");

    QPoint pos = pbtn->pos();
    int posx = pos.x();
    int posy = pos.y();

    porpAnim->setStartValue(QRect(posx,posy,pbtn->width(),pbtn->height()));

//    创建一帧动画   这个设置 qreal step 的意思就是一帧运行所占的时长
//    posx += 20;
//    porpAnim->setKeyValueAt(0.7,QRect(posx,posy,pbtn->width(),pbtn->height()));

    posx += xoffset;
    posy += yoffset;

    porpAnim->setEndValue(QRect(posx,posy,pbtn->width(),pbtn->height()));
}

void MainWindow::SetSkin()
{
    QFile f("./style.qss");
    f.open(QIODevice::ReadOnly);
    QString qstr = f.readAll();
    this->setStyleSheet(qstr);
    f.close();
}



void MainWindow::on_btn_left_clicked()
{
    auto iter = m_mapbtn.begin();
    while(iter != m_mapbtn.end())
    {
        SetAnimation(iter.key(),-100,0);
        iter++;
    }

    m_pAnimgroup->start();
}

void MainWindow::SlotFinished()
{
   for(int i = 0; i < m_vecbtn.size(); ++i)
   {
       QPushButton * pcurbtn = m_vecbtn[i]; //获取按钮指针

       int max_x = ui->widget->width();     //按钮的父窗口的宽就是按钮位置的最大可视范围

       int left_x = pcurbtn->pos().x();          //按钮的左边界坐标
       int right_x = left_x + pcurbtn->width();  //按钮的右边界坐标

       int y = pcurbtn->pos().y();               //按钮的纵坐标

       if(right_x < 0)
       {//按钮右边界已经超出父窗口左边界了

           //判断是不是还有按钮在父窗口右边界外，如果有那么要移动位置到此按钮的后面
           int index = m_vecbtn.indexOf(pcurbtn);

           int index_pre = 0; //前一个按钮的索引
           index_pre = (index <= 0)?(m_vecbtn.size() - 1):(index - 1);


           QPushButton * prebtn = m_vecbtn[index_pre];      //获取当前按钮前一个按钮prebtn

           int posx = prebtn->width() + prebtn->pos().x();  //按钮prebtn右边界的横坐标

           int dvalue = max_x - posx;  //按钮prebtn右边界和父窗口右边界的差值


           //30 这个值指的是按钮之间默认的距离
           if(dvalue > 30)
           {//prebtn按钮在父窗口边界左边且距离大于30
               pcurbtn->move(max_x + right_x,y);  //按钮右边界超出父窗口左边界多少，那么按钮从父窗口右边界探出多少
           }
           else if(dvalue <=  0)
           {//prebtn按钮在父窗口边界右边
               pcurbtn->move(posx + 30,y);
           }
           else
           {//prebtn按钮在父窗口左边且距离左边界小于30
               pcurbtn->move(posx + (30 - dvalue),y);
           }
       }
   }
}

