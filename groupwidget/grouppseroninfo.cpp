#include "grouppseroninfo.h"
#include "ui_grouppseroninfo.h"

groupPseronInfo::groupPseronInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupPseronInfo)
{
    ui->setupUi(this);
    status=true;
}

groupPseronInfo::~groupPseronInfo()
{
    delete ui;
}

void groupPseronInfo::setimg(const QPixmap &photo)//设置图片
{
    ui->imglabel->setPixmap(photo);
    ui->imglabel->setScaledContents(true);
}
void groupPseronInfo::setname(const QString &Name)//设置昵称
{
    ui->namelabel->setText(Name);
}

void groupPseronInfo::on_pushButton_clicked()
{
    if(status)
    {
        ui->pushButton->setIcon(QIcon("img/select.svg"));
        status=false;
    }
    else
    {
        ui->pushButton->setIcon(QIcon("img/select2.svg"));
        status=true;
    }


}

