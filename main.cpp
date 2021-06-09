#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <list>
#include <vector>
#include <QMessageBox>
#include "mainwindow/mainwindow.h"
#include "login_interface/login_interface.h"
#include "personal_info_widget/personal_interface.h"
#include "database_interaction/database_interaction.h"
#include "data_structs.h"
#include "publish_article_interface.h"

int main(int argc, char *argv[])
{
    database_interaction db("127.0.0.1","SE_db_usersInformation","sa","929014757");
    qDebug()<<"is database open successfully?"<<db.open_database();
    Data::dataBaseInter=&db;
    QApplication a(argc, argv);
    if(Data::dataBaseInter==NULL){
        QMessageBox errorMessageBox;
        errorMessageBox.setText("数据库连接失败！请检查数据源相关配置");
        errorMessageBox.exec();
        a.quit();
    }
    MainWindow m;
    m.show();
    return a.exec();
}
