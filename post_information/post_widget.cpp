#include "post_widget.h"

post_widget::post_widget(article_post *_ap,QWidget *parent) : QWidget(parent)
//post_widget::post_widget(article_post *_ap)
{
    //绑定文章信息结构体
    ap=_ap;
    setMinimumSize(1010,70);
    setMaximumSize(1010,70);

    //根据绑定的文章更新信息
    updateInfo();

    label_author->setGeometry(20,10,60,30);
    label_text->setGeometry(120,10,900,20);
    label_time->setGeometry(860,40,81,16);

    //脱离父窗口样式
    this->setAttribute(Qt::WA_StyledBackground,true);
    //设置初始色
    this->setStyleSheet("background-color:rgb(255,255,255)");
    setAutoFillBackground(true);
    //setMouseTracking(true);

    pdi=new post_detailed_info(ap,parent);
}
bool post_widget::updateInfo()
{
    if(ap==NULL)return false;

    //根据绑定的文章显示信息
    label_author->setText(ap->author_name.mid(0,5));
    label_text->setText(ap->title.mid(0,50));

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

    label_time->setText(t);
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


