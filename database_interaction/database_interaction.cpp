#include "database_interaction.h"
personal_information* Data::personalInfo=NULL;
database_interaction* Data::dataBaseInter=NULL;
database_interaction::database_interaction(QString _host,QString _dataBaseName,QString _userName,QString _password)
{
    host=_host;
    dataBaseName=_dataBaseName;
    userName=_userName;
    password=_password;
}
bool database_interaction::open_database(){
    db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
    //qDebug()<<"ODBC driver?"<<db.isValid();
    db.setHostName(host);                               //选择主机
    db.setDatabaseName(dataBaseName);                   //设置数据源名称
    db.setUserName(userName);                           //登录用户
    db.setPassword(password);                           //密码
    isConnect=db.open();
    return db.open();
}

bool database_interaction::accountVerification(personal_information* &pi,QString account, QString password)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("select * from personal_information where account='%1' and password='%2'").arg(account,password);
    query.exec(sqlSentence);
    int successfulNum=0;
    while(query.next())
    {
        pi=new personal_information(
                    query.value(0).toString(),
                    query.value(1).toString(),
                    query.value(2).toString()
                );
        successfulNum++;
    }
    //如果仅有一个结果
    if(successfulNum==1)return true;
    //如果没有结果（或因出错而有多个结果）
    return false;
}

bool database_interaction::getPostInfo(list<article_post *> &l, int type, QString start_time, QString end_time, int num)
{
    //start_time>=end_time
    if(start_time.toLongLong()<end_time.toLongLong()){
        return getPostInfo(l,type,end_time,start_time,num);
    }
    QSqlQuery query(db);
    QString sqlSentence;
    if(type<0){
        sqlSentence =QString ("select * from article_post  where time<='%1' and time>='%2' ").arg(start_time,end_time);
    }
    else{
        sqlSentence =QString ("select * from article_post  where type=%1 and time<='%2' and time>='%3' ").arg(QString::number(type),start_time,end_time);

    }
    query.exec(sqlSentence);
    int postNum=0;
    while(query.next())
       {
        if(postNum>=num&&num>=0)break;
        article_post* ap=new article_post(
                    query.value(0).toString() ,
                    query.value(1).toString() ,
                    query.value(2).toInt(),
                    query.value(3).toString(),
                    query.value(4).toInt(),
                    query.value(5).toString()
                    );
        l.push_back(ap);
        postNum++;
      }
   if(postNum==0)return false;
   return true;
}

bool database_interaction::getComments(list<comment *> &l,int post_id, QString start_time, QString end_time, int num)
{
    if(start_time.toLongLong()<end_time.toLongLong()){
        return getComments(l,post_id,end_time,start_time,num);
    }
    QSqlQuery query(db);
    QString sqlSentence;
    sqlSentence =QString ("select * from comment where post_id=%1 and time<='%2' and time>='%3' ").arg(QString::number(post_id),start_time,end_time);
    query.exec(sqlSentence);
    int commentNum=0;
    while(query.next())
       {
        if(commentNum>=num&&num>=0)break;
        comment* cm=new comment(
                    query.value(0).toString(),
                    query.value(1).toString(),
                    query.value(2).toString(),
                    query.value(3).toInt(),
                    query.value(4).toInt(),
                    query.value(4).toString()
                    );
        l.push_back(cm);
        ++commentNum;
      }
   if(commentNum==0)return false;
   return true;
}

bool database_interaction::selectData(list<vector<QString>*> &l, int typeNum,QString sourse, QString limitStatement)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("select * from %1 %2").arg(sourse,limitStatement);
    query.exec(sqlSentence);
    int successfulNum=0;
    while(query.next())
    {
        //新建容器
        vector<QString>* v=new vector<QString>;
        //将获取的每个元组的数据以QString类型存储至该容器中
        for(int i=0;i<typeNum;i++){
            v->push_back(query.value(i).toString());
        }
        l.push_back(v);
        successfulNum++;
    }
    return true;
}

bool database_interaction::deleteData(QString sourse, QString limitStatement)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("delete from %1 %2").arg(sourse,limitStatement);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

bool database_interaction::insertData_PersonalInformation(QString _account, QString _password, QString _name)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into personal_information values('%1','%2','%3')").arg(_account,_password,_name);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

bool database_interaction::insertData_ArticlePost(QString _title, QString _text, int _type, QString _time, int _postId, QString _author_name)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into article_post values('%1','%2',%3,'%4',%5,'%6')")
            .arg(_title,_text,QString::number(_type),_time,QString::number(_postId),_author_name);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;

}
//
//
//
bool database_interaction::insertData_Comment(QString _text,QString _author_name,QString _author_id,int _commentId,int _postId,QString _time)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into comment values('%1','%2','%3',%4,%5,'%6')")
            .arg(_text,_author_name,_author_id,QString::number(_commentId),QString::number(_postId),_time);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}
