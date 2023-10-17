#include "chatmainwindow.h"
#include "ui_chatmainwindow.h"
#include "ui_is_friendsinfowidget.h"
chatmainwindow::chatmainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatmainwindow)
{


    ui->setupUi(this);
    this->setWindowIcon(QIcon("img/chat.png"));

    this->setFixedSize(1350,800);//固定窗口大小
    intiUdp();
    this->setWindowFlags(Qt::FramelessWindowHint);          //去掉标题栏无边框
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    shadow->setOffset(0, 0);
    //设置阴影颜色
    shadow->setColor(QColor(39,40,43,100));
    //设置阴影圆角
    shadow->setBlurRadius(10);
    //给嵌套QWidget设置阴影
    ui->widget->setGraphicsEffect(shadow);

    //初始化控件
    ui->rsvMessagelistWidget->setFocusPolicy(Qt::NoFocus);//设置没有虚框线
    ui->rsvMessagelistWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//设置关闭水平滑块
    is_topwindow=true;//置顶状态
    ui->stackedWidget->setCurrentIndex(0);
    ui->rstackedWidget->setCurrentIndex(4);
    ui->searchsmallwidget->close();//初始化搜索窗口为关闭状态
    addFridentSmallWidget=new addfridentsmallwidget;//实例化添加好友的窗口
    Is_Friendsinfo=new is_friendsinfowidget;//实例化好友信息窗口
    selectGroupWidget=new selectGroup;//实例化
    connect(addFridentSmallWidget->ui->addfriden_btn,SIGNAL(clicked(bool)),this,SLOT(on_addfriend()));//添加好友窗口的添加按钮单击后执行on_addfriend函数

    ui->contactlistWidget->setContextMenuPolicy(Qt::CustomContextMenu);//设置右击可以有菜单
    ui->message_listWidget->setContextMenuPolicy(Qt::CustomContextMenu);//设置右击可以有菜单

    //在搜索编辑框中添加动作
    ui->searchlineEdit->addAction(QIcon("img/contact.svg"),QLineEdit::LeadingPosition);//在编辑框头部添加图片
    ui->searchlineEdit->setClearButtonEnabled(true);
    ui->searchlineEdit->setCursorMoveStyle(Qt::VisualMoveStyle);//在编辑框尾部添加取消按钮




}


chatmainwindow::~chatmainwindow()
{
    delete ui;
}

void chatmainwindow::intiUdp()
{
    userUdpsocket=new QUdpSocket(this);
    port=6667;//目标端口
    userUdpsocket->bind(8888);//绑定端口
    connect(userUdpsocket,&QUdpSocket::readyRead,this,&chatmainwindow::userReceiveMessage);
}

void chatmainwindow::userReceiveMessage()//处理用户接受的信息
{
    while(userUdpsocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(userUdpsocket->pendingDatagramSize());

        userUdpsocket->readDatagram(datagram.data(),datagram.size());//读取数据

        QString msg=datagram.data();//接受的消息

        QString altermsg=msg.toUtf8();

        UserMessageWidget->setMsg(altermsg);

        // 获取当前时间戳
        QString time = QString::number(QDateTime::currentDateTime().toTime_t());

        // 处理消息时间戳显示
        dealMessageTime(time);

        // 创建新消息窗口
        MychatMessage* messageW = new MychatMessage(ui->rsvMessagelistWidget->parentWidget());

        // 创建新列表项
        QListWidgetItem* item = new QListWidgetItem(ui->rsvMessagelistWidget);

        //处理消息显示和数据
        dealMessage(messageW, item, altermsg, time, MychatMessage::User_She);//用户类型为主用户

        // 滚动到最后一条消息
        ui->rsvMessagelistWidget->setCurrentRow(ui->rsvMessagelistWidget->count() - 1);


    }
}

QString chatmainwindow::getHostip()//获取本端的IP地址
{
    QList<QHostAddress> addrlist=QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, addrlist)
    {
        if(addr.protocol()==QAbstractSocket::IPv4Protocol)
        {
            return addr.toString();
        }
    }
    return 0;

}
QString chatmainwindow::getLocChatMsg()//获取本端的聊天信息内容
{

    QString chatmsg=ui->textEdit->toHtml();
    ui->textEdit->clear();
    ui->textEdit->setFocus();
    return chatmsg;

}

