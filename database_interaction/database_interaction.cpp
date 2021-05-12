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

QString database_interaction::getDate()
{
    QString date;
    QString time;
    QSqlQuery query(db);
    query.exec("Select CONVERT(varchar(100), GETDATE(), 112)");
    while(query.next()){date=query.value(0).toString();}
    //qDebug()<<"date= "<<date;
    query.clear();
    query.exec("Select CONVERT(varchar(100), GETDATE(), 24)");
    while(query.next()){time=query.value(0).toString();}
    time.replace(":","");
    //qDebug()<<"time= "<<time;
    date.append(time);
    return date;
}

int database_interaction::getNumberOf(QString source)
{
    QSqlQuery query(db);
    query.exec(QString("Select count(*) from %1").arg(source));
    while(query.next()){return query.value(0).toInt();}

}
