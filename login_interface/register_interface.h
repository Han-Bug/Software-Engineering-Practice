#ifndef REGISTER_INTERFACE_H
#define REGISTER_INTERFACE_H

#include <QWidget>
#include <QDialog>
#include <database_interaction/database_interaction.h>
#include "validity_test.h"
namespace Ui {
class register_interface;
}

class register_interface : public QDialog
{
    Q_OBJECT

public:
    explicit register_interface(QWidget *parent = 0);
    void cleanDataOfLine();
    int legalityReview(QString _account,QString _password,QString _passwordConfirm,QString name);
    ~register_interface();

private slots:
    void on_pushButton_sure_to_register_clicked();

private:
    Ui::register_interface *ui;

    database_interaction *db;
    validity_test vt;
};

#endif // REGISTER_INTERFACE_H
