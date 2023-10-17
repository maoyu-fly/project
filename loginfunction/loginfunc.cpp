#include "loginfunc.h"
#include "ui_loginfunc.h"

loginfunc::loginfunc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginfunc)
{
    ui->setupUi(this);
    this->setWindowTitle("注册界面");
    this->setFixedSize(800,476);
    this->setWindowFlags(Qt::Tool);


}

loginfunc::~loginfunc()
{
    delete ui;
}

void loginfunc::on_loginbtn_clicked()
{
    if(ui->chatnameedit->text().isEmpty())
    {

    }
    else if(ui->pwd2edit->text().isEmpty())
    {

    }
    else if(ui->useredit->text().isEmpty())
    {

    }
    else if(ui->pwdedit->text().isEmpty())
    {

    }
    else
    {
        QString username=ui->useredit->text();
        QString chatName=ui->chatnameedit->text();
        QString password=ui->pwdedit->text();
        QSqlQuery query;
        query.prepare("select count(user) from userchat where user= ?");
        query.bindValue(0,username);
        query.exec();
        while(query.next())
        {
            int num=query.value(0).toInt();
            if(num==0)//表示该账号没有被注册，那么就可以注册一条新的信息
            {
                query.prepare("INSERT INTO userchat (user,Pwd,chatname) VALUES (?,?,?)");
                query.bindValue(0, username);
                query.bindValue(1, password);
                query.bindValue(2,chatName);
                query.exec();//执行sql语句
                QMessageBox::information(this,"注册提示","注册成功");

            }
            else//否则，就不能注册
            {
                QMessageBox::information(this,"注册提示","账号已被注册");
            }


        }

    }
}

