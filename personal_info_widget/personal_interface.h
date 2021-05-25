#ifndef PERSONAL_INTERFACE_H
#define PERSONAL_INTERFACE_H

#include <QWidget>
#include <data_structs.h>
#include "database_interaction/database_interaction.h"
#include "Search.h"

namespace Ui {
class personal_interface;
}

class personal_interface : public QWidget
{
    Q_OBJECT

public:
    explicit personal_interface(database_interaction *db,QWidget *parent = 0);

    void setPersonalInfo(personal_information *pi);
    void show_information();
    ~personal_interface();

private slots:

    void on_pushButton_Favorites_clicked();

private:
    Ui::personal_interface *ui;

private:
    database_interaction *db;
    personal_information *personalInfo=NULL;
    bool is_pi_available=false;
    Search* se;
};

#endif // PERSONAL_INTERFACE_H
