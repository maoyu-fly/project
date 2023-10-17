#include "selectgroup.h"
#include "ui_selectgroup.h"

selectGroup::selectGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selectGroup)
{
    ui->setupUi(this);
    this->setFixedSize(750,550);
    this->setWindowFlags(Qt::Tool|Qt::CustomizeWindowHint);





//    this->setWindowFlags(Qt::Tool|Qt::CustomizeWindowHint);
//    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setWindowFlags(Qt::Popup);

    this->setWindowOpacity(0.9);//设置透明度
}

selectGroup::~selectGroup()
{
    delete ui;
}


void selectGroup::on_pushButton_2_clicked()
{

    this->close();
}
void selectGroup::addAListwidget()
{
    personInfo=new groupPseronInfo();
//    personInfo->show();
    QListWidgetItem *item=new QListWidgetItem;
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,personInfo);
}
void selectGroup::settingImg(const QPixmap photo)
{
    personInfo->setimg(photo);
}
void selectGroup::settingname(const QString  name)
{
    personInfo->setname(name);
}

void selectGroup::deleteListInfo(int &i)
{
    QListWidgetItem *item=ui->listWidget->takeItem(i);
    delete item;
}
