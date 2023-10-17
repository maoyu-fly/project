#include "usermsgwidgetinfo.h"
#include "ui_usermsgwidgetinfo.h"

usermsgwidgetinfo::usermsgwidgetinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usermsgwidgetinfo)
{
    ui->setupUi(this);
}

usermsgwidgetinfo::~usermsgwidgetinfo()
{
    delete ui;
}
void usermsgwidgetinfo::setHeadImg(const QPixmap &img)//设置图像
{
    ui->message_friendhead_label->setPixmap(img);
    ui->message_friendhead_label->setScaledContents(true);//设置图片为跟随控件大小
}
void usermsgwidgetinfo::setUserid(const QString &chatname)//设置昵称
{
    ui->message_friend_userid_label->setText(chatname);

}
void usermsgwidgetinfo::setMsg(const QString &msg)
{
    ui->message_rsv_label->setText(msg);
}

