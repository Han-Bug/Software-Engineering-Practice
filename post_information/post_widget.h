#ifndef POST_WIDGET_H
#define POST_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QMouseEvent>

#include "data_structs.h"
#include "post_detailed_info.h"

class post_widget : public QWidget
{
    Q_OBJECT
public:
    explicit post_widget(article_post *ap,QWidget *parent = nullptr);
    //post_widget(article_post *ap);
    //更新窗口内容
    bool updateInfo();

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);


signals:

private:
    article_post *ap=NULL;

    post_detailed_info *pdi;
    QLabel *label_author=new QLabel(this);
    QLabel *label_text=new QLabel(this);
    QLabel *label_time=new QLabel(this);
public slots:
};

#endif // POST_WIDGET_H
