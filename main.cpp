#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <list>
#include <vector>

#include "mainwindow/mainwindow.h"
#include "login_interface/login_interface.h"
#include "personal_info_widget/personal_interface.h"
#include "database_interaction/database_interaction.h"
#include "data_structs.h"
#include "publish_article_interface.h"

int main(int argc, char *argv[])
{
    database_interaction db("127.0.1.1","123","sa","123456");
    qDebug()<<"is database open successfully?"<<db.open_database();
    list<article_post*> l;
    db.getPostInfo(l,0,"202200000000","000000000000",-1);
    QApplication a(argc, argv);
    MainWindow m(&db);
    m.show();
    return a.exec();
}
