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
    if(!vt.IsDigit(_account,10))return 2;
    if(!vt.wordLimit(name,10))return 4;
    if(!vt.IsDigitAndWord(_password,10))return 3;
    if(_password!=_passwordConfirm)return 1;
    /// 0:合法
    /// 1:密码与确认密码不同
    /// 2:帐号非法
    /// 3:密码非法
    /// 4:名称非法
    ///
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
    /// 0:合法
    /// 1:密码与确认密码不同
    /// 2:帐号非法
    /// 3:密码非法
    /// 4:名称非法
    ///
    ///
    //此处跳过合法性验证
    //
    if(lr==0){
        if(db->insertData_PersonalInformation(ui->lineEdit_account->text(),ui->lineEdit_password->text(),ui->lineEdit_name->text()))
            ui->label_prompt_message->setText("注册成功!");
        else{ui->label_prompt_message->setText("已存在该帐号");}
    }
    else if(lr==1){
        ui->label_prompt_message->setText("密码与确认密码不同!");
    }
    else if(lr==2){
        ui->label_prompt_message->setText("帐号非法!");
    }
    else if(lr==3){
        ui->label_prompt_message->setText("密码非法!");
    }
    else if(lr==4){
        ui->label_prompt_message->setText("名称非法!");
    }
}
