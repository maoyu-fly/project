#include "initdatabase.h"

initdatabase::initdatabase(QWidget *parent)
    : QWidget{parent}
{

}
void initdatabase::initDatabase()
{

    QSqlDatabase dbs=QSqlDatabase::addDatabase("QMYSQL");
    dbs.setHostName("localhost");
    dbs.setDatabaseName("mychat");
    dbs.setUserName("root");
    dbs.setPassword("maoyu520");
    dbs.open();//启动数据库

}
