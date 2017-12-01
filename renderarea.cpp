#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    pathPoints.push_back(QPoint(1,1));
    pathPoints.push_back(QPoint(10,10));

}


void RenderArea::mousePressEvent(QMouseEvent *event){
    //float x = event->pos().x();
    //float y=event->pos().y();

}

void RenderArea::SetPathPoint(std::vector<QPoint> newPath){

}


void RenderArea::paintEvent(QPaintEvent *){

    QColor black=QColor(0,0,0);
    QPainter painter(this);

    painter.setPen(QPen(black,0));

    QPainterPath path;

    for(int i=0;i<pathPoints.size();i++){
        path.lineTo(pathPoints[i]);
    }

    painter.drawPath(path);
}
