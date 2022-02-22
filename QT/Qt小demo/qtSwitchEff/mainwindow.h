#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QString>
#include <QPoint>


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
    void on_btn_up_clicked();

    void on_btn_down_clicked();

    void on_btn_left_clicked();

    void on_btn_right_clicked();

private:
    Ui::MainWindow *ui;
    QPropertyAnimation * m_panimation;
    void DealAnimation(int pox,int poxy);

};
#endif // MAINWINDOW_H
