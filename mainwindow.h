#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void BtnShow(void);

private:    
    //添加按键
    QPushButton * pushBtn1;
    QPushButton * pushBtn2;

    TcpClient tcpClient;

private slots:
    //按键处理函数
    void pushBtn1_click();
    void pushBtn2_click();

    void on_showBtn_clicked();
};
#endif // MAINWINDOW_H
