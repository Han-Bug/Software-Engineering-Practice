#ifndef COMMENTS_WIDGET_H
#define COMMENTS_WIDGET_H

#include <QWidget>
#include <data_structs.h>
namespace Ui {
class comments_widget;
}

class comments_widget : public QWidget
{
    Q_OBJECT

public:
    explicit comments_widget(comment* cm,QWidget *parent = 0);
    ~comments_widget();
    comment* cm;
private:
    Ui::comments_widget *ui;
};

#endif // COMMENTS_WIDGET_H
