#ifndef FRIENDINFOWIDGET_H
#define FRIENDINFOWIDGET_H

#include <QWidget>

namespace Ui {
class friendinfowidget;
}

class friendinfowidget : public QWidget
{
    Q_OBJECT

public:
    explicit friendinfowidget(QWidget *parent = nullptr);
    ~friendinfowidget();

public:
    Ui::friendinfowidget *ui;
};

#endif // FRIENDINFOWIDGET_H
