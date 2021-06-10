#ifndef COMMENT_WIDGET_H
#define COMMENT_WIDGET_H

#include <QWidget>
#include "database_interaction/database_interaction.h"
namespace Ui {
class comment_widget;
}

class comment_widget : public QWidget
{
    Q_OBJECT

public:
    explicit comment_widget(QWidget *parent = nullptr);
    ~comment_widget();
    void setAuthor(QString _authorAccount,QString _authorName);//获取当前评论的用户的账号信息以及用户名称
    void setId(int _id);//获取当前评论的帖子的id

private slots:
    void on_pushButton_clicked();

private:
    Ui::comment_widget *ui;
    QString authorName;
    QString authorAccount;
    int id;
    database_interaction *db;
};

#endif // COMMENT_WIDGET_H
