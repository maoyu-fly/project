#ifndef GROUPPSERONINFO_H
#define GROUPPSERONINFO_H

#include <QWidget>

namespace Ui {
class groupPseronInfo;
}

class groupPseronInfo : public QWidget
{
    Q_OBJECT

public:
    explicit groupPseronInfo(QWidget *parent = nullptr);
    ~groupPseronInfo();
    bool status;
    void setimg(const QPixmap &photo);//设置图片
    void setname(const QString &Name);//设置昵称

private slots:
    void on_pushButton_clicked();

private:
    Ui::groupPseronInfo *ui;
};

#endif // GROUPPSERONINFO_H
