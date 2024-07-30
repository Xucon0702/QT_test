#include "tcpclient.h"
#include <QMessageBox>
#include <QHostInfo>

TcpClient::TcpClient(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle(tr("TCP Client"));

    contentListWidget = new QListWidget;

    sendLineEdit = new QLineEdit;
    sendBtn = new QPushButton(tr("发送"));

    userNameLabel = new QLabel(tr("用户名："));
    userNameLineEdit = new QLineEdit;

    serverIPLabel = new QLabel(tr("服务器地址："));
    serverIPLineEdit = new QLineEdit;

    portLabel = new QLabel(tr("端口："));
    portLineEdit = new QLineEdit;

    enterBtn= new QPushButton(tr("开始连接"));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(contentListWidget,0,0,1,2);
    mainLayout->addWidget(sendLineEdit,1,0);
    mainLayout->addWidget(sendBtn,1,1);
    mainLayout->addWidget(userNameLabel,2,0);
    mainLayout->addWidget(userNameLineEdit,2,1);
    mainLayout->addWidget(serverIPLabel,3,0);
    mainLayout->addWidget(serverIPLineEdit,3,1);
    mainLayout->addWidget(portLabel,4,0);
    mainLayout->addWidget(portLineEdit,4,1);
    mainLayout->addWidget(enterBtn,5,0,1,2);

    status = false;

    port = 8010;
    portLineEdit->setText(QString::number(port));

    serverIP =new QHostAddress();

    connect(enterBtn,SIGNAL(clicked()),this,SLOT(slotEnter()));
    connect(sendBtn,SIGNAL(clicked()),this,SLOT(slotSend()));

    sendBtn->setEnabled(false);

}







TcpClient::~TcpClient()
{

}

void TcpClient::slotEnter()
{
    if(!status)
    {
        QString ip = serverIPLineEdit->text();  //获取输入的ip
        if(!serverIP->setAddress(ip))           //判断IP是否设置成功
        {
            QMessageBox::information(this,tr("error"),tr("server ip address error!"));
            return;
        }

        if(userNameLineEdit->text()=="")        //判断用户名是否为空
        {
            QMessageBox::information(this,tr("error"),tr("User name error!"));
            return;
        }

        userName=userNameLineEdit->text();

        tcpSocket = new QTcpSocket(this);    //创建tcp的socket

        connect(tcpSocket,SIGNAL(connected()), //绑定接口:tcp连接成功时调用slotConnected
                this,SLOT(slotConnected()));

        connect(tcpSocket,SIGNAL(disconnected()), //绑定接口:tcp连接断开时调用slotDisconnected
                this,SLOT(slotDisconnected()));

        connect(tcpSocket,SIGNAL(readyRead()),      //绑定接口:tcp收到数据时调用dataReceived
                this,SLOT(dataReceived()));

        tcpSocket->connectToHost(*serverIP,port);       //连接服务端

        status=true;                                    //连接后改变连接状态，防止重复连接
    }
    else
    {
        int length=0;
        QString msg=userName+tr(":Leave Chat Room");
        if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg. length())
        {
            return;
        }

        tcpSocket->disconnectFromHost();

        status=false;
    }
}

void TcpClient::slotConnected()
{
    sendBtn->setEnabled(true);
    enterBtn->setText(tr("离开"));

    int length=0;
    QString msg=userName+tr(":Enter Chat Room");
    if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())  //实际发送的数据和msg原本长度不同的话 return --> 可以报错
    {
        return;
    }
}

void TcpClient::slotSend()
{
    if(sendLineEdit->text()=="")
    {
        return ;
    }

    QString msg=userName+":"+sendLineEdit->text();

    tcpSocket->write(msg.toLatin1(),msg.length()); //发送数据
    sendLineEdit->clear();  //清除发送的数据框
}

void TcpClient::slotDisconnected()
{
    sendBtn->setEnabled(false);
    enterBtn->setText(tr("进入聊天室"));

    //关闭tcp连接
    tcpSocket->disconnectFromHost();
    contentListWidget->clear();   //断连后清除界面信息

    status=false;
}

void TcpClient::dataReceived()
{
    while(tcpSocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());

        tcpSocket->read(datagram.data(),datagram.size());

        QString msg=datagram.data();
        contentListWidget->addItem(msg.left(datagram.size()));  //添加输入的信息显示
    }
}