void chatmainwindow::on_sendbtn_clicked()//发送信息
{
    // 获取消息文本
    QString msg = ui->textEdit->toPlainText();
    UserMessageWidget->setMsg(msg);
    userUdpsocket->writeDatagram(msg.toUtf8(),QHostAddress("127.0.0.1"),port);//向目标地址和端口发送数据
    // 清除文本框
    ui->textEdit->setText("");
    // 获取当前时间戳
    QString time = QString::number(QDateTime::currentDateTime().toTime_t());

    // 调试信息
    qDebug() << "addMessage" << msg << time << ui->rsvMessagelistWidget->count();

    // 处理消息时间戳显示
    dealMessageTime(time);

    // 创建新消息窗口
    MychatMessage* messageW = new MychatMessage(ui->rsvMessagelistWidget->parentWidget());

    //设置消息窗口的主用户头像
    QSqlQuery query;
    query.prepare("select *from userchat where user=?");
    query.bindValue(0,getmainUserid);
    query.exec();//执行
    while(query.next())
    {
        QByteArray dataphoto1=query.value(3).toByteArray();
        QPixmap photo;
        photo.loadFromData(dataphoto1);
        messageW->setRightPixmap(photo);
    }

    // 创建新列表项
    QListWidgetItem* item = new QListWidgetItem(ui->rsvMessagelistWidget);

    // 处理消息显示和数据
    dealMessage(messageW, item, msg, time, MychatMessage::User_Me);//用户类型为主用户

    // 滚动到最后一条消息
    ui->rsvMessagelistWidget->setCurrentRow(ui->rsvMessagelistWidget->count() - 1);

}

void chatmainwindow::on_transbtn_clicked()
{

}

void chatmainwindow::on_pushButton_clicked()
{
    selectGroupWidget->setGeometry(this->pos().x()+300,this->pos().y()+130,750,550);
    selectGroupWidget->show();
}


void chatmainwindow::on_contactBtn_clicked()//联系人按钮
{

    ui->msgbtn->setIcon(QIcon("img/chat.svg"));
    ui->contactBtn->setIcon(QIcon("img/contact2.svg"));
    ui->collectBtn->setIcon(QIcon("img/collect.svg"));
    ui->stackedWidget->setCurrentIndex(1);
//    ui->funclabel->setText("企业微信通知");
    ui->rstackedWidget->setCurrentIndex(4);


}


void chatmainwindow::on_collectBtn_clicked()//收藏按钮
{
    ui->collectBtn->setIcon(QIcon("img/collect2.svg"));
    ui->contactBtn->setIcon(QIcon("img/contact.svg"));
    ui->stackedWidget->setCurrentIndex(2);
    ui->rstackedWidget->setCurrentIndex(4);
}


void chatmainwindow::on_msgbtn_clicked()//消息按钮
{
    ui->msgbtn->setIcon(QIcon("img/chat2.svg"));
    ui->contactBtn->setIcon(QIcon("img/contact.svg"));
    ui->collectBtn->setIcon(QIcon("img/collect.svg"));
    ui->stackedWidget->setCurrentIndex(0);
    ui->rstackedWidget->setCurrentIndex(4);


}
void chatmainwindow::mousePressEvent(QMouseEvent *event)
{
    mouseWindowTopLeft = event->pos();
}

void chatmainwindow::mouseMoveEvent(QMouseEvent *event)
{
    //窗口移动
    if (event->buttons() & Qt::LeftButton)
    {
        mouseDeskTopLeft = event->globalPos();
        windowDeskTopLeft = mouseDeskTopLeft - mouseWindowTopLeft;  //矢量计算
        this->move(windowDeskTopLeft);     //移动到目的地
    }
}


void chatmainwindow::on_closewindowbtn_clicked()//关闭窗口
{
    this->close();
}


void chatmainwindow::on_minwindowbtn_clicked()//最小化窗口
{
    this->showMinimized();
}

