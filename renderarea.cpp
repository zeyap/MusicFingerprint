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

    QColor c1=QColor(100,70,60);
    QColor c2=QColor(200,90,63);
    QColor c3=QColor(242,117,63);
    QColor c4=QColor(242,159,63);
    QColor c5=QColor(255,233,87);
    QColor c6=QColor(255,255,150);
    QColor c7=QColor(240,255,200);
    QPainter painter(this);

    int w,h;
    w=tags.size()/12*XOffSet;
    h=300;

    painter.setWindow(w*0.005,0,w*1.01,h*1.16);

    if(tags.size()>0){
        for(int i=0;i<tags.size();i+=2){
            if(tags[i]==0){
                rectOffsetX=tags[i+1]*XOffSet;
            }else{
                QBrush brush;
                QPen pen;
                int dB=tags[i+1];
                if(dB<=20){
                    pen=QPen(c7);
                    brush=QBrush(c7,Qt::SolidPattern);
                }else if(dB<=40){
                    pen=QPen(c6);
                    brush=QBrush(c6,Qt::SolidPattern);
                }else if(dB<=80){
                    pen=QPen(c5);
                    brush=QBrush(c5,Qt::SolidPattern);
                }
                else if(dB<=100){
                    pen=QPen(c4);
                    brush=QBrush(c4,Qt::SolidPattern);
                }
                else if(dB<=120){
                    pen=QPen(c3);
                    brush=QBrush(c3,Qt::SolidPattern);
                }
                else if(dB<=140){
                    pen=QPen(c2);
                    brush=QBrush(c2,Qt::SolidPattern);
                }
                else{
                    pen=QPen(c1);
                    brush=QBrush(c1,Qt::SolidPattern);
                }

                painter.setBrush(brush);
                painter.setPen(pen);

                painter.drawRect(rectOffsetX,tags[i],XOffSet,XOffSet);
            }
        }
    }
}
