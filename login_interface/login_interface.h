#ifndef LOGIN_INTERFACE_H
#define LOGIN_INTERFACE_H

#include <QDialog>
#include <QDebug>
#include <QMainWindow>
#include "database_interaction/database_interaction.h"
#include "register_interface.h"
#include "personal_info_widget/personal_interface.h"
#include "data_structs.h"
#include "mainwindow/mainwindow.h"
namespace Ui {
class login_interface;
}

class login_interface : public QDialog
{
    Q_OBJECT

public:
    explicit login_interface(QWidget *parent = 0);

    //personal_information* personalInfo;    //用户信息绑定

    ~login_interface();

private slots:
    void on_pushButton_login_in_clicked();

    void on_lineEdit_account_returnPressed();

    void on_pushButton_register_clicked();


private:
    Ui::login_interface *ui;
    database_interaction* db;                   //数据库绑定
    //register_interface* ri;                     //注册界面绑定

};

#endif // LOGIN_INTERFACE_H
