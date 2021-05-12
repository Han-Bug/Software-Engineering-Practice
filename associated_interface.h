#ifndef ASSOCIATED_INTERFACE_H
#define ASSOCIATED_INTERFACE_H

#include <QWidget>

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
    explicit associated_interface(database_interaction* _db,QWidget *parent = 0);
    ~associated_interface();
    void updateContent();
private:
    Ui::associated_interface *ui;

    database_interaction* db;
    //滚动界面布局
    QVBoxLayout *layout_content;

};

#endif // ASSOCIATED_INTERFACE_H