void chatmainwindow::on_maxwindowbtn_clicked()//最大化窗口
{
    this->showFullScreen();//全屏
}

void chatmainwindow::on_topwindowbtn_clicked()//置顶按钮图片切换
{
    if(is_topwindow==true)
    {
        ui->topwindowbtn->setIcon(QIcon("img/sticky2.svg"));
        is_topwindow=false;
    }
    else
    {
        ui->topwindowbtn->setIcon(QIcon("img/sticky.svg"));
        is_topwindow=true;
    }
}

void chatmainwindow::on_folderBtn_clicked()//文件功能
{
    ui->stackedWidget->setCurrentIndex(3);
}


void chatmainwindow::on_addbtn_clicked()//添加联系人
{
    ui->stackedWidget->setCurrentIndex(5);
}


void chatmainwindow::on_searchcancelbtn_clicked()//取消编辑按钮
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->searchsmallwidget->close();
}

void chatmainwindow::on_searchlineEdit_textEdited()//当添加联系人编辑框编辑时
{

    if(ui->searchlineEdit->text().isEmpty())
     {
        ui->whether_sear_stackedWidget->setCurrentIndex(0);
        ui->searchsmallwidget->close();
     }
    else
    {
        ui->whether_sear_stackedWidget->setCurrentIndex(0);
        ui->searchsmallwidget->show();
        QString searuser=ui->searchlineEdit->text();
        ui->searrecordedit->setText(searuser);
    }
}


void chatmainwindow::on_searbtn_clicked()//单击搜索按钮
{
    qDebug()<<"再次测试数据传输是否成功"<<v.isEmpty();//如果不为空表示，list容器传输数据成功

    //先设置一个查询，查询所输入的账号是否存在与好友中
    bool is_or_no_status=true;
    QSqlQuery query1;
    query1.prepare("select friend_user_id from friends where user_id=?");//查询主用户的好友列表中是否有该好友
    query1.bindValue(0,getmainUserid);                            //绑定值
    query1.exec();                                                //执行该sql语句
    qDebug()<<"输入的搜索栏中的账号："<<ui->searchlineEdit->text();
    while(query1.next())
    {

        qDebug()<<"记录1："<<query1.value(0).toString();
        if(ui->searchlineEdit->text()==query1.value(0).toString())//如果需要查找的人在记录中，那么就代表属于好友,然后暂停循环
        {
            is_or_no_status=true;break;
        }
        else                                                       //反之如果不在好友列表中，就代表还没有添加
        {
            is_or_no_status=false;
        }
    }

    qDebug()<<"this is test:"<<is_or_no_status;//测试代码，测试是否为好友的状态

    if(ui->searchlineEdit->text()==getmainUserid)//用户为自己
    {
        updataMyselfinfoWidget();//更新个人信息窗体中的控件
    }
    else if(query1.value(0).isNull())//如果说搜索的值在friends列表中不存在，那么就有两种情况出现，第一种情况是搜索的用户注册过，第二种情况是搜索的用户还没有注册，也就是不存在
    {
        QString search_user=ui->searchlineEdit->text();
        QSqlQuery query;
        query.prepare("select count(user) from userchat where user= ?");
        query.bindValue(0,search_user);
        query.exec();//执行
        while(query.next())//遍历查询结果
        {
            qDebug()<<"再一次测试执行query的值为"<<query.value(0).toInt();
                if(query.value(0).toInt()==0)//表示没有查询到，数据库中没有该用户，表示输入的用户还没有注册
            {
                ui->whether_sear_stackedWidget->setCurrentIndex(1);
            }
            else//表示查询到该用户
            {

                QSqlQuery query;
                query.prepare("select * from userchat where user= ?");
                query.bindValue(0,search_user);
                query.exec();//执行
                while(query.next())//遍历查询结果
                {
                    QString addFridentSmallWidgetname_label=query.value(2).toString();

                    QByteArray imagedata=query.value(3).toByteArray();
                    QPixmap photo;
                    photo.loadFromData(imagedata);
                    addFridentSmallWidget->ui->chatname_label->setText(addFridentSmallWidgetname_label);
                    addFridentSmallWidget->ui->head_label->setPixmap(photo);
                    addFridentSmallWidget->ui->head_label->setScaledContents(true);

                }
                addFridentSmallWidget->setGeometry(this->pos().x()+200,this->pos().y()+40,355,240);
                addFridentSmallWidget->show();
//                connect(addFridentSmallWidget->ui->addfriden_btn,SIGNAL(clicked(bool)),this,SLOT(on_addfriend()));//添加好友窗口连接添加联系人函数
            }
        }
    }
    else if(is_or_no_status==true)//如果说，需要添加的好友已在数据库表friends的记录中
    {
        qDebug()<<"执行到这里";
        updatafriendsWidgetInfo();//更新好友窗口中的控件
    }
    else
    {

    }

}


