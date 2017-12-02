#include "renderarea.h"

static std::vector<int> tags;
static RenderArea* renderArea;

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

}

RenderArea* RenderArea::getInstance(){
    if(renderArea==NULL){
        renderArea=new RenderArea;
        renderArea->Init();
    }
    return renderArea;
}

void RenderArea::Init(){
    tags.clear();
}


void RenderArea::mousePressEvent(QMouseEvent *event){
    //float x = event->pos().x();
    //float y=event->pos().y();

}

void RenderArea::GetTag(std::vector<int> newTag){

    tags.insert(tags.end(),newTag.begin(),newTag.end());
}


void RenderArea::paintEvent(QPaintEvent *){

    QColor black=QColor(0,0,0);
    QPainter painter(this);
    painter.setPen(QPen(black,0));

    if(tags.size()>0){
        for(int i=0;i<tags.size();i+=2){
            if(tags[i]==0){
                rectOffsetX=tags[i+1]*XOffSet;
            }else{
                QBrush brush;
                brush=QBrush(black,Qt::Dense5Pattern);
                painter.setBrush(brush);
                painter.drawRect(rectOffsetX,tags[i],XOffSet,XOffSet);
            }
        }
    }
}
