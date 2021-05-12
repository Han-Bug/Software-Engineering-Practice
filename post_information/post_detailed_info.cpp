#include "post_detailed_info.h"
#include "ui_post_detailed_info.h"

post_detailed_info::post_detailed_info(article_post *_ap,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::post_detailed_info)
{
    ui->setupUi(this);
    ap=_ap;
    ui->textBrowser->setGeometry(this->width()/50,this->height()/10,this->width()*0.96,this->height()/8*7);
    ui->label->setGeometry(this->width()/50,this->height()/40,this->width()*0.96,this->height()/20);
    updateInfo();
}

bool post_detailed_info::updateInfo()
{
    if(ap==NULL)return false;
    ui->textBrowser->setText(ap->text);
    ui->label->setText(ap->title);
    return true;
}

//void post_detailed_info::resizeEvent(QResizeEvent *ev)
//{
//    QSize oldSize,newSize;
//    //获取开始的size
//    oldSize = ev->oldSize();
//    //获取现在的size
//    newSize = ev->size();
//    //获取长宽变化的比率
//    qreal ratioW,ratioH;
//    ratioW = newSize.width()/oldSize.width();
//    ratioH = newSize.height()/oldSize.height();
//    ui->textBrowser->resize(QSize(ui->textBrowser->size().width()*ratioW,
//                                  ui->textBrowser->size().height()*ratioH));
//    ui->label->resize(QSize(ui->label->size().width()*ratioW,
//                            ui->label->size().height()*ratioH));
//}

post_detailed_info::~post_detailed_info()
{
    delete ui;
}
