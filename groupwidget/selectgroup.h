#ifndef SELECTGROUP_H
#define SELECTGROUP_H

#include <QWidget>
#include <QMouseEvent>
#include <QListWidget>
#include <groupwidget/grouppseroninfo.h>
#include <QWindow>
namespace Ui {
class selectGroup;
}

class selectGroup : public QWidget
{
    Q_OBJECT

public:
    explicit selectGroup(QWidget *parent = nullptr);
    ~selectGroup();


public:
    groupPseronInfo *personInfo;
    void addAListwidget();
    void settingImg(const QPixmap photo);
    void settingname(const QString name);
    void deleteListInfo(int &i);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::selectGroup *ui;
};

#endif // SELECTGROUP_H
