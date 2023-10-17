#ifndef MYSELFINFOWIDGET_H
#define MYSELFINFOWIDGET_H

#include <QWidget>

namespace Ui {
class myselfinfoWidget;
}

class myselfinfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit myselfinfoWidget(QWidget *parent = nullptr);
    ~myselfinfoWidget();

public:
    Ui::myselfinfoWidget *ui;
};

#endif // MYSELFINFOWIDGET_H
