#include "register_interface.h"
#include "ui_register_interface.h"

register_interface::register_interface(database_interaction *_db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_interface)
{
    ui->setupUi(this);
    db=_db;
    ui->label_prompt_message->setStyleSheet("color: red");
    cleanDataOfLine();
}

void register_interface::cleanDataOfLine()
{
    ui->lineEdit_account->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_password_confirm->clear();
    ui->label_prompt_message->clear();
}

int register_interface::legalityReview(QString _account, QString _password, QString _passwordConfirm, QString name)
{
    /// 0:合法
    /// 1:密码与确认密码不同
    /// 2:帐号非法
    /// 3:密码非法
    /// 4:名称非法
    return 0;
}

register_interface::~register_interface()
{
    delete ui;
}

void register_interface::on_pushButton_sure_to_register_clicked()
{
    //帐号判断
    int lr=legalityReview(ui->lineEdit_account->text(),
                   ui->lineEdit_password->text(),
                   ui->lineEdit_password_confirm->text(),
                   ui->lineEdit_name->text()
                   );
    if(lr==0){
        if(db->insertData_PersonalInformation(ui->lineEdit_account->text(),ui->lineEdit_password->text(),ui->lineEdit_name->text()))
            ui->label_prompt_message->setText("注册成功!");
        else{ui->label_prompt_message->setText("注册失败!");}
    }
    else if(lr==1){

    }
    else if(lr==2){

    }
    else if(lr==3){

    }
    else if(lr==4){

    }
}
