#include <QDebug>

#include "customgraphics.h"


GameImplementation::CustomGraphics::CustomGraphics(int x, int y, int type) : CourseSide::SimpleActorItem(x, y, type)
{
    x_ = x;
    y_ = y;
    type_ = type;
}

QRectF GameImplementation::CustomGraphics::boundingRect() const
{
    switch(type_) {
        case 0: // Bus
            return QRectF(0, 0, 19, 20);
        case 1: // Passenger
            return QRectF(0, 0, 5, 5);
        case 2: // Stop
            return QRectF(0, 0, 20, 20);
        default:
            return QRectF(0, 0, 0, 0);
    }

}

void GameImplementation::CustomGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch (type_) {
        case 0: { // Bus
//            qDebug() << "Drawing bus";
            QImage image(":/graphics_items/graphic_items/bus.png", NULL);
            QRectF bounds = boundingRect();
            painter->drawImage(bounds, image, bounds);
            break;
        }
        case 1: { // Passenger
//            qDebug() << "Drawing Passenger";
            QRectF bounds = boundingRect();
            QColor color(0, 255, 255);
            QBrush brush(color);
            painter->setBrush(brush);
            painter->drawEllipse(bounds);
            break;
        }
        case 2: { // Stop
//            qDebug() << "Drawing Stop";
        QImage image(":/graphics_items/graphic_items/busstop.png", NULL);
        QRectF bounds = boundingRect();
        painter->drawImage(bounds, image, bounds);
            break;
        }
    }
}
