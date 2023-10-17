#ifndef FRIENDSITEM_H
#define FRIENDSITEM_H

#include <QWidget>

namespace Ui {
class friendsitem;
}

class friendsitem : public QWidget
{
    Q_OBJECT

public:
    explicit friendsitem(QWidget *parent = nullptr);
    ~friendsitem();

public:
    Ui::friendsitem *ui;
};

#endif // FRIENDSITEM_H
