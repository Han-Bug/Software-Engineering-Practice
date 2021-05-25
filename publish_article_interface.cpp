#include "publish_article_interface.h"
#include "ui_publish_article_interface.h"
#include "mainwindow/mainwindow.h"

publish_article_interface::publish_article_interface(database_interaction *_db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::publish_article_interface)
{
    ui->setupUi(this);
    db=_db;
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
    //合法性检验
    //(无限制)
    //


    if(!db->insertData_ArticlePost(ui->lineEdit->text(),
                               ui->textEdit->toPlainText(),
                               ui->comboBox_article_type->currentIndex(),
                               db->getDate(),
                               //db->getNumberOf("article_post"),
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
    int postId=db->getNumberOf("article_post");
    db->insertData_post_dynamic_properties(postId,0,0);//初始化点赞数
    db->insertData_post_dynamic_properties( postId,1,0);//初始化收藏数
    mb.setText("发布成功！");
    mb.exec();


    this->close();
}
