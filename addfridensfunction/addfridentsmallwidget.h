#ifndef ADDFRIDENTSMALLWIDGET_H
#define ADDFRIDENTSMALLWIDGET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QSqlQuery>
#include <QDebug>
namespace Ui {
class addfridentsmallwidget;
}

class addfridentsmallwidget : public QWidget
{
    Q_OBJECT

public:
    explicit addfridentsmallwidget(QWidget *parent = nullptr);
    ~addfridentsmallwidget();

//public:
//    QString getUserid;//获取用户的账号
//    QString getfriendid;//获取好友的账号


protected:
    bool event(QEvent * e);


public:
    Ui::addfridentsmallwidget *ui;


//private slots:
//    void on_addfriden_btn_clicked();
};

#endif // ADDFRIDENTSMALLWIDGET_H
