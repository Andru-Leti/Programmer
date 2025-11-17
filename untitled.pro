QT       += core gui quick widgets network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bulletin_board.cpp \
    create_2.cpp \
    data_base_2.cpp \
    main.cpp \
    mainwindow.cpp \
    now.cpp \
    registration.cpp

HEADERS += \
    bulletin_board.h \
    create_2.h \
    data_base_2.h \
    mainwindow.h \
    now.h \
    registration.h

FORMS += \
    bulletin_board.ui \
    create_2.ui \
    data_base_2.ui \
    mainwindow.ui \
    now.ui \
    registration.ui

 #Default rules for deployment.
 qnx: target.path = /tmp/$${TARGET}/bin
 else: unix:!android: target.path = /opt/$${TARGET}/bin
 !isEmpty(target.path): INSTALLS += target

