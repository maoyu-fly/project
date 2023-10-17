#include "myselfinfowidget.h"
#include "ui_myselfinfowidget.h"

myselfinfoWidget::myselfinfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myselfinfoWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::Popup);

}

myselfinfoWidget::~myselfinfoWidget()
{
    delete ui;
}
