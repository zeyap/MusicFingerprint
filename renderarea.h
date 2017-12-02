#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <main.h>

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
    static void Init();

    void GetTag(std::vector<int> newTag);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    RenderArea(QWidget *parent=0);
    int rectOffsetX;
};

#endif // RENDERAREA_H
