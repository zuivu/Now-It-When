#include "enemy.hh"

#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QDebug>

#include <errors/gameerror.hh>

namespace GameImplementation {

Enemy::Enemy(int x, int y) : CourseSide::SimpleActorItem(x, y)
{
    loc_.setXY(x, y);
    is_removed_ = false;
    setPos(mapToParent(x, y));
    installSceneEventFilter(this);
}

bool Enemy::isCloseToDrone(Interface::Location drone_loc)
{
    int hit_range = 32;
    return loc_.isClose(drone_loc, hit_range);
}

Interface::Location Enemy::getLocation()
{
    return loc_;
}

QRectF Enemy::boundingRect() const
{
    return QRectF(0, 0, 35, 19);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage image(":/graphics_items/graphic_items/small_plane.png", NULL);
    QRectF bounds = boundingRect();
    painter->drawImage(bounds, image, bounds);
}

Interface::Location Enemy::giveLocation() const
{
    return loc_;
}

void Enemy::move(Interface::Location loc)
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

bool Enemy::isRemoved() const
{
    return is_removed_;
}

void Enemy::remove()
{
    is_removed_ = true;
}

bool Enemy::should_move(QPointF pos, QRectF parent_bound)
{
    if(pos.x() > parent_bound.width() - boundingRect().width()) return false;
    if(pos.y() > parent_bound.height() - boundingRect().height()) return false;
    if(pos.x() < 0) return false;
    if(pos.y() < 0) return false;
    return true;
}

}
