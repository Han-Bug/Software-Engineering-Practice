#include "post_widget.h"
#include "ui_post_widget.h"

post_widget::post_widget(article_post *ap,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::post_widget)
{
    ui->setupUi(this);

    this->ap=ap;

    QFont font( "Microsoft YaHei",10,75); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）  字体样式设计
    ui->label_author->setFont(font);
    ui->label_time->setStyleSheet ("QLabel { color: green; text-decoration: underline; }");//绿色加下划线
    ui->label_thumbNum->setStyleSheet ("QLabel { color: gray; text-decoration: underline; }");//灰色加下划线
    ui->label_collectNum->setStyleSheet ("QLabel { color: gray; text-decoration: underline; }");//灰色加下划线
    ui->label_title->setStyleSheet("QLabel{background-color:rgb(251,251,251);}");  //设置样式表

    //脱离父窗口样式
    this->setAttribute(Qt::WA_StyledBackground,true);
    //设置初始色
    this->setStyleSheet("background-color:rgb(255,255,255)");
    setAutoFillBackground(true);
    //setMouseTracking(true);
    apd=Data::dataBaseInter->getPostInfo_PDPData(ap->postId);
    pdi=new post_detailed_info(ap,apd,parent);

    updateInfo();
}

post_widget::~post_widget()
{
    delete ui;
}
bool post_widget::updateInfo()
{
    if(ap==NULL)return false;

    //根据绑定的文章显示信息
    QString typeName;
    if(ap->type==0)typeName="日常分享";
    else if(ap->type==1)typeName="悬赏接单";
    else if(ap->type==2)typeName="失物招领";
    else if(ap->type==3)typeName="经验交流";
    else if(ap->type==4)typeName="二手市场";
    ui->label_type->setText(typeName);
    ui->label_author->setText(ap->author_name.mid(0,5));
    ui->label_title->setText(ap->title.mid(0,50));
    ui->label_thumbNum->setText("点赞数："+QString::number(apd->thumbNum));
    ui->label_collectNum->setText("收藏数："+QString::number(apd->collectNum));
    //日期规范化显示：
    QString t_year="    ";
    QString t_month="  ";
    QString t_day="  ";

    //获取年月日
    for(int y=0;y<4;y++){
        t_year[y]=ap->time[y];
    }
    for(int m=0;m<2;m++){
        t_month[m]=ap->time[m+4];
    }
    for(int d=0;d<2;d++){
        t_day[d]=ap->time[d+6];
    }

    //将20210101显示为2021.01.01
    QString t="";
    t.append(t_year);
    t.append(".");
    t.append(t_month);
    t.append(".");
    t.append(t_day);

    ui->label_time->setText(t);
    return true;
}
void post_widget::enterEvent(QEvent *){
    if(ap==NULL)return ;
    this->setStyleSheet("background-color:rgb(240,248,255)");
}
void post_widget::leaveEvent(QEvent *){
    if(ap==NULL)return ;
    this->setStyleSheet("background-color:rgb(255,255,255)");
}
void post_widget::mousePressEvent(QMouseEvent *e){
    if(ap==NULL)return ;
    if(e->button())this->setStyleSheet("background-color:rgb(176,196,222)");
}

void post_widget::mouseReleaseEvent(QMouseEvent *e){
    if(ap==NULL)return ;
    if(e->button())this->setStyleSheet("background-color:rgb(240,248,255)");
    //pdi->setAttribute(Qt::WA_DeleteOnClose);
    pdi->show();

}

