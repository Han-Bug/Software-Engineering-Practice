#ifndef POST_DETAILED_INFO_H
#define POST_DETAILED_INFO_H

#include <QWidget>
#include <QResizeEvent>
#include <QSize>
#include <QVBoxLayout>
#include <list>
#include "data_structs.h"
//
//
//
#include <QMessageBox>
#include "database_interaction/database_interaction.h"
#include "comment/comment_widget.h"
#include "comment/comments_widget.h"
//
//
//
namespace Ui {
class post_detailed_info;
}

class post_detailed_info : public QWidget
{
    Q_OBJECT
public:
    explicit post_detailed_info(article_post *ap,article_postData *apd, QWidget *parent = 0);
    bool updateInfo();
    bool updateComments();
//    void resizeEvent(QResizeEvent *ev);
    ~post_detailed_info();

private slots:
    void on_pushButton_comment_clicked();
    void on_pushButton_thumb_clicked();

    void on_pushButton_Delthumb_clicked();

    void on_pushButton_Delcollect_clicked();

    void on_pushButton_collect_clicked();
private:
    Ui::post_detailed_info *ui;
    article_post *ap=NULL;
    QVBoxLayout *layout;
    database_interaction *db;
    personal_information *pi;
    article_postData *apd=NULL;
    QList<comments_widget*> com_widgets;
};

#endif // POST_DETAILED_INFO_H
