#ifndef INITDATABASE_H
#define INITDATABASE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
class initdatabase : public QWidget
{
    Q_OBJECT
public:
    explicit initdatabase(QWidget *parent = nullptr);
public:
    void initDatabase();

signals:

};

#endif // INITDATABASE_H
