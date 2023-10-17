#ifndef USERMSGWIDGETINFO_H
#define USERMSGWIDGETINFO_H

#include <QWidget>

namespace Ui {
class usermsgwidgetinfo;
}

class usermsgwidgetinfo : public QWidget
{
    Q_OBJECT

public:
    explicit usermsgwidgetinfo(QWidget *parent = nullptr);
    ~usermsgwidgetinfo();

public:
    void setHeadImg(const QPixmap &img);//设置图像
    void setUserid(const QString &chatname);//设置昵称
    void setMsg(const QString &msg);

private:
    Ui::usermsgwidgetinfo *ui;
};

#endif // USERMSGWIDGETINFO_H
