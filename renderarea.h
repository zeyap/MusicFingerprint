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
    explicit RenderArea(QWidget *parent)
        : QWidget(parent)
    {
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);

    }

    void Init();

    void GetTag(std::vector<int> newTag);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    int rectOffsetX;
    std::vector<int> tags;
};

#endif // RENDERAREA_H
