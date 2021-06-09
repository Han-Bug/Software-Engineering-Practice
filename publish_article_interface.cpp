#include "publish_article_interface.h"
#include "ui_publish_article_interface.h"

publish_article_interface::publish_article_interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::publish_article_interface)
{
    ui->setupUi(this);
    db=Data::dataBaseInter;

    ui->lineEdit->setPlaceholderText("请在此输入标题");
    ui->textEdit->setPlaceholderText("请在此输入正文");

}

publish_article_interface::~publish_article_interface()
{
    delete ui;
}

void publish_article_interface::setAuthor(QString _authorAccount,QString _authorName)
{
    authorAccount=_authorAccount;
    authorName=_authorName;
}

void publish_article_interface::on_pushButton_publish_clicked()
{
    QString title=ui->lineEdit->text();
    QString text=ui->textEdit->toPlainText();
    //合法性检验
    if(!vt.wordLimit(title,20)){
        QMessageBox errorMessageBox;
        errorMessageBox.setText("标题不能为空且不能超过20个字");
        errorMessageBox.exec();
        return;}
    else if(!vt.wordLimit(text,-1)){
        QMessageBox errorMessageBox;
        errorMessageBox.setText("正文不能为空");
        errorMessageBox.exec();
        return;}

    //(无限制)
    //

    if(!db->insertData_ArticlePost(ui->lineEdit->text(),
                               ui->textEdit->toPlainText(),
                               ui->comboBox_article_type->currentIndex(),
                               db->getDate(),
                               db->getNumberOf("article_post"),
                               authorName
                               ))
    {
        QMessageBox errorMessageBox;
        errorMessageBox.setText("发布失败！");
        errorMessageBox.exec();
        return;
    }
    QMessageBox mb;
    mb.setText("发布成功！");
    mb.exec();
    this->close();
}
