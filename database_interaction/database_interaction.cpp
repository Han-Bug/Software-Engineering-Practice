#include "database_interaction.h"
#define GET_ACCOUNT_BY_SQL "select "
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

bool database_interaction::getPostInfo_collect(list<article_post*> &l, QString _account){
    QSqlQuery query(db);
    QString sqlSentence = QString("select * from article_post where postId in (select postId from collect_user_to_post where account = '%1')").arg(_account);
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
// /////
bool database_interaction::Fabulous_UserToPost(int _postId,QString _account)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("select * from fabulous_user_to_post where postId = %1 and account = '%2'").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<=0)return false;
    else return true;
}

bool database_interaction::Collect_UserToPost(int _postId,QString _account)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("select * from collect_user_to_post where postId = %1 and account = '%2'").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<=0)return false;
    else return true;
}

bool database_interaction::selectCount(int &a, int &b, int _postId){
    QSqlQuery query(db);
    QString sqlSentence=QString("select fabulous,collect from post_dynamic_properties where postId = '%1'").arg(QString::number(_postId));
    query.exec(sqlSentence);
    while(query.next())
    {
        a = query.value(0).toInt();
        b = query.value(1).toInt();
    }
}

bool database_interaction::deleteData(QString sourse, QString limitStatement)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("delete from %1 %2").arg(sourse,limitStatement);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}
// ////
bool database_interaction::deleteData_Associated_UserToPost(int _postId,QString _account,int _type)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("delete from associated_user_to_post where postId='%1',account='%2',type='%3'").arg(QString::number(_postId),_account,QString::number(_type));
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

bool database_interaction::deleteData_Collect_UserToPost(int _postId,QString _account){
    QSqlQuery query(db);
    QString sqlSentence=QString("delete from collect_user_to_post where postId = %1 and account = '%2'").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
    return true;
}
bool database_interaction::deleteData_Fabulous_UserToPost(int _postId,QString _account){
    QSqlQuery query(db);
    QString sqlSentence=QString("delete from fabulous_user_to_post where postId = %1 and account = '%2'").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
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

bool database_interaction::insertData_Associated_TagToPost(int _postId, QString _tag)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into associated_tag_to_post values(%1,'%2')").arg(QString::number(_postId),_tag);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

bool database_interaction::insertData_Associated_UserToPost(int _postId, QString _account)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into associated_user_to_post values(%1,'%2')").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

bool database_interaction::insertData_Collect_UserToPost(int _postId,QString _account)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into collect_user_to_post values(%1,'%2')").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}
bool database_interaction::insertData_Fabulous_UserToPost(int _postId,QString _account)
{
    QSqlQuery query(db);
    QString sqlSentence=QString("insert into fabulous_user_to_post values(%1,'%2')").arg(QString::number(_postId),_account);
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}

// //////
bool database_interaction::insertData_post_dynamic_properties(int _post_id)//初始化点赞和收藏数
{
    QSqlQuery query(db);
    QString sqlSentence;
    int n = 0;
    sqlSentence=QString("insert into post_dynamic_properties values(%1,%2,%3)").arg(QString::number(_post_id),QString::number(n),QString::number(n));
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

// ///
bool database_interaction::updateData_post_dynamic_properties_add(int _post_id,int _type)//更新点赞收藏数
{
    QSqlQuery query(db);
    QString sqlSentence;
    if (_type==1)
        sqlSentence=QString("update post_dynamic_properties set fabulous=fabulous+1 where postId=%1").arg(QString::number(_post_id));
    else if (_type==2)
        sqlSentence=QString("update post_dynamic_properties set collect=collect+1 where postId=%1").arg(QString::number(_post_id));
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
}
bool database_interaction::updateData_post_dynamic_properties_sub(int _post_id,int _type)
{
    QSqlQuery query(db);
    QString sqlSentence;
    if (_type==1)
        sqlSentence=QString("update post_dynamic_properties set fabulous=fabulous-1 where postId=%1").arg(QString::number(_post_id));
    else if (_type==2)
        sqlSentence=QString("update post_dynamic_properties set collect=collect-1 where postId=%1").arg(QString::number(_post_id));
    query.exec(sqlSentence);
    if(query.numRowsAffected()<0)return false;
    return true;
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

int database_interaction::getNumberOf(QString source)
{
    QSqlQuery query(db);
    query.exec(QString("Select count(*) from %1").arg(source));
    while(query.next()){return query.value(0).toInt();}

}
