#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->resize(this->centralWidget()->size());
    //label->setPixmap(this->centralWidget()->grab());
    ui->pushButton->show();

    m_panimation = new QPropertyAnimation(ui->pushButton,"geometry");
    m_panimation->setDuration(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::DealAnimation(int pox,int poxy)
{
    QPoint pos = ui->pushButton->pos();
    m_panimation->setStartValue(QRect(pos.x(),pos.y(),75,23));

    int width = ui->edt_width->text().toInt();
    int high  = ui->edt_high->text().toInt();
    m_panimation->setEndValue(QRect(pox,poxy,width,high));
    m_panimation->start();
}


void MainWindow::on_btn_up_clicked()
{
    int movelong = ui->edt_long->text().toInt();

    QPoint pos = ui->pushButton->pos();
    int x = pos.x();
    int y = pos.y() - movelong;
    DealAnimation(x,y);
}

void MainWindow::on_btn_down_clicked()
{
    int movelong = ui->edt_long->text().toInt();

    QPoint pos = ui->pushButton->pos();
    int x = pos.x();
    int y = pos.y() + movelong;
    DealAnimation(x,y);
}

void MainWindow::on_btn_left_clicked()
{
    int movelong = ui->edt_long->text().toInt();

    QPoint pos = ui->pushButton->pos();
    int x = pos.x() -  movelong;;
    int y = pos.y();
    DealAnimation(x,y);
}

void MainWindow::on_btn_right_clicked()
{
    int movelong = ui->edt_long->text().toInt();

    QPoint pos = ui->pushButton->pos();
    int x = pos.x() +  movelong;;
    int y = pos.y();
    DealAnimation(x,y);
}
