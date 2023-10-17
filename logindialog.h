#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <chatmainwindow.h>
#include <QMessageBox>
#include <QSqlQuery>
#include "chatmainwindow.h"
#include "loginfunction/loginfunc.h"//注册界面头文件
#include <QPoint>
namespace Ui {
class logindialog;
}

class logindialog : public QDialog
{
    Q_OBJECT

public:
    explicit logindialog(QWidget *parent = nullptr);
    ~logindialog();
public:
    chatmainwindow *chatmainWindow;//主界面
    loginfunc *loginFunc;//注册界面
    QString myname;
    void initchatmaindata();//初始化主界面中联系人列表中的数据
    void initMessageData();//初始化主界面中消息人列表中的数据
    void initGroupData(QString userid);
    QPixmap photo1;

    QPoint mousewindowTopLeft1;
    QPoint mouseDeskTopLeft1;
    QPoint windowDeskTOpLeft1;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);


private slots:
    void on_landbtn_clicked();

    void on_loginpushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


private:
    Ui::logindialog *ui;

};

#endif // LOGINDIALOG_H
