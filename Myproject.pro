QT       += core gui sql network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfridensfunction/addfridentsmallwidget.cpp \
    chatmainwindow.cpp \
    chatwidget/formsendsmallwidget.cpp \
    chatwidget/mychatmessage.cpp \
    friendsinfo/friendinfowidget.cpp \
    friendsinfo/friendsitem.cpp \
    friendsinfo/is_friendsinfowidget.cpp \
    groupwidget/grouppseroninfo.cpp \
    groupwidget/selectgroup.cpp \
    initdatabase.cpp \
    logindialog.cpp \
    loginfunction/loginfunc.cpp \
    main.cpp \
    msgwidgetinfo/usermsgwidgetinfo.cpp \
    myselfinfo/myselfinfowidget.cpp \
    widget.cpp

HEADERS += \
    addfridensfunction/addfridentsmallwidget.h \
    chatmainwindow.h \
    chatwidget/formsendsmallwidget.h \
    chatwidget/mychatmessage.h \
    friendsinfo/friendinfowidget.h \
    friendsinfo/friendsitem.h \
    friendsinfo/is_friendsinfowidget.h \
    groupwidget/grouppseroninfo.h \
    groupwidget/selectgroup.h \
    initdatabase.h \
    logindialog.h \
    loginfunction/loginfunc.h \
    msgwidgetinfo/usermsgwidgetinfo.h \
    myselfinfo/myselfinfowidget.h \
    widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    addfridensfunction/addfridentsmallwidget.ui \
    chatmainwindow.ui \
    chatwidget/formsendsmallwidget.ui \
    friendsinfo/friendinfowidget.ui \
    friendsinfo/friendsitem.ui \
    friendsinfo/is_friendsinfowidget.ui \
    groupwidget/grouppseroninfo.ui \
    groupwidget/selectgroup.ui \
    logindialog.ui \
    loginfunction/loginfunc.ui \
    msgwidgetinfo/usermsgwidgetinfo.ui \
    myselfinfo/myselfinfowidget.ui

RESOURCES += \
    img.qrc

DISTFILES +=
