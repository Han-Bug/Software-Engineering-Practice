#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <vector>
#include <list>

#include "database_interaction/database_interaction.h"
#include "login_interface/login_interface.h"
#include "personal_info_widget/personal_interface.h"
#include "post_information/post_widget.h"
#include "publish_article_interface.h"

class login_interface;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(database_interaction *db,QWidget *parent = 0);
    //设置个人信息
    void setPersonalInfo(personal_information* pi);
    //更新广场
    void updatePost(int type=-1);

    ~MainWindow();

private slots:
    void on_user_clicked();

    void on_pushButton_publish_clicked();

    void on_pushButton_dailyShare_clicked();

private:
    Ui::MainWindow *ui;
    //滚动界面布局
    QVBoxLayout *layout_post;

    //个人界面
    personal_interface *pi;

    //文章小窗口容器
    vector<post_widget*> pw_v;

    //数据库交互模块
    database_interaction *db;
    //个人信息
    personal_information *personalInfo=NULL;



    //测试用
private:

};

#endif // MAINWINDOW_H
