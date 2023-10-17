#include "friendinfowidget.h"
#include "ui_friendinfowidget.h"

friendinfowidget::friendinfowidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendinfowidget)
{
    ui->setupUi(this);
}

friendinfowidget::~friendinfowidget()
{
    delete ui;
}
