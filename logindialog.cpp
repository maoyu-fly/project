#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
logindialog::logindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindialog)
{
    ui->setupUi(this);
    ui->imglabel->setFixedSize(35,35);
    this->setFixedSize(540,410);
    this->setWindowTitle("测试版聊天客户端");
    this->setWindowIcon(QIcon("img/chat.png"));
//    chatmainWindow=new chatmainwindow;//实例化；
    this->setWindowFlags(Qt::FramelessWindowHint);//去除标题栏
    ui->usernameedit->addAction(QIcon("img/chat.png"),QLineEdit::LeadingPosition);
    ui->pwdedit->addAction(QIcon("img/padlock.png"),QLineEdit::LeadingPosition);

}

logindialog::~logindialog()
{
    delete ui;
}

void logindialog::on_landbtn_clicked()//单击登录按钮时，显示聊天主界面
{
    if(ui->usernameedit->text().isEmpty())
    {
         QMessageBox::information(this,"登录提示","请输入账号");
    }
    else if(ui->pwdedit->text().isEmpty())
    {
        QMessageBox::information(this,"登录提示","请输入密码");
    }
    else
    {
        QString username=ui->usernameedit->text();
        QString password=ui->pwdedit->text();
        QString qs=QString("select *from userchat where user= '%1' and Pwd = '%2'").arg(username).arg(password);
        QSqlQuery query(qs);//执行sql语句

        if(!query.next())
        {
            QMessageBox::information(this,"登录认证","登录失败,账号或密码错误");
            ui->pwdedit->clear();
            ui->usernameedit->clear();
        }
        else
        {
            QMessageBox::information(this,"登录认证","登录成功");
            QSqlQuery query;
            query.prepare("select * from userchat where user= ?");
            query.bindValue(0,username);
            query.exec();
            while(query.next())
            {
                myname=query.value(2).toString();
                qDebug()<<"myname:"<<query.value(2).toString();
                QByteArray photodata=query.value(3).toByteArray();
                photo1.loadFromData(photodata);

            }
            chatmainWindow=new chatmainwindow();
            chatmainWindow->setWindowTitle(myname);
            chatmainWindow->setUserHeadimg(photo1);
            chatmainWindow->getmainUserid=ui->usernameedit->text();//获取主用户的帐号，返回到主界面中
            chatmainWindow->getcontactmainuserid=ui->usernameedit->text();//获取主用户的帐号，返回到主界面中;
            chatmainWindow->show();//打开主界面
            initchatmaindata();//初始化主界面中contactwidget的数据；
            initMessageData();//初始化主界面中消息人列表框中的数据
            this->close();//登录界面

        }

    }

}


void logindialog::on_loginpushButton_clicked()
{
    loginFunc=new loginfunc;
    loginFunc->show();
}


 void logindialog::initchatmaindata()//初始化，主窗口中contactwidget中的数据
{
    qDebug()<<"测试语句";
    qDebug()<<ui->usernameedit->text();
    QSqlQuery q;
    q.prepare("select friend_user_id from friends where user_id=?");//查询主用户的好友列表
    q.bindValue(0,ui->usernameedit->text());
    q.exec();
    while (q.next())//遍历
    {
        qDebug()<<"测试了"<<q.value(0);
        chatmainWindow->v.append(q.value(0).toString());
        chatmainWindow->addfriendsInfo();
        chatmainWindow->updatafriendsitemData(q.value(0).toString());
        chatmainWindow->addGroupPeople();
        chatmainWindow->updataGroupPeople(q.value(0).toString());

    }

}

//void logindialog::initGroupData(QString userid)
//{

//    QSqlQuery q3;
//    q3.prepare("select *from userchat where user=?");
//    q3.bindValue(0,userid);
//    q3.exec();
//    while (q3.next())
//    {
//        QByteArray photostream=q3.value(3).toByteArray();
//        QPixmap photo;
//        photo.loadFromData(photostream);
//        chatmainWindow->selectGroupWidget->settingImg(photo);
//        chatmainWindow->selectGroupWidget->settingname(q3.value(2).toString());
//    }
//}

void logindialog::mousePressEvent(QMouseEvent *event)//鼠标按下
{
    mousewindowTopLeft1 = event->pos();
}

void logindialog::mouseMoveEvent(QMouseEvent *event)//移动到目的地
{
    //窗口移动
    if (event->buttons() & Qt::LeftButton)
    {
        mouseDeskTopLeft1 = event->globalPos();
        windowDeskTOpLeft1 = mouseDeskTopLeft1 - mousewindowTopLeft1;  //矢量计算
        this->move(windowDeskTOpLeft1);     //移动到目的地
    }
}


void logindialog::on_pushButton_2_clicked()//关闭窗口
{
    this->close();//关闭窗口
}


void logindialog::on_pushButton_clicked()//最小化
{
    this->showMinimized();//最小化
}

void logindialog::initMessageData()//初始化消息联系人列表中的数据
{
    QSqlQuery q1;
    q1.prepare("select MessageFriends from usermessagefriends where Mainuser=?");
    q1.bindValue(0,ui->usernameedit->text());
    q1.exec();
    while(q1.next())//遍历
    {
        chatmainWindow->messageV.append(q1.value(0).toString());
        chatmainWindow->initaddmessageNumber(q1.value(0).toString());

    }

}

