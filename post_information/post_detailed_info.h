#ifndef POST_DETAILED_INFO_H
#define POST_DETAILED_INFO_H

#include <QWidget>
#include <QResizeEvent>
#include <QSize>
#include "data_structs.h"

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

private:
    Ui::post_detailed_info *ui;
    article_post *ap=NULL;
};

#endif // POST_DETAILED_INFO_H
