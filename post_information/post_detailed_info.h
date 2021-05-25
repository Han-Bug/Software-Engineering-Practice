#ifndef POST_DETAILED_INFO_H
#define POST_DETAILED_INFO_H

#include <QWidget>
#include <QResizeEvent>
#include <QSize>
#include "data_structs.h"
#include "database_interaction/database_interaction.h"

namespace Ui {
class post_detailed_info;
}

class post_detailed_info : public QWidget
{
    Q_OBJECT
public:
    explicit post_detailed_info(article_post *ap,QWidget *parent = 0);
    bool updateInfo();
//    void resizeEvent(QResizeEvent *ev);
    ~post_detailed_info();

private slots:
    //void on_pushButton_Fabulous_clicked();

    //void on_pushButton_Collect_clicked();

    void on_pushButton_thumb_clicked();

    void on_pushButton_collect_clicked();

    void on_pushButton_Delthumb_clicked();

    void on_pushButton_Delcollect_clicked();

private:
    Ui::post_detailed_info *ui;
    article_post *ap=NULL;
};

#endif // POST_DETAILED_INFO_H
