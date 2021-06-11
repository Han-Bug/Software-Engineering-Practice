#include "ui_personal_interface.h"
#include "personal_interface.h"
personal_interface::personal_interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::personal_interface)
{
    ui->setupUi(this);
    db=Data::dataBaseInter;
    updateUser();
    se = new Search(db);
    updateUser();
}

void personal_interface::updateUser(){
    if(Data::personalInfo==NULL){
        return;
    }
    ui->label_account->setText(Data::personalInfo->account);
    ui->label_name->setText(Data::personalInfo->name);
}

personal_interface::~personal_interface()
{
    delete ui;
}
void personal_interface::on_pushButton_Favorites_clicked()
{
    list<article_post*> result;
    se->search2(result,Data::personalInfo->account);
    associated_interface* ai=new associated_interface(result);
    ai->setAttribute(Qt::WA_DeleteOnClose);
    ai->show();
}
//void personal_interface::setPersonalInfo(personal_information *pi)
//{
//    personalInfo=pi;
//    if(personalInfo!=NULL)is_pi_available=true;
//    show_information();
//}
