#ifndef publish_article_interface_H
#define publish_article_interface_H

#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <database_interaction/database_interaction.h>
namespace Ui {
class publish_article_interface;
}

class publish_article_interface : public QWidget
{
    Q_OBJECT

public:
    explicit publish_article_interface(QWidget *parent = 0);
    ~publish_article_interface();
    void setAuthor(QString _authorAccount,QString _authorName);
private slots:
    void on_pushButton_publish_clicked();

private:
    Ui::publish_article_interface *ui;
    database_interaction *db;
    validity_test vt;
    QString authorName;
    QString authorAccount;
};

#endif // publish_article_interface_H
