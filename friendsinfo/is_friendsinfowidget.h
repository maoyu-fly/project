#ifndef IS_FRIENDSINFOWIDGET_H
#define IS_FRIENDSINFOWIDGET_H

#include <QWidget>

namespace Ui {
class is_friendsinfowidget;
}

class is_friendsinfowidget : public QWidget
{
    Q_OBJECT

public:
    explicit is_friendsinfowidget(QWidget *parent = nullptr);
    ~is_friendsinfowidget();


public:
    Ui::is_friendsinfowidget *ui;
};

#endif // IS_FRIENDSINFOWIDGET_H
