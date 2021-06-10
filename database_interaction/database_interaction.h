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
    bool getPostInfo(list<article_post*> &l, int type, QString start_time, QString end_time, int num=-1);
    bool getComments(list<comment*> &l,int post_id,QString start_time,QString end_time,int num=-1);
    //获取数据
    bool selectData(list<vector<QString>*> &l, int typeNum,QString sourse, QString limitStatement="");
    //删除数据
    bool deleteData(QString sourse, QString limitStatement="");
    //插入数据
    bool insertData_PersonalInformation(QString _account,QString _password,QString _name);
    bool insertData_ArticlePost(QString _title,QString _text,int _type,QString _time,int _postId,QString _author_name);
    bool insertData_Associated_TagToPost(QString _postId,QString _tag);
    bool insertData_Associated_UserToPost(QString _postId,QString _account);
    bool insertData_Comment(QString _text,QString _author_name,QString _author_id,int _commentId,int _postId,QString _time);

    bool Fabulous_UserToPost(int _postId,QString _account);
    bool Collect_UserToPost(int _postId,QString _account);
    bool selectCount(int &a, int &b, int _postId);
    bool getPostInfo_collect(list<article_post*> &l, QString _account);
    bool deleteData_Collect_UserToPost(int _postId,QString _account);
    bool deleteData_Fabulous_UserToPost(int _postId,QString _account);
    bool insertData_Collect_UserToPost(int _postId,QString _account);
    bool insertData_Fabulous_UserToPost(int _postId,QString _account);
    //更新数据
    bool updateData_PersonalInformation_Name(QString _account,QString _name);
    bool updateData_PersonalInformation_Password(QString _account,QString _password);
    //获取当前数据库时间
    QString getDate();
    bool isConnected();
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
struct Data{
    static personal_information* personalInfo;
    static database_interaction* dataBaseInter;
};

#endif // DATABASE_INTERACTION_H
