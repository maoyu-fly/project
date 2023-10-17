#ifndef MYCHATMESSAGE_H
#define MYCHATMESSAGE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QDebug>
#include <QFontMetrics>
#include <QDateTime>
class MychatMessage : public QWidget
{
    Q_OBJECT
public:
    explicit MychatMessage(QWidget *parent = nullptr);
    enum User_Type//枚举类型
    {
        User_System,//系统
        User_Me,    //自己
        User_She,   //用户
        User_Time,  //时间
    };
    void setTextSuccess();
    void setText(QString text, QString time, QSize allSize, User_Type userType);
    void setLeftPixmap(const QPixmap lPhoto);//设置左边的图片
    void setRightPixmap(const QPixmap rPhoto);//设置右边的图片

    QSize getRealString(QString src);
    QSize fontRect(QString str);

    inline QString text() {return m_msg;}
    inline QString time() {return m_time;}
    inline User_Type userType() {return m_userType;}
protected:
    void paintEvent(QPaintEvent *event);
private:
    QString m_msg;//消息的文本
    QString m_time;//消息发送的时间
    QString m_curTime;//要显示的格式化时间字符串

    QSize m_allSize;//整个聊天窗口的大小
    User_Type m_userType = User_System;

    int m_kuangWidth;
    int m_textWidth;
    int m_spaceWid;
    int m_lineHeight;

    QRect m_iconLeftRect;
    QRect m_iconRightRect;
    QRect m_sanjiaoLeftRect;
    QRect m_sanjiaoRightRect;
    QRect m_kuangLeftRect;
    QRect m_kuangRightRect;
    QRect m_textLeftRect;
    QRect m_textRightRect;
    QPixmap m_leftPixmap;//左边图片
    QPixmap m_rightPixmap;//右用户图片
    bool m_isSending = false;//判断是否为发送状态


signals:

};

#endif // MYCHATMESSAGE_H
