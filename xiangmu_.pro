#-------------------------------------------------
#
# Project created by QtCreator 2021-04-28T20:10:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xiangmu_
TEMPLATE = app

INCLUDEPATH += .\search_engine

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    comment/comment_widget.cpp \
    comment/comments_widget.cpp \
    database_interaction/database_interaction.cpp \
    login_interface/login_interface.cpp \
    login_interface/register_interface.cpp \
    mainwindow/mainwindow.cpp \
    personal_info_widget/personal_interface.cpp \
    post_information/post_detailed_info.cpp \
    post_information/post_widget.cpp \
    associated_interface.cpp \
    main.cpp \
    publish_article_interface.cpp \
    validity_test.cpp

HEADERS += \
    comment/comment_widget.h \
    comment/comments_widget.h \
    database_interaction/database_interaction.h \
    login_interface/login_interface.h \
    login_interface/register_interface.h \
    mainwindow/mainwindow.h \
    personal_info_widget/personal_interface.h \
    post_information/post_detailed_info.h \
    post_information/post_widget.h \
    associated_interface.h \
    data_structs.h \
    publish_article_interface.h \
    Search.h \
    validity_test.h

SUBDIRS += \
    xiangmu_.pro

FORMS += \
    comment/comment_widget.ui \
    comment/comments_widget.ui \
    login_interface/login_interface.ui \
    login_interface/register_interface.ui \
    mainwindow/mainwindow.ui \
    personal_info_widget/personal_interface.ui \
    post_information/post_detailed_info.ui \
    post_information/post_widget.ui \
    associated_interface.ui \
    publish_article_interface.ui


RESOURCES += \
    photo/photo.qrc

DISTFILES += \
    photo/beijing.png \
    photo/blackheart.png \
    photo/blackstar.png \
    photo/gray.png \
    photo/redheart.png \
    photo/white.png \
    photo/whitebeijing.png \
    photo/yellowstar.png
