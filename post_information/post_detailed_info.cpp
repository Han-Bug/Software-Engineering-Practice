#include "post_detailed_info.h"
#include "ui_post_detailed_info.h"
#include "login_interface/login_interface.h"
#include<QPainter>

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
    bool num1,num2;
    num1 = db.Fabulous_UserToPost(ap->postId,login_interface::id);
    num2 = db.Collect_UserToPost(ap->postId,login_interface::id);
    ui->pushButton_thumb->show();
    ui->pushButton_Delthumb->show();
    ui->pushButton_collect->show();
    ui->pushButton_Delcollect->show();
    if(num1)//已经点赞
        ui->pushButton_thumb->hide();//显示取消点赞
    else
       ui->pushButton_Delthumb->hide();//显示点赞
    if(num2)//已经收藏
        ui->pushButton_collect->hide();//显示取消收藏
    else
        ui->pushButton_Delcollect->hide();//显示收藏
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

void post_detailed_info::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int a,b;
    db.selectCount(a,b,ap->postId);
    painter.drawText(670,60,"+"+QString::number(a));
    painter.drawText(780,60,"+"+QString::number(b));
}

void post_detailed_info::on_pushButton_thumb_clicked()//点赞
{
    ui->pushButton_thumb->hide();
    ui->pushButton_Delthumb->show();
    db.updateData_post_dynamic_properties_add(ap->postId,1);//点赞数++
    db.insertData_Fabulous_UserToPost(ap->postId,login_interface::id);
}

void post_detailed_info::on_pushButton_collect_clicked()//收藏
{
    ui->pushButton_collect->hide();
    ui->pushButton_Delcollect->show();
    db.updateData_post_dynamic_properties_add(ap->postId,2);//收藏数++
    db.insertData_Collect_UserToPost(ap->postId,login_interface::id);
}

void post_detailed_info::on_pushButton_Delthumb_clicked()//取消点赞
{

    ui->pushButton_thumb->show();
    ui->pushButton_Delthumb->hide();
    db.updateData_post_dynamic_properties_sub(ap->postId,1);//点赞数--
    db.deleteData_Fabulous_UserToPost(ap->postId,login_interface::id);
}

void post_detailed_info::on_pushButton_Delcollect_clicked()//取消收藏
{

    ui->pushButton_collect->show();
    ui->pushButton_Delcollect->hide();
    db.updateData_post_dynamic_properties_sub(ap->postId,2);//收藏数--
    db.deleteData_Collect_UserToPost(ap->postId,login_interface::id);
}
