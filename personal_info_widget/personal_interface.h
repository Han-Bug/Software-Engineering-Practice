#ifndef PERSONAL_INTERFACE_H
#define PERSONAL_INTERFACE_H

#include <QWidget>
#include <data_structs.h>
#include "database_interaction/database_interaction.h"

namespace Ui {
class personal_interface;
}

class personal_interface : public QWidget
{
    Q_OBJECT

public:
    explicit personal_interface(QWidget *parent = 0);

    //void setPersonalInfo(personal_information *pi);
    void updateUser();
    ~personal_interface();

private:
    Ui::personal_interface *ui;

private:
    database_interaction *db;
    //personal_information *personalInfo=NULL;
    //bool is_pi_available=false;
};

#endif // PERSONAL_INTERFACE_H
