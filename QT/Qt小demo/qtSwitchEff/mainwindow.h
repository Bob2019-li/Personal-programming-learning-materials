#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QString>
#include <QPoint>
#include <QEvent>
#include <QDebug>
#include <QVector>
#include <QPushButton>
#include <QMap>
#include <QHBoxLayout>
#include <QParallelAnimationGroup>
#include <QFile>
#include <QMetaProperty>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_left_clicked();
    void SlotFinished();
private:
    Ui::MainWindow *ui;
    QMap<QPushButton *,QPropertyAnimation *> m_mapbtn;
    QParallelAnimationGroup * m_pAnimgroup;
    QVector<QPushButton *> m_vecbtn;


    void SetAnimation(QPushButton * pbtn, int xoffset,int yoffset);
    void SetSkin();

};
#endif // MAINWINDOW_H
