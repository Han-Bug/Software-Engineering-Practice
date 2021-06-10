#include "comment_widget.h"
#include "ui_comment_widget.h"

comment_widget::comment_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comment_widget)
{
    ui->setupUi(this);
    db=Data::dataBaseInter;

}

comment_widget::~comment_widget()
{
    delete ui;
}
void comment_widget::setAuthor(QString _authorAccount, QString _authorName)
{
    authorAccount=_authorAccount;
    authorName=_authorName;
}
void comment_widget::setId(int _id)
{
    id=_id;
}


void comment_widget::on_pushButton_clicked()
{
    if(!db->insertData_Comment(ui->textEdit->toPlainText(),
                               authorName,
                               authorAccount,
                               db->getNumberOf("comment"),
                               id,
                               db->getDate()
                               ))
    {
        QMessageBox errorMessageBox;
        errorMessageBox.setText("评论失败！");
        errorMessageBox.exec();
        return;
    }
    QMessageBox mb;
    mb.setText("评论成功！");
    mb.exec();
    this->close();
}
