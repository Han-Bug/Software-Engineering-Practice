#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H
#include <QString>
#include <list>
#include <vector>

struct personal_information
{
    QString account;
    QString password;
    QString name;
    personal_information(QString _account,QString _password,QString _name){
        account=_account;
        password=_password;
        name=_name;
    }
};
struct associated_user_to_post
{
    QString postId;
    QString account;
    associated_user_to_post(QString _postId,QString _account){
        postId=_postId;
        account=_account;
    }
};
struct article_post
{
    QString title;
    QString text;
    int type;
    QString time;
    int postId;
    QString author_name;
    article_post(QString _title,QString _text,int _type,QString _time,int _postId,QString _author_name){
        title=_title;
        text=_text;
        type=_type;
        time=_time;
        postId=_postId;
        author_name=_author_name;
    }
};
struct associated_tag_to_post
{
    QString postId;
    QString tag;
    associated_tag_to_post(QString _postId,QString _tag){
        postId=_postId;
        tag=_tag;
    }
};
//降序
static bool compareArticalPostByTime(article_post* a,article_post* b){
    return a->time.toLongLong()>b->time.toLongLong();
}

#endif // DATA_STRUCTS_H
