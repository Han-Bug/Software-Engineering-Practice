#ifndef POST_WIDGET__H
#define POST_WIDGET__H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QMouseEvent>

#include "data_structs.h"
#include "post_detailed_info.h"
#include "database_interaction/database_interaction.h"

namespace Ui {
class post_widget;
}

class post_widget : public QWidget
{
    Q_OBJECT
public:
    explicit post_widget(article_post *ap,QWidget *parent = nullptr);
    bool updateInfo();
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

    ~post_widget();

private:
    article_post *ap=NULL;
    post_detailed_info *pdi;
    database_interaction *db;
    article_postData *apd=NULL;

    Ui::post_widget *ui;
};

#endif // POST_WIDGET__H
