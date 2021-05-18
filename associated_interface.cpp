#include "associated_interface.h"
#include "ui_associated_interface.h"

associated_interface::associated_interface(list<article_post *> &l, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::associated_interface)
{
    ui->setupUi(this);
    layout_content=new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setMaximumWidth(ui->scrollArea->width());
    //遍历链表，将链表内容添加至容器
    for(list<article_post *>::iterator it=l.begin();it!=l.end();it++){
        pw_v.push_back(new post_widget(*it));
    }
    for(int i=0;i<pw_v.size();i++){
        layout_content->addWidget(pw_v[i]);
    }
    //updateContent();

}
associated_interface::~associated_interface()
{
    delete ui;
}

