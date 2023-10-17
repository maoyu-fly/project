#include "friendsitem.h"
#include "ui_friendsitem.h"

friendsitem::friendsitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendsitem)
{
    ui->setupUi(this);
}

friendsitem::~friendsitem()
{
    delete ui;
}
