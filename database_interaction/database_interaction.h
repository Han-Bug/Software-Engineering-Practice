#ifndef DATABASE_INTERACTION_H
#define DATABASE_INTERACTION_H
#include <iostream>
using namespace std;
#include <list>
#include <vector>

#include <QMessageBox>
#include <QDebug>
#include <QString>

#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "data_structs.h"

class database_interaction
{
public:
    database_interaction(QString _host,QString _dataBaseName,QString _userName,QString _password);

    //打开数据库
    bool open_database();
    //验证帐号数据，若存在则返回true并将数据写入pi，不存在则返回false
    bool accountVerification(personal_information* &pi,QString account,QString password);
    //获取指定类型、时间区间的文章数据  num:需获取的文章数量，-1表示无数量限制
    //bool getPostInfo(list<article_post*> &l,int type,int start_time,int end_time,int num=-1);
    //写入新帐号数据
    //bool registerNewAccount(const personal_information &pi);
    //写入新文章数据
    //bool registerNewPost(const article_post &ap);
    //写入新的关联：用户-文章   type:关联类型
    //bool registerNewLink_PersonToPost(QString personalAccount,QString postId,int type);
    //判断某属性是否存在  例如：tableName=personal_information;columnName=name;value="123456" 即判断是否存在name值为“123456”的account
    //bool existenceTest(QString tableName,QString columnName,QString value);

    //获取数据
    bool selectData(list<vector<QString>*> &l, int typeNum,QString sourse, QString limitStatement="");
    //删除数据
    bool deleteData(QString sourse, QString limitStatement="");
    //插入数据
    bool insertData_PersonalInformation(QString _account,QString _password,QString _name);
    bool insertData_ArticlePost(QString _title,QString _text,int _type,QString _time,int _postId,QString _author_name);
    bool insertData_Associated_TagToPost(QString _postId,QString _tag);
    bool insertData_Associated_UserToPost(QString _postId,QString _account);

    //更新数据
    bool updateData_PersonalInformation_Name(QString _account,QString _name);
    bool updateData_PersonalInformation_Password(QString _account,QString _password);
    //获取当前数据库时间
    QString getDate();
    //获取某数据的已有数量
    int getNumberOf(QString source);

    ~database_interaction(){db.close();}
private:
    QString host;
    QString dataBaseName;
    QString userName;
    QString password;
    QSqlDatabase db;
    bool isConnect=false;
};

#endif // DATABASE_INTERACTION_H
