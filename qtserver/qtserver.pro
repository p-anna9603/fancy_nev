#-------------------------------------------------
#
# Project created by QtCreator 2020-02-26T15:57:47
#
#-------------------------------------------------

QT       += core gui sql
QT       += core network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtserver
TEMPLATE = app
QTPLUGIN = QSQLMYSQL

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        dialog.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        dialog.h \
        mainwindow.h

FORMS += \
        dialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libek/
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libek/
#else:unix: LIBS += -L$$PWD/../libek/

INCLUDEPATH += $$PWD/../libek
DEPENDPATH += $$PWD/../libek
#ANNA fasdlkjflkdsahfélkadjsélh
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/'
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/'
else:unix: LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/'
#INCLUDEPATH += $$PWD/../libek
#DEPENDPATH += $$PWD/../libek

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/'
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/'
#else:unix: LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/'

#INCLUDEPATH += $$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib'
#DEPENDPATH += $$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib'

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/'
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/'
#else:unix: LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/'

#INCLUDEPATH += $$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib'
#DEPENDPATH += $$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib'

#DISTFILES += \
#    ../../../../Program Files/MySQL/MySQL Server8.0/lib/libmysql.dll

##win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/' -llibmysql
##else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/' -llibmysqld
##else:unix: LIBS += -L$$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/lib/' -llibmysql

#INCLUDEPATH += $$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/include'
#DEPENDPATH += $$PWD/'../../../../Program Files/MySQL/MySQL Server8.0/include'
