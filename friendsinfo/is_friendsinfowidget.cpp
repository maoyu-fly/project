#include "is_friendsinfowidget.h"
#include "ui_is_friendsinfowidget.h"

is_friendsinfowidget::is_friendsinfowidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::is_friendsinfowidget)
{
    ui->setupUi(this);
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//设置去掉标题栏
    this->setWindowFlags(Qt::Popup);
    this->setGeometry(500,150,355,240);
}

is_friendsinfowidget::~is_friendsinfowidget()
{
    delete ui;
}
