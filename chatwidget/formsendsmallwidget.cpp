#include "formsendsmallwidget.h"
#include "ui_formsendsmallwidget.h"

Formsendsmallwidget::Formsendsmallwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formsendsmallwidget)
{
    ui->setupUi(this);
}
void Formsendsmallwidget::setHeadimg(const QPixmap photo)
{
    ui->headlabel->setPixmap(photo);
    ui->headlabel->setScaledContents(true);
}
void Formsendsmallwidget::setMessage(const QString msg)
{
    ui->msglabel_2->setText(msg);
    ui->msglabel_2->setTextInteractionFlags(Qt::TextSelectableByMouse);

}
void Formsendsmallwidget::setmessageText(QString text,QString time,user_type Type)//设置聊天文本
{

    my_msg=text;//消息
     setMessage(my_msg);
    my_time=time;//时间
    my_curtime=QDateTime::fromTime_t(time.toInt()).toString("hh:mm");//当前时间
    my_userType=Type;//类型
    this->update();

}
Formsendsmallwidget::~Formsendsmallwidget()
{
    delete ui;
}
