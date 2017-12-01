#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPen>
#include <QWidget>
#include <QMouseEvent>
#include<QImage>
#include<QLabel>
#include <QPainter>
#include <QPoint>
#include <vector>

class RenderArea:public QWidget
{
    Q_OBJECT

public:
    static RenderArea* getInstance();
    int height=50;
    int width=80;
    void SetPathPoint(std::vector<QPoint> newPath);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    RenderArea(QWidget *parent=0);
    static void Init();
};

#endif // RENDERAREA_H