void chatmainwindow::on_addfriend()//添加联系人按钮
{

    QSqlQuery query;
    QString friendid=ui->searchlineEdit->text();//获取好友的账号
    QString mainid=getmainUserid;//获取主用户的账号
    qDebug()<<friendid;
    qDebug()<<mainid;
    saveFriendInfo(friendid);
    query.prepare("insert into friends(user_id,friend_user_id) values(?,?)");
    query.bindValue(0,mainid);//向数据库friends表中插入主用户的账号
    query.bindValue(1,friendid);//向数据库friends表中插入好友的账号
    query.exec();//执行
    //在联系人列表中添加一条记录
    addfriendsInfo();
    //更新联系人列表中的控件
    updatafriendsitemData(friendid);


    addGroupPeople();
    updataGroupPeople(friendid);


    ui->searchlineEdit->clear();
    ui->searrecordedit->clear();
    addFridentSmallWidget->close();
}

void chatmainwindow::addfriendsInfo()//好友列表中新增一条记录
{
    QListWidgetItem *item=new QListWidgetItem;
    Friendsitem=new friendsitem(this);
    Friendsitem->show();
    ui->contactlistWidget->addItem(item);
    ui->contactlistWidget->setItemWidget(item,Friendsitem);
}

void chatmainwindow::updatafriendsitemData(QString frid)//更新好友列表中的控件
{
    QSqlQuery query;
    query.prepare("select * from userchat where user = ?");
    query.bindValue(0,frid);
    query.exec();
    while(query.next())
    {
        Friendsitem->ui->friend_chatname_label->setText(query.value(2).toString());
        QPixmap photo_3;
        QByteArray imagedata=query.value(3).toByteArray();
        photo_3.loadFromData(imagedata);
        Friendsitem->ui->friendhead_label->setPixmap(photo_3);
        Friendsitem->ui->friendhead_label->setScaledContents(true);
    }
}

void chatmainwindow::updatafriendsWidgetInfo()//更新已是好友窗口中的信息
{
    Is_Friendsinfo->setGeometry(this->pos().x()+200,this->pos().y()+40,355,440);
    Is_Friendsinfo->show();
    QSqlQuery query;
    query.prepare("select * from userchat where user = ?");
    query.bindValue(0,ui->searchlineEdit->text());
    query.exec();
    while(query.next())
    {
        Is_Friendsinfo->ui->friendsinfowidget_user_label->setText(query.value(0).toString());//显示该好友的账号
        Is_Friendsinfo->ui->friendsinfowidget_chatname_label->setText(query.value(2).toString());//显示该好友的昵称
        QPixmap photo_1;

        QByteArray imagedata2=query.value(3).toByteArray();
        photo_1.loadFromData(imagedata2);
        Is_Friendsinfo->ui->friendsinfowidget_head_label->setPixmap(photo_1);//显示该好友的头像
        Friendsitem->ui->friendhead_label->setScaledContents(true);
    }
}


