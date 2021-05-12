#include "ui_personal_interface.h"
#include "personal_interface.h"
personal_interface::personal_interface(database_interaction *_db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::personal_interface)
{
    ui->setupUi(this);
    this->db=_db;

}

void personal_interface::show_information(){
    if(!is_pi_available){
        return;
    }
    ui->label_account->setText(personalInfo->account);
    ui->label_name->setText(personalInfo->name);
}

personal_interface::~personal_interface()
{
    delete ui;
}

void personal_interface::setPersonalInfo(personal_information *pi)
{
    personalInfo=pi;
    if(personalInfo!=NULL)is_pi_available=true;
    show_information();
}
