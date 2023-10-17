#ifndef FORMSENDSMALLWIDGET_H
#define FORMSENDSMALLWIDGET_H

#include <QWidget>
#include <QDateTime>
namespace Ui {
class Formsendsmallwidget;
}

class Formsendsmallwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Formsendsmallwidget(QWidget *parent = nullptr);
    ~Formsendsmallwidget();
    enum user_type
    {
        user__time,//时间
        user__me,//自己
        user__she,//其它用户
    };


public:
    void setHeadimg(const QPixmap photo);

    void setMessage(const QString msg);

    void setmessageText(QString text,QString time,user_type Type);//设置聊天文本

    inline QString text() {return my_msg;}

    inline QString time() {return my_time;}

    inline user_type userType() {return my_userType;}

public:
    QString my_msg;//消息
    QString my_time;//发送的时间
    QString my_curtime;//当前时间
    user_type my_userType = user__me;

private:
    Ui::Formsendsmallwidget *ui;
};

#endif // FORMSENDSMALLWIDGET_H