void chatmainwindow::on_contactlistWidget_customContextMenuRequested(const QPoint &pos)//处理联系人列表鼠标右键事件，弹出菜单
{
//    QListWidgetItem *items6=ui->contactlistWidget->currentItem();//获取当前选中的item
//    QList<QListWidgetItem*> items6 = ui->contactlistWidget->selectedItems();
//    qDebug()<<"item的数量为："<<items6.count();
    QPoint gobalpos=ui->contactlistWidget->mapToGlobal(pos);
    popMenu_in_contactListWidget=new QMenu;
    action_delete=new QAction(QIcon("img/delete.png"),tr("删除"));
    action_sendcard=new QAction(QIcon("img/id-card.png"),tr("发送名片"));
    action_tab=new QAction(QIcon("img/star.png"),tr("标记"));
    action_msg=new QAction(QIcon("img/send.png"),tr("发送消息"));
    QListWidgetItem* item=ui->contactlistWidget->itemAt(pos);//判断鼠标点击的位置是否在item上
    if(item==nullptr)//不在item上不显示菜单
    {
        return;
    }
    qDebug()<<"123:"<<ui->contactlistWidget->itemAt(mapFromGlobal(QCursor::pos()));
    popMenu_in_contactListWidget->addAction(action_msg);
    popMenu_in_contactListWidget->addAction(action_tab);
    popMenu_in_contactListWidget->addAction(action_sendcard);
    popMenu_in_contactListWidget->addSeparator();//添加分隔线
    popMenu_in_contactListWidget->addAction(action_delete);
    connect(action_delete,&QAction::triggered,this,&chatmainwindow::on_deleteTriggered);
    connect(action_msg,&QAction::triggered,this,&chatmainwindow::on_msgTriggered);
    popMenu_in_contactListWidget->exec(gobalpos); // 菜单出现的位置为当前鼠标的位置


}

void chatmainwindow::on_deleteTriggered()//菜单删除联系人功能
{
    QListWidgetItem *items=ui->contactlistWidget->currentItem();//获取当前选中的行
    int row=ui->contactlistWidget->row(items);//获取行号
    qDebug()<<"测试这是选的是第几列item"<<row;//item从0开始
    selectGroupWidget->deleteListInfo(row);
    delete items;//删除列表
    //删除数据库中的记录
    QSqlQuery query6;
    query6.prepare("delete  from friends where user_id=? and friend_user_id=? ");//删除好友表中的主用户和好友账号记录
    query6.bindValue(0,getmainUserid);
    query6.bindValue(1,v.at(row));//容器list存放的是好友列表
    query6.exec();//执行语句；
    //设置删除后再添加控件的参数
    qDebug()<<"单击列表的账号"<<v.at(row);
    updateDeleteAfterWidget(row);//调用updateDeleteAfterWidget(int row)函数更新删除联系人后，再次添加添加人之中的控件
    v.erase(v.begin()+row);//在容器list中删除该好友的信息



}

bool chatmainwindow::is_or_notInMessageList()//判断在联系人列表中选中要发送信息的好友是否已经存在在消息联系人中
{
    QListWidgetItem *contactitem1=ui->contactlistWidget->currentItem();//获取contactListwidget中已被选中的item
    int contactrow1=ui->contactlistWidget->row(contactitem1);//获取具体行
    QSqlQuery query5;
    query5.prepare("select count(MessageFriends) from  usermessagefriends where MessageFriends=? ");
    query5.bindValue(0,v.at(contactrow1));
    query5.exec();
    while(query5.next())
    {
        status=query5.value(0).toInt();
        qDebug()<<"测试是否已在好友列表中的状态:"<<status;

    }
    if(status==1)//如果为1，表示已经存在，就返回false,表示不能再在消息联系人列表框中添加，并直接显示对话框
    {

        return false;
    }
    else
    {
        return true;
    }

}

