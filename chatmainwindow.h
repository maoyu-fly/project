#ifndef CHATMAINWINDOW_H
#define CHATMAINWINDOW_H

#include <QWidget>
#include <QUdpSocket>//使用udp套接字的类库
#include <QNetworkInterface>//网络(IP地址)接口库
#include <QDateTime>//时间日期库
#include <QFile>//系统文件类库
#include <QFileDialog>//文件对话框库
#include <QMessageBox>
#include "qdom.h"
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QSqlQuery>
#include <addfridensfunction/addfridentsmallwidget.h>//包含添加好友的界面
#include "ui_addfridentsmallwidget.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QEvent>
#include <friendsinfo/friendsitem.h>
#include "ui_friendsitem.h"
#include <friendsinfo/is_friendsinfowidget.h>
#include <QMenu>
#include <QListWidgetItem>
#include <QList>
#include <myselfinfo/myselfinfowidget.h>
#include <ui_myselfinfowidget.h>
#include <friendsinfo/friendinfowidget.h>
#include "ui_friendinfowidget.h"
#include <msgwidgetinfo/usermsgwidgetinfo.h>
#include <QDate>
#include <chatwidget/formsendsmallwidget.h>
#include <chatwidget/mychatmessage.h>
#include <QHostAddress>
#include <groupwidget/selectgroup.h>
class FileSrvDlg;
namespace Ui {
class chatmainwindow;
}

class chatmainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit chatmainwindow(QWidget *parent = nullptr);
    ~chatmainwindow();
public:
    void setUserHeadimg(const QPixmap &photo);//设置主用户的头像

    void intiUdp();//初始化udp套接字

    void sendMsg();//发送UDP消息

    QString getHostip();//获取本端的IP地址

    QString getLocChatMsg();//获取本端的聊天信息内容

    void recvFileName(QString name,QString hostip,QString rmtname,QString filename);

    void addfriendsInfo();//新增好友列表记录

    void updatafriendsitemData(QString frid);//更新好友列表中的控件

    void updatafriendsWidgetInfo();//更新已是好友窗口中的信息

    void saveFriendInfo(QString FriendInfoId);//保存好友的信息到list中

    void updataMyselfinfoWidget();//更新个人信息窗体

    void updateDeleteAfterWidget(int row);//更新删除联系人后，再次添加添加人之中的控件

    void addmessNumber();//当在联系人列表的菜单中单击，则会在消息列表中新增一个item

    void initaddmessageNumber(QString info);//用来初始化联系人列表

    bool is_or_notInMessageList();//判断好友是否已在消息列表中

    int status;

    Formsendsmallwidget *sendSmallwidget;

    void dealMessage(MychatMessage *messageW, QListWidgetItem *item, QString text, QString time, MychatMessage::User_Type type);

    void dealMessageTime(QString curMsgTime);


protected:
    void resizeEvent(QResizeEvent *event);



public:
    bool is_topwindow;//实现置顶状态，图片的切换

    addfridentsmallwidget *addFridentSmallWidget;

    QString getmainUserid;//获取主用户账号,用于在数据库中插入数据；

    QString getcontactmainuserid;//获取好友用户账号

    friendsitem *Friendsitem;//好友列表窗体

    is_friendsinfowidget *Is_Friendsinfo;//好友的信息窗体

    myselfinfoWidget *MySelfInfoWidget;//个人信息窗体

    QList<QString> v;//把好友的账号保存在容器中

    QList<QString> messageV;//保存关于消息列表的容器

    friendinfowidget *FriendInfoWidget;//当单击好友列表时，显示的窗体

    usermsgwidgetinfo *UserMessageWidget;//用户消息列表

    selectGroup *selectGroupWidget;//选择联系人进行群聊窗体

    void addGroupPeople();//在选择群聊列表中添加一个item

    void updataGroupPeople(QString id);//更新选择群聊列表中item的控件信息




//移动窗口功能
protected:
    // Event handlers
    virtual void mousePressEvent(QMouseEvent *event);//鼠标按下

    virtual void mouseMoveEvent(QMouseEvent *event);//鼠标移动



public:
    QPoint mouseWindowTopLeft; //鼠标相对窗口左上角的坐标         在mousePressEvent 得到

    QPoint mouseDeskTopLeft;   //鼠标相对于桌面左上角坐标         在mouseMoveEvent实时获取

    QPoint windowDeskTopLeft;  //窗口左上角相对于桌面左上角坐标    在mouseMoveEvent实时计算(矢量)获得

private slots:

    void on_sendbtn_clicked();//发送按钮的单击事件方法

    void on_transbtn_clicked();

    void on_pushButton_clicked();

    void on_contactBtn_clicked();//联系人

    void on_collectBtn_clicked();//收藏

    void on_msgbtn_clicked();//消息发送

    void on_closewindowbtn_clicked();//关闭窗口

    void on_minwindowbtn_clicked();//最小化窗口

    void on_maxwindowbtn_clicked();//最大化窗口

    void on_topwindowbtn_clicked();//置顶窗口

    void on_folderBtn_clicked();//文件按钮

    void on_addbtn_clicked();//添加

    void on_searchcancelbtn_clicked();//搜索按钮触发

    void on_searchlineEdit_textEdited();//编辑文本时

    void on_searbtn_clicked();//单击搜索按钮时

    void on_addfriend();//添加好友；

    void on_contactlistWidget_customContextMenuRequested(const QPoint &pos);

    void on_contactlistWidget_itemClicked(QListWidgetItem *item);

    void on_message_listWidget_customContextMenuRequested(const QPoint &pos);//展示在消息列表中的菜单

    void deleteMsgContactPerson();//实现消息列表菜单的删除聊天功能；

    void userReceiveMessage();//用户接收消息





    void on_message_listWidget_itemClicked(QListWidgetItem *item);

private:

    QUdpSocket *userUdpsocket;

    QString myname="";//本端当前用户名
//    QUdpSocket *myudpsocket;//udp套接字
    int port;//用户端口号
    QString myfilename;
    QDomDocument mydoc;

    //制作联系人右键菜单
    QMenu *popMenu_in_contactListWidget;//弹出菜单
    QAction *action_delete;//删除
    QAction *action_msg;//发送信息
    QAction *action_tab;//标记
    QAction *action_sendcard;//发送名片

    //制作消息联系人右键菜单
    QMenu *popMenu_in_messageListWidget;//菜单
    QAction *action_Settop;//置顶设置
    QAction *action_noRead;//标记为未读
    QAction *action_messageNO;//消息免打扰
    QAction *action_newmessageWidget;//在独立窗口中打开
    QAction *action_noShowMessage;//不显示聊天
    QAction *action_deleteMessage;//删除聊天；


public slots:
    void on_deleteTriggered();
    void on_msgTriggered();


private:
    Ui::chatmainwindow *ui;
};

#endif // CHATMAINWINDOW_H
