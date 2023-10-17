#include "addfridentsmallwidget.h"
#include "ui_addfridentsmallwidget.h"

addfridentsmallwidget::addfridentsmallwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addfridentsmallwidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//设置去掉标题栏


}

addfridentsmallwidget::~addfridentsmallwidget()
{
    delete ui;
}


bool addfridentsmallwidget::event(QEvent * e)
{
    if (QEvent::Show == e->type())
    {
        activateWindow();
    }
    else if (QEvent::WindowDeactivate == e->type())
    {
        this->close();
    }
    return QWidget::event(e);
}

//void addfridentsmallwidget::on_addfriden_btn_clicked()
//{
//    QSqlQuery query;
//    QString friendid=getfriendid;//获取好友的账号
//    QString mainid=getUserid;//获取主用户的账号
//    qDebug()<<"addfridentsmallwidget::"<<friendid;
//    qDebug()<<"addfridentsmallwidget::"<<mainid;
//    query.prepare("insert into friends(user_id,friend_user_id) values(?,?)");
//    query.bindValue(0,mainid);//向数据库friends表中插入主用户的账号
//    query.bindValue(1,friendid);//向数据库friends表中插入好友的账号
//    query.exec();//执行
//}

