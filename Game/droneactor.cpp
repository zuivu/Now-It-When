#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QDebug>

#include <errors/gameerror.hh>

#include "droneactor.h"

namespace GameImplementation {

DroneActor::DroneActor(int x, int y) : CourseSide::SimpleActorItem(x, y)
{
    loc_.setXY(x, y);
    is_removed_ = false;
    is_mouse_pressed_ = false;
    setPos(mapToParent(x, y));
    installSceneEventFilter(this);
}

bool DroneActor::is_dragging()
{
    return is_mouse_pressed_;
}

Interface::Location DroneActor::getLocation()
{
    return loc_;
}

QRectF DroneActor::boundingRect() const
{
    return QRectF(0, 0, 16, 19);
}

void DroneActor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage image(":/graphics_items/graphic_items/drone.png", NULL);
    QRectF bounds = boundingRect();
    painter->drawImage(bounds, image, bounds);
}

Interface::Location DroneActor::giveLocation() const
{
    return loc_;
}

void DroneActor::move(Interface::Location loc)
{
    QPointF point;
    point.setX(loc.giveX());
    point.setY(loc.giveY());
    QRectF bound(0,0,500,500);
    if(should_move(point, bound)){
        this->setX(loc.giveX());
        this->setY(loc.giveY());
        loc_ = loc;
    }
    else{
//        qDebug() << point.x();
//        qDebug() << point.y();
        throw Interface::GameError("Drone cannot move to specified location!");
    }
}

bool DroneActor::isRemoved() const
{
    return is_removed_;
}

void DroneActor::remove()
{
    is_removed_ = true;
}


bool DroneActor::sceneEvent(QEvent *ev)
{
    QGraphicsSceneMouseEvent* mouseEvent = (QGraphicsSceneMouseEvent*)ev;
    if (ev->type() == QEvent::GraphicsSceneMouseMove)
    {
        if(is_mouse_pressed_) {
            QPointF point = mouseEvent->scenePos();
            Interface::Location to_move;
            to_move.setXY(point.x(), point.y());
            try {
                move(to_move);
            }  catch (Interface::GameError ge) {
                qDebug() << ge.giveMessage();
            }
        }
    }
    if (ev->type() == QEvent::GrabMouse)
    {
        is_mouse_pressed_ = true;
    }
    if (ev->type() == QEvent::UngrabMouse)
    {
        is_mouse_pressed_ = false;
    }
    return false;
}

bool DroneActor::should_move(QPointF pos, QRectF parent_bound)
{
    if(pos.x() > parent_bound.width() - boundingRect().width()) return false;
    if(pos.y() > parent_bound.height() - boundingRect().height()) return false;
    if(pos.x() < 0) return false;
    if(pos.y() < 0) return false;
    return true;
}

} // GameImplementation
