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

    QColor color=QColor(0,200,150);
    QPainter painter(this);
    painter.setPen(QPen(color,0));

    if(tags.size()>0){
        for(int i=0;i<tags.size();i+=2){
            if(tags[i]==0){
                rectOffsetX=tags[i+1]*XOffSet;
            }else{
                QBrush brush;
                int dB=tags[i+1];
                if(dB<=20){
                    brush=QBrush(color,Qt::Dense6Pattern);
                }else if(dB<=40){
                    brush=QBrush(color,Qt::Dense5Pattern);
                }else if(dB<=80){
                    brush=QBrush(color,Qt::Dense4Pattern);
                }
                else if(dB<=100){
                    brush=QBrush(color,Qt::Dense3Pattern);
                }
                else if(dB<=120){
                    brush=QBrush(color,Qt::Dense2Pattern);
                }
                else if(dB<=140){
                    brush=QBrush(color,Qt::Dense1Pattern);
                }
                else{
                    brush=QBrush(color,Qt::SolidPattern);
                }

                painter.setBrush(brush);
                painter.drawRect(rectOffsetX,tags[i],XOffSet,XOffSet);
            }
        }
    }
}
