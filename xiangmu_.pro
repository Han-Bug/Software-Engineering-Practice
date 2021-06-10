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
    comment_widget.cpp \
    database_interaction/database_interaction.cpp \
    login_interface/login_interface.cpp \
    login_interface/register_interface.cpp \
    mainwindow/mainwindow.cpp \
    personal_info_widget/personal_interface.cpp \
    post_information/post_detailed_info.cpp \
    post_information/post_widget.cpp \
    main.cpp \
    validity_test.cpp \
    publish_article_interface.cpp \
    associated_interface.cpp \
    comments_widget.cpp

HEADERS += \
    comment_widget.h \
    database_interaction/database_interaction.h \
    login_interface/login_interface.h \
    login_interface/register_interface.h \
    mainwindow/mainwindow.h \
    personal_info_widget/personal_interface.h \
    post_information/post_detailed_info.h \
    post_information/post_widget.h \
    data_structs.h \
    validity_test.h \
    publish_article_interface.h \
    associated_interface.h \
    Search.h \
    comments_widget.h

SUBDIRS += \
    xiangmu_.pro

FORMS += \
    comment_widget.ui \
    login_interface/login_interface.ui \
    login_interface/register_interface.ui \
    mainwindow/mainwindow.ui \
    personal_info_widget/personal_interface.ui \
    post_information/post_detailed_info.ui \
    publish_article_interface.ui \
    associated_interface.ui \
    comments_widget.ui
