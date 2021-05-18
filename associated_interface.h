#ifndef ASSOCIATED_INTERFACE_H
#define ASSOCIATED_INTERFACE_H
using namespace  std;
#include <QWidget>
#include "post_information/post_widget.h"

#include "database_interaction/database_interaction.h"
#include "data_structs.h"
#include "post_information/post_widget.h"

namespace Ui {
class associated_interface;
}

class associated_interface : public QWidget
{
    Q_OBJECT

public:
    explicit associated_interface(list<article_post*> &l,QWidget *parent = 0);
    void fillInData();
    ~associated_interface();
private:
    Ui::associated_interface *ui;

    //滚动界面布局
    QVBoxLayout *layout_content;
    //文章小窗口容器
    vector<post_widget*> pw_v;


};

#endif // ASSOCIATED_INTERFACE_H
