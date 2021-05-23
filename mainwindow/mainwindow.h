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
#include "associated_interface.h"
#include "Search.h"

//using namespace  std;

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
    void updatePost();

    ~MainWindow();

private slots:
    void on_user_clicked();

    void on_pushButton_publish_clicked();

    void on_pushButton_doSearch_clicked();

    void on_pushButton_dailyShare_clicked(bool checked);

    void on_pushButton_forOrders_clicked(bool checked);

    void on_pushButton_lostAndFound_clicked(bool checked);

    void on_pushButton_expExchange_clicked(bool checked);

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

    Search *se;

    bool* types;


    //测试用
private:

};

#endif // MAINWINDOW_H
