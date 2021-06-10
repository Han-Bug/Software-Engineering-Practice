#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    db=Data::dataBaseInter;
    se=new Search(db);
    types=new bool[5];
    for(int i=0;i<5;i++)types[i]=true;
    ui->setupUi(this);
    //初始化子窗口
    pi=new personal_interface();
    layout_post=new QVBoxLayout(ui->scrollAreaWidgetContents);
    layout_post->setSpacing(10);
    ui->scrollAreaWidgetContents->setMaximumWidth(ui->scrollArea->width());
    updatePost();
}

void MainWindow::setUser()
{
    if(Data::personalInfo==NULL)ui->user->setText("点击登录");
    else ui->user->setText(Data::personalInfo->name);
}

void MainWindow::updatePost()
{
    for(int i=0;i<pw_v.size();i++){
        pw_v[i]->close();
        layout()->removeWidget(pw_v[i]);
    }

    //清除已有文章数据
    pw_v.clear();
    list<article_post*> l;
    //根据文章类型获取指定文章，-1即获取所有文章
    for(int i=0;i<5;i++){
        if(types[i])db->getPostInfo(l,i,"000000000000","900000000000",-1);
    }
    l.sort(comparePostsByTime);
    while(l.size()!=0){
        article_post* ap=l.front();
        post_widget* pw=new post_widget(ap);
        pw->setAttribute(Qt::WA_DeleteOnClose);
        pw_v.push_back(pw);
        l.pop_front();
    }

    //qDebug()<<pw_v.size();
    for(int i=0;i<pw_v.size();i++){
        layout_post->addWidget(pw_v[i]);
    }

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_user_clicked()
{
    if(Data::personalInfo==NULL){
        login_interface *li=new login_interface();
        li->exec();
        setUser();
        updatePost();
        pi->updateUser();
        //pi->setPersonalInfo(personalInfo);
    }
    else pi->show();
}

void MainWindow::on_pushButton_publish_clicked()
{
    if(Data::personalInfo==NULL){
        login_interface *li=new login_interface();
        li->exec();
        setUser();
        updatePost();
    }
    else{
        publish_article_interface *pai=new publish_article_interface();
        pai->setAuthor(Data::personalInfo->account,Data::personalInfo->name);
        pai->show();
    }
}


void MainWindow::on_pushButton_doSearch_clicked()
{
    list<article_post*> result;
    se->search(ui->lineEdit_search->text(),result);
    //qDebug()<<ui->lineEdit_search->text();
    associated_interface* ai=new associated_interface(result);
    ai->setAttribute(Qt::WA_DeleteOnClose);
    ai->show();

}

void MainWindow::on_pushButton_dailyShare_clicked(bool checked)
{
    if(checked)types[0]=true;
    else types[0]=false;
    updatePost();

}

void MainWindow::on_pushButton_forOrders_clicked(bool checked)
{
    if(checked)types[1]=true;
    else types[1]=false;
    updatePost();
}

void MainWindow::on_pushButton_lostAndFound_clicked(bool checked)
{
    if(checked)types[2]=true;
    else types[2]=false;
    updatePost();

}

void MainWindow::on_pushButton_expExchange_clicked(bool checked)
{
    if(checked)types[3]=true;
    else types[3]=false;
    updatePost();

}


void MainWindow::on_pushButton_secondaryMarket_clicked(bool checked)
{
    if(checked)types[4]=true;
    else types[4]=false;
    updatePost();
}
