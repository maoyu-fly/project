#include "widget.h"
#include "initdatabase.h"
#include <QApplication>
#include <logindialog.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initdatabase database;
    database.initDatabase();
    logindialog login1;
    login1.show();

//    Widget w;

//    w.show();
    return a.exec();
}