void chatmainwindow::on_msgTriggered()//菜单发送信息功能，需要判断是否已在消息列表框中
{
    qDebug()<<"执行到此处";
    bool is_or_not=is_or_notInMessageList();
    if(is_or_not)
    {
        addmessNumber();//在消息列表框中添加消息联系人；
        ui->stackedWidget->setCurrentIndex(0);
        ui->msgbtn->setIcon(QIcon("img/chat2.svg"));
        ui->contactBtn->setIcon(QIcon("img/contact.svg"));


        ui->rstackedWidget->setCurrentIndex(0);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->msgbtn->setIcon(QIcon("img/chat2.svg"));
        ui->contactBtn->setIcon(QIcon("img/contact.svg"));
        ui->rstackedWidget->setCurrentIndex(0);
    }

}
void chatmainwindow::saveFriendInfo(QString FriendInfoId)//把好友的账号插入到容器中
{
    v.push_back(FriendInfoId);

}
void chatmainwindow::updataMyselfinfoWidget()//更新个人信息窗体
{
    MySelfInfoWidget=new myselfinfoWidget;
    MySelfInfoWidget->setGeometry(this->pos().x()+200,this->pos().y()+40,355,240);
    MySelfInfoWidget->show();
    QSqlQuery query;
    query.prepare("select * from userchat where user = ?");
    query.bindValue(0,ui->searchlineEdit->text());
    query.exec();
    while(query.next())
    {
        MySelfInfoWidget->ui->myselfinfo_userid->setText(query.value(0).toString());//显示个人的账号
        MySelfInfoWidget->ui->myselfinfo_chatname_label->setText(query.value(2).toString());//显示个人的昵称
        QByteArray imagedata1=query.value(3).toByteArray();
        QPixmap photo_1;
        photo_1.loadFromData(imagedata1);
        MySelfInfoWidget->ui->myselfinfo_head_label->setPixmap(photo_1);//显示个人的头像
        MySelfInfoWidget->ui->myselfinfo_head_label->setScaledContents(true);
    }

}


void chatmainwindow::on_contactlistWidget_itemClicked(QListWidgetItem *item)//单击好友列表中的item时，展示好友的具体信息
{

    int row=ui->contactlistWidget->row(item);//获取当前联系人列表的行数
    qDebug()<<"单击列表的账号"<<v.at(row);
    QSqlQuery query7;
    query7.prepare("select *from userchat where user=?");
    query7.bindValue(0,v.at(row));//容器v存里存放的是好友的信息
    query7.exec();//执行sql语句
    while(query7.next())//遍历
    {
        QByteArray imagedata=query7.value(3).toByteArray();
        QPixmap photo_2;
        photo_2.loadFromData(imagedata);
        ui->friendsinfowidget_head_label->setPixmap(photo_2);//头像
        ui->friendsinfowidget_head_label->setScaledContents(true);
        ui->friendinfowidget_userid_label->setText(query7.value(0).toString());//账号
        ui->friendinfowidget_chatname_label->setText(query7.value(2).toString());//昵称
    }
    ui->rstackedWidget->setCurrentIndex(1);//展示
    qDebug()<<"row"<<row;
}
void chatmainwindow::updateDeleteAfterWidget(int row)//更新删除联系人后，再次添加添加人之中的控件
{
    QSqlQuery query2;
    query2.prepare("select *from userchat where user=?");
    query2.bindValue(0,v.at(row));//容器v存里存放的是好友的信息
    query2.exec();//执行sql语句
    while(query2.next())//遍历
    {
        QByteArray imagedata=query2.value(3).toByteArray();
        QPixmap photo_2;
        photo_2.loadFromData(imagedata);
        ui->deletefriendsinfowidget_head_label_2->setPixmap(photo_2);//头像
        ui->deletefriendsinfowidget_head_label_2->setScaledContents(true);
        ui->deletefriendinfowidget_userid_label_2->setText(query2.value(0).toString());//账号
        ui->deletefriendinfowidget_chatname_label_2->setText(query2.value(2).toString());//昵称
    }
    ui->rstackedWidget->setCurrentIndex(2);//切换到删除后再添加的界面
}

