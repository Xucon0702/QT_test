#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(0, 0, 1000,600); //界面分辨率

        //实例化两个按钮对象，并设置其显示文本为窗口皮肤 1 和窗口皮肤 2
//        pushBtn1 = new QPushButton("窗口皮肤 1", this);
//        pushBtn2 = new QPushButton("窗口皮肤 2", this);
        pushBtn1 = new QPushButton("按键1", this); //设置按键名称
        pushBtn2 = new QPushButton("按键2", this);

        //设定两个 QPushButton 对象的位置
        pushBtn1->setGeometry(0,5,80,40);
        pushBtn2->setGeometry(100,5,80,40);

        //信号槽连接,绑定按键和处理函数
        connect(pushBtn1, SIGNAL(clicked()), this, SLOT(pushBtn1_click()));
        connect(pushBtn2, SIGNAL(clicked()), this, SLOT(pushBtn2_click()));
    ui->tcpClient.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushBtn1_click()
{
    // 应用第一张图片作为背景皮肤，调整大小以铺满窗口
//    this->setStyleSheet("QMainWindow {background-image: url(/home/qinlong/Qt/04_buttons_example/picture/a8.jpg); background-position: center; background-repeat: no-repeat; background-size: cover;}");
}

void MainWindow::pushBtn2_click()
{
    // 应用第二张图片作为背景皮肤，调整大小以铺满窗口
//    this->setStyleSheet("QMainWindow {background-image: url(/home/qinlong/Qt/04_buttons_example/picture/r8.jpg); background-position: center; background-repeat: no-repeat; background-size: cover;}");
}

//在UI上直接添加的按键，通过右键转到槽跳转过来的；每次改名的时候要删除之前的接口;
//按钮的点击响应函数：on_按钮名_信号名;这种方式不用调用connect函数显示指定
void MainWindow::on_showBtn_clicked()
{
     qDebug("show clicked");
     QMessageBox::information(this, "title", "on_myRadioButton_clicked");

     QMessageBox message(QMessageBox::NoIcon, "Show Qt", "Do you want to show Qt dialog?", QMessageBox::Yes | QMessageBox::No, NULL);
     if(message.exec() == QMessageBox::Yes) //用户选择判定执行对应操作
     {
             QMessageBox::aboutQt(NULL, "About Qt");
     }

    ui->label->setText("Hello, world!");
    ui->label_2->setText("this is two!");

}


