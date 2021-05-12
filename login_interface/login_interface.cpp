#include "login_interface.h"
#include "ui_login_interface.h"

login_interface::login_interface(database_interaction *_db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_interface)
{
    ui->setupUi(this);
    db=_db;
    this->personalInfo=NULL;
    //ri=new register_interface(db);
    ui->label_prompt_message->setStyleSheet("color: red");
    ui->label_prompt_message->clear();

}

login_interface::~login_interface()
{
    delete ui;
}
void login_interface::on_pushButton_login_in_clicked()
{
    //获取输入的帐号密码等信息
    list<vector<QString>*> l;
    QString limitStatement=QString("where account = %1 and password = %2")
            .arg(ui->lineEdit_account->text(),
                 ui->lineEdit_password->text());
    db->selectData(l,3,"personal_information",limitStatement);
    if(l.size()!=0){
        personalInfo=new personal_information((*l.front())[0],(*l.front())[1],(*l.front())[2]);
        close();
    }
    else{
        ui->label_prompt_message->setText("密码错误");
    }
}
void login_interface::on_lineEdit_account_returnPressed()
{

}

void login_interface::on_pushButton_register_clicked()
{
    register_interface *ri=new register_interface(db);
    ri->exec();
}
