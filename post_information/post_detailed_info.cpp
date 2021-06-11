#include "post_detailed_info.h"
#include "ui_post_detailed_info.h"

post_detailed_info::post_detailed_info(article_post *_ap, article_postData *apd, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::post_detailed_info)
{
    ui->setupUi(this);
    ap=_ap;
    this->apd=apd;
    db=Data::dataBaseInter;
    pi=Data::personalInfo;

    //ui->textBrowser->setGeometry(this->width()/50,this->height()/10,this->width()*0.96,this->height()/8*7);
    //ui->label->setGeometry(this->width()/50,this->height()/40,this->width()*0.96,this->height()/20);
    QPalette pal =ui->textBrowser->palette();//添加背景图片
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/white.png")));
    setPalette(pal);
    QFont font( "YouYuan",15,75); //第一个属性是字体样式，第二个是大小，第三个是加粗（权重是75）
    ui->label->setFont(font);//title
    QFont fontt( "YouYuan",10,20); //第一个属性是字体样式，第二个是大小，第三个是加粗（权重是75）
    ui->textBrowser->setFont(fontt);
    ui->label_thumbNum->setStyleSheet ("QLabel { color: gray; text-decoration: underline; }");//灰色加下划线
    ui->label_collectNum->setStyleSheet ("QLabel { color: gray; text-decoration: underline; }");//灰色加下划线
    ui->label_author->setText("作者："+ap->author_name);
    ui->label_collectNum->setText("收藏:"+QString::number(apd->collectNum));
    ui->label_thumbNum->setText("点赞:"+QString::number(apd->thumbNum));

    ui->pushButton_thumb->show();
    ui->pushButton_collect->show();
    ui->pushButton_collect->setDisabled(true);
    ui->pushButton_thumb->setDisabled(true);

    layout=new QVBoxLayout(ui->scrollAreaWidgetContents);
    layout->setSpacing(10);

    updateInfo();
    updateComments();
}

bool post_detailed_info::updateInfo()
{
    if(ap==NULL)return false;
    ui->textBrowser->setText(ap->text);
    ui->label->setText(ap->title);

    if(Data::personalInfo!=NULL){
        bool num1,num2;
        ui->pushButton_collect->setDisabled(false);
        ui->pushButton_thumb->setDisabled(false);
        num1 = db->Fabulous_UserToPost(ap->postId,Data::personalInfo->account);
        num2 = db->Collect_UserToPost(ap->postId,Data::personalInfo->account);
        ui->pushButton_Delthumb->show();
        ui->pushButton_Delcollect->show();
        if(num1)//已经点赞
            ui->pushButton_thumb->hide();//显示取消点赞
        else
           ui->pushButton_Delthumb->hide();//显示点赞
        if(num2)//已经收藏
            ui->pushButton_collect->hide();//显示取消收藏
        else
            ui->pushButton_Delcollect->hide();//显示收藏
    }
    else{
    }
    if (Data::personalInfo == nullptr){
        ui->pushButton_thumb->hide();
        ui->pushButton_Delthumb->hide();
        ui->pushButton_collect->hide();
        ui->pushButton_Delcollect->hide();
    }
    return true;
}

bool post_detailed_info::updateComments()
{
    for(auto &w:com_widgets){
        w->close();
        layout->removeWidget(w);
    }

    //清除已有评论数据
    com_widgets.clear();
    list<comment*> l;
    //获取评论内容，-1即获取所有文章

    db->getComments(l,ap->postId,"000000000000","900000000000",-1);

    l.sort(compareCommentsByTime);
    while(l.size()!=0){
        comment* cm=l.front();
        comments_widget* cw=new comments_widget(cm);
        cw->setAttribute(Qt::WA_DeleteOnClose);
        com_widgets.push_back(cw);
        l.pop_front();
    }
    for(auto &w:com_widgets){
        layout->addWidget(w);
    }
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

void post_detailed_info::on_pushButton_thumb_clicked()//点赞
{
    ui->pushButton_thumb->hide();
    ui->pushButton_Delthumb->show();
    //db.updateData_post_dynamic_properties_add(ap->postId,1);//点赞数++
    qDebug()<<"insertData_thumb:"<<db->insertData_Fabulous_UserToPost(ap->postId,Data::personalInfo->account);
}

void post_detailed_info::on_pushButton_collect_clicked()//收藏
{
    ui->pushButton_collect->hide();
    ui->pushButton_Delcollect->show();
    //db.updateData_post_dynamic_properties_add(ap->postId,2);//收藏数++
    qDebug()<<"insertData_collect:"<<db->insertData_Collect_UserToPost(ap->postId,Data::personalInfo->account);
}

void post_detailed_info::on_pushButton_Delthumb_clicked()//取消点赞
{
    ui->pushButton_thumb->show();
    ui->pushButton_Delthumb->hide();
    //db.updateData_post_dynamic_properties_sub(ap->postId,1);//点赞数--
    db->deleteData_Fabulous_UserToPost(ap->postId,Data::personalInfo->account);
}

void post_detailed_info::on_pushButton_Delcollect_clicked()//取消收藏
{
    ui->pushButton_collect->show();
    ui->pushButton_Delcollect->hide();
    //db.updateData_post_dynamic_properties_sub(ap->postId,2);//收藏数--
    db->deleteData_Collect_UserToPost(ap->postId,Data::personalInfo->account);
}


//
//
//
//
//
void post_detailed_info::on_pushButton_comment_clicked()
{
    if(pi==NULL){
        QMessageBox mb;
        mb.setText("请先登录，再进行评论！");
        mb.exec();

    }
    else{
        comment_widget *pai=new comment_widget();
        pai->setAuthor(pi->account,pi->name);
        pai->setId(ap->postId);
        pai->show();
    }
}
//
//
//
//
//
//