//
//
//
//



bool database_interaction::insertData_Associated_TagToPost(QString _postId, QString _tag)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into associated_tag_to_post values('%1','%2')").arg(_postId,_tag);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

bool database_interaction::insertData_Associated_UserToPost(QString _postId, QString _account)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into associated_user_to_post values('%1','%2')").arg(_postId,_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

bool database_interaction::updateData_PersonalInformation_Name(QString _account,QString _name)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("update personal_information set name=%1 where account=%2").arg(_name,_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

bool database_interaction::updateData_PersonalInformation_Password(QString _account, QString _password)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("update personal_information set password=%1 where account=%2").arg(_password,_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;

}

bool database_interaction::getCollectedPost(list<article_post*> &l, QString _account){
    QSqlQuery query(db);
    QString sqlSentence = QString("select * from article_post where postId in (select postId from associated_user_to_post where type = 1 and account = '%1')").arg(_account);
    query.exec(sqlSentence);
    int postNum=0;
    while(query.next())
    {
        article_post* ap=new article_post(
                    query.value(0).toString() ,
                    query.value(1).toString() ,
                    query.value(2).toInt(),
                    query.value(3).toString(),
                    query.value(4).toInt(),
                    query.value(5).toString()
                    );
        l.push_back(ap);
        postNum++;
    }
    if(postNum==0)return false;
    return true;
}

bool database_interaction::Fabulous_UserToPost(int _postId,QString _account)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("select * from associated_user_to_post where type = 0 and postId = %1 and account = '%2'").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<=0)return false;
    else return true;
}

bool database_interaction::Collect_UserToPost(int _postId,QString _account)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("select * from associated_user_to_post where type = 1 and postId = %1 and account = '%2'").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<=0)return false;
    else return true;
}

bool database_interaction::selectCount(int &a, int &b, int _postId){
    QSqlQuery query(db);
    QString sqlSentence=QString("select value from post_dynamic_properties where type = 0 and post_id = '%1'").arg(QString::number(_postId));
    query.exec(sqlSentence);
    while(query.next()){
        a = query.value(2).toInt();
    }
    sqlSentence=QString("select value from post_dynamic_properties where type = 1 and post_id = '%1'").arg(QString::number(_postId));
    query.exec(sqlSentence);
    while(query.next()){
        b = query.value(2).toInt();
    }
}

bool database_interaction::deleteData_Collect_UserToPost(int _postId,QString _account){
    QSqlQuery query(db);
    QString sqlSentence=QString("delete from associated_user_to_post where type = 1 and postId = %1 and account = '%2'").arg(QString::number(_postId),_account);
    qDebug()<<"sql:"<<sqlSentence;
    query.exec(sqlSentence);
    return true;
}

bool database_interaction::deleteData_Fabulous_UserToPost(int _postId,QString _account){
    QSqlQuery query(db);
    QString sqlSentence=QString("delete from associated_user_to_post where type = 0 and postId = %1 and account = '%2'").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
    return true;
}

bool database_interaction::insertData_Collect_UserToPost(int _postId,QString _account)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into associated_user_to_post values(%1,'%2',1)").arg(QString::number(_postId),_account);
    //qDebug()<<"sqlSentence:"<<sqlSentence;
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

bool database_interaction::insertData_Fabulous_UserToPost(int _postId,QString _account)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into associated_user_to_post values(%1,'%2',0)").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

article_postData* database_interaction::getPostInfo_PDPData(int postId)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("select * from post_dynamic_properties where post_id=%1").arg(QString::number(postId));
    query.exec(sqlSentence);
    int DataNum=0;
    article_postData *apd=new article_postData(-1,-1);
    while(query.next())
    {
        int type=query.value("type").toInt();
        int value=query.value("value").toInt();
        if(type==0){
           apd->thumbNum=value;
        }
        else if(type==1){
            apd->collectNum=value;
        }
        ++DataNum;
    }
    if(DataNum==0)return NULL;
    if(apd->collectNum==-1||apd->thumbNum==-1)return NULL;
    return apd;
}

QString database_interaction::getDate()
{
    QString date;
    QString time;
    QSqlQuery query(db);
    query.exec("Select CONVERT(varchar(100), GETDATE(), 112)");
    while(query.next()){date=query.value(0).toString();}
    query.clear();
    query.exec("Select CONVERT(varchar(100), GETDATE(), 24)");
    while(query.next()){time=query.value(0).toString();}
    time.replace(":","");
    date.append(time);
    return date;
}

bool database_interaction::isConnected()
{
    return isConnect;
}

int database_interaction::getNumberOf(QString source)
{
    QSqlQuery query(db);
    query.exec(QString("Select count(*) from %1").arg(source));
    while(query.next()){return query.value(0).toInt();}

}