void chatmainwindow::addmessNumber()//在消息列表中添加item
{
    QListWidgetItem *contactitem=ui->contactlistWidget->currentItem();
    int contactrow=ui->contactlistWidget->row(contactitem);
    qDebug()<<"测试语句，添加的是："<<contactrow;
    qDebug()<<"测试语句，取出容器v的值为："<<v.at(contactrow);

    QListWidgetItem *messageitem=new QListWidgetItem;
    UserMessageWidget=new usermsgwidgetinfo(this);//实例自定义消息列表的控件
    //查询该好友的信息，并更新到消息列表item中
    QSqlQuery query3;
    query3.prepare("select * from userchat where user=?");
    query3.bindValue(0,v.at(contactrow));
    query3.exec();
    while(query3.next())
    {
        QSqlQuery query4;
        query4.prepare("insert into usermessagefriends(Mainuser,MessageFriends) value(?,?)");//在指定数据库表中插入在主用户的聊天列表中相关的记录
        query4.bindValue(0,getmainUserid);
        query4.bindValue(1,v.at(contactrow));
        query4.exec();//执行语句

        messageV.append(v.at(contactrow));//当单击发送信息时，会把当前好友的账号保存到消息列表容器中，用来操作消息联系人列表框
        UserMessageWidget->setUserid(query3.value(2).toString());//设置用户名
        ui->funclabel->setText(query3.value(2).toString());
        QPixmap UserMessageWidgetHeadImg;
        QByteArray dataimg=query3.value(3).toByteArray();
        UserMessageWidgetHeadImg.loadFromData(dataimg);
        UserMessageWidget->setHeadImg(UserMessageWidgetHeadImg);//设置头像

    }

    UserMessageWidget->show();//显示
    ui->message_listWidget->addItem(messageitem);
    ui->message_listWidget->setItemWidget(messageitem,UserMessageWidget);
}


void chatmainwindow::on_message_listWidget_customContextMenuRequested(const QPoint &pos)//消息联系人列表菜单
{
    QPoint gobalpos1=ui->message_listWidget->mapToGlobal(pos);
    popMenu_in_messageListWidget=new QMenu;
    popMenu_in_messageListWidget->setStyleSheet("QMenu {background-color:rgba(255,255,255,1);border:1px solid rgb(233,233,233);color:rgb(0,0,0);}"
                                                "QMenu::item {width:120px;height:25px;margin:0px;padding:4px 30px}"
                                                "QMenu::item:selected {background:rgb(225,225,225);}"
                                                "QMenu::item:pressed {background:rgb(225,225,225);/*摁下状态*/};");//设置消息人列表菜单的样式


    action_Settop=new QAction("置顶");
    action_noRead=new QAction("标为未读");
    action_messageNO=new QAction("消息免打扰");
    action_newmessageWidget=new QAction("在独立窗口中打开");
    action_noShowMessage=new QAction("不显示聊天");
    action_deleteMessage=new QAction("删除聊天");
    QListWidgetItem *item1=ui->message_listWidget->itemAt(pos);
    if(item1==nullptr)
    {
        return;
    }
    popMenu_in_messageListWidget->addAction(action_Settop);
    popMenu_in_messageListWidget->addAction(action_noRead);
    popMenu_in_messageListWidget->addAction(action_messageNO);
    popMenu_in_messageListWidget->addAction(action_newmessageWidget);
    popMenu_in_messageListWidget->addSeparator();
    popMenu_in_messageListWidget->addAction(action_noShowMessage);
    popMenu_in_messageListWidget->addAction(action_deleteMessage);
    connect(action_deleteMessage,&QAction::triggered,this,&chatmainwindow::deleteMsgContactPerson);//当动作触发时
    popMenu_in_messageListWidget->exec(gobalpos1);

}

void chatmainwindow::deleteMsgContactPerson()//实现消息列表菜单的删除聊天功能；
{
    QListWidgetItem *item5=ui->message_listWidget->currentItem();//获取当前选中的item
    int row3=ui->message_listWidget->row(item5);//转换成行号
    delete item5;//删除对应的列表

    //删除数据库中对应的记录
    QSqlQuery query9;
    query9.prepare(" delete from usermessagefriends where Mainuser=? and MessageFriends=?");//删除消息表中的主用户和好友账号记录
    query9.bindValue(0,getmainUserid);
    query9.bindValue(1,messageV.at(row3));//容器list存放的是好友列表
    query9.exec();//执行语句；

    messageV.erase(messageV.begin()+row3);//删除保存在容器中保存的对应记录
}

void chatmainwindow::setUserHeadimg(const QPixmap &photo)//更新主用户的头像
{
    ui->MainUserheadImg->setPixmap(photo);
    ui->MainUserheadImg->setScaledContents(true);
}

