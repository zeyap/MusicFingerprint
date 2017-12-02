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

    void GetTag(std::vector<int> newTag);
public slots:
    void Move(int x);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    RenderArea(QWidget *parent=0);
    static void Init();
    int rectOffsetX;
};

#endif // RENDERAREA_H
