#include "comments_widget.h"
#include "ui_comments_widget.h"

comments_widget::comments_widget(comment *cm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comments_widget)
{
    ui->setupUi(this);
    this->cm=cm;
    ui->label_reviewer->setText(cm->author_name);
    ui->textBrowser->setText(cm->text);
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:rgb(255,255,255)");
}

comments_widget::~comments_widget()
{
    delete ui;
}
