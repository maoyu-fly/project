#ifndef LOGINFUNC_H
#define LOGINFUNC_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class loginfunc;
}

class loginfunc : public QWidget
{
    Q_OBJECT

public:
    explicit loginfunc(QWidget *parent = nullptr);
    ~loginfunc();

private slots:
    void on_loginbtn_clicked();


private:
    Ui::loginfunc *ui;
};

#endif // LOGINFUNC_H