void chatmainwindow::initaddmessageNumber(QString info)//初始化消息列表
{
    QListWidgetItem *messageitem=new QListWidgetItem;
    UserMessageWidget=new usermsgwidgetinfo(this);//实例自定义消息列表的控件
    //查询该好友的信息，并更新到消息列表item中
    QSqlQuery query3;
    query3.prepare("select * from userchat where user=?");
    query3.bindValue(0,info);
    query3.exec();
    while(query3.next())
    {
        UserMessageWidget->setUserid(query3.value(2).toString());//设置用户名
        QPixmap UserMessageWidgetHeadImg;
        QByteArray dataimg=query3.value(3).toByteArray();
        UserMessageWidgetHeadImg.loadFromData(dataimg);
        UserMessageWidget->setHeadImg(UserMessageWidgetHeadImg);//设置头像
    }
    UserMessageWidget->show();//显示
    ui->message_listWidget->addItem(messageitem);
    ui->message_listWidget->setItemWidget(messageitem,UserMessageWidget);
}


void chatmainwindow::dealMessage(MychatMessage *messageW, QListWidgetItem *item, QString text, QString time,  MychatMessage::User_Type type)//处理聊天消息
{
//    messageW->setFixedWidth(this->width());
    messageW->setFixedWidth(ui->rsvMessagelistWidget->width()-1);//消息框出现的位置
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->rsvMessagelistWidget->setItemWidget(item, messageW);
}

void chatmainwindow::dealMessageTime(QString curMsgTime)//处理聊天时间
{
    bool isShowTime = false;
    if(ui->rsvMessagelistWidget->count() > 0)
    {
        QListWidgetItem* lastItem = ui->rsvMessagelistWidget->item(ui->rsvMessagelistWidget->count() - 1);
        MychatMessage* messageW = (MychatMessage*)ui->rsvMessagelistWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
        //        isShowTime = true;
    }
    else
    {
        isShowTime = true;
    }
    if(isShowTime)
    {
        MychatMessage* messageTime = new MychatMessage(ui->rsvMessagelistWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->rsvMessagelistWidget);
        QSize size = QSize(ui->rsvMessagelistWidget->width()-1, 40);//设置时间出现的位置
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, MychatMessage::User_Time);
        ui->rsvMessagelistWidget->setItemWidget(itemTime, messageTime);
    }
}

void chatmainwindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    for(int i = 0; i < ui->rsvMessagelistWidget->count(); i++)
    {
        MychatMessage* messageW = (MychatMessage*)ui->rsvMessagelistWidget->itemWidget(ui->rsvMessagelistWidget->item(i));
        QListWidgetItem* item = ui->rsvMessagelistWidget->item(i);
        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());//处理消息
    }
}

void chatmainwindow::on_message_listWidget_itemClicked(QListWidgetItem *item)//处理当单击item消息联系人列表框时
{
    int row=ui->message_listWidget->row(item);
    ui->rstackedWidget->setCurrentIndex(0);
    qDebug()<<"测试语句：当单击message_listwidget时，messagev容器的值是否对应:"<<messageV.at(row);
    //更新funclabel为好友的昵称
    QSqlQuery query8;
    query8.prepare("select *from userchat where user=?");
    query8.bindValue(0,messageV.at(row));
    query8.exec();
    while(query8.next())//遍历
    {
        ui->funclabel->setText(query8.value(2).toString());
    }

}

void  chatmainwindow::addGroupPeople()//在选择群聊列表中添加一个item
{

    selectGroupWidget->addAListwidget();
}

void  chatmainwindow::updataGroupPeople(QString id)//更新选择群聊列表中item的控件信息
{
    QSqlQuery q3;
    q3.prepare("select *from userchat where user=?");
    q3.bindValue(0,id);
    q3.exec();
    while (q3.next())
    {
        QByteArray photostream=q3.value(3).toByteArray();
        QPixmap photo;
        photo.loadFromData(photostream);
        selectGroupWidget->settingImg(photo);
        selectGroupWidget->settingname(q3.value(2).toString());
    }
}

