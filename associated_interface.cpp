#include "associated_interface.h"
#include "ui_associated_interface.h"

associated_interface::associated_interface(database_interaction* _db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::associated_interface)
{
    ui->setupUi(this);
    db=_db;
    layout_content=new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setMaximumWidth(ui->scrollArea->width());
    updateContent();

}

associated_interface::~associated_interface()
{
    delete ui;
}

void associated_interface::updateContent()
{

}
