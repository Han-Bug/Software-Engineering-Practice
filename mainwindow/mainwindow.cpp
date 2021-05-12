#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(database_interaction *_db,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化子窗口
    this->db=_db;
    pi=new personal_interface(db);
    layout_post=new QVBoxLayout(ui->scrollAreaWidgetContents);
    layout_post->setSpacing(10);
    ui->scrollAreaWidgetContents->setMaximumWidth(ui->scrollArea->width());
    updatePost();

}

void MainWindow::setPersonalInfo(personal_information *pi)
{
    personalInfo=pi;
    if(personalInfo==NULL)ui->user->setText("点击登录");
    else ui->user->setText(personalInfo->name);
}

void MainWindow::updatePost(int type)
{
    for(int i=0;i<pw_v.size();i++){
        pw_v[i]->setParent(NULL);
        layout()->removeWidget(pw_v[i]);
    }

    //清除已有文章数据
    pw_v.clear();
    list<vector<QString>*> l;
    //根据文章类型获取指定文章，-1即获取所有文章
    if(type==-1)
        db->selectData(l,6,"article_post");
    else
        db->selectData(l,6,"article_post",QString("where type = %1").arg(QString::number(type)));
    while(l.size()!=0){
        vector<QString> &v=*l.front();
        article_post* ap=new article_post(v[0],v[1],v[2].toInt(),v[3],v[4].toInt(),v[5]);
        pw_v.push_back(new post_widget(ap));
        l.pop_front();
    }
    qDebug()<<pw_v.size();
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
    if(personalInfo==NULL){
        login_interface *li=new login_interface(db);
        li->exec();
        setPersonalInfo(li->personalInfo);
        pi->setPersonalInfo(personalInfo);
    }
    else pi->show();
}

void MainWindow::on_pushButton_publish_clicked()
{
    if(personalInfo==NULL){
        login_interface *li=new login_interface(db);
        li->exec();
        setPersonalInfo(li->personalInfo);
        pi->setPersonalInfo(personalInfo);
    }
    else{
        publish_article_interface *pai=new publish_article_interface(db);
        pai->setAuthor(personalInfo->account,personalInfo->name);
        pai->show();
    }
}

void MainWindow::on_pushButton_dailyShare_clicked()
{
    updatePost();
}
