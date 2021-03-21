#ifndef DRONEACTOR_H
#define DRONEACTOR_H

#include <QObject>
#include <QPoint>
#include <QPainter>
#include <qgraphicsitem.h>
#include <interfaces/iactor.hh>
#include <graphics/simpleactoritem.hh>
#include <core/location.hh>

namespace GameImplementation {

/**
 * @brief DroneActor is a class, which every implements the drone in the game.
 */
class DroneActor : public CourseSide::SimpleActorItem, public Interface::IActor
{
public:
    DroneActor() = delete;

    /**
      * @brief Constructor for the DroneActor
      * @param x x-coordinate of drone location
      * @param y y-coordinate of drone location
      * @post Actor isn't in removed-state by default
      */
    DroneActor(int x, int y);

    /**
      * @brief The function returns if the mouse is clicked over drone actor
      * @post noexcept
      */
    bool is_dragging();

    /**
      * @brief getLocation returns the current drone location
      * @post noexcept
      */
    Interface::Location getLocation();

    /**
      * @brief Overridden function from base class QGraphicsItem
      */
    QRectF boundingRect() const override;

    /**
      * @brief Overridden function from base class QGraphicsItem which is used to draw the drone on a scene
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief giveLocation returns the location of the actor.
     * @pre -
     * @return Actors location.
     * @post Exception guarantee: strong.
     */
    Interface::Location giveLocation() const override;

    /**
     * @brief move-method moves the actor to given location.
     * @param loc Actors new location.
     * @pre -
     * @post Actors location is sij. Excaption guarantee: strong.
     * @exception GameError Location is not possible.
     */
    void move(Interface::Location loc) override;

    /**
     * @brief isRemoved tells if the actor is removed ingame.
     * @pre -
     * @return `true`, if actor is removed ingame, otherwise `false`.
     * @post Exception guarantee: nothrow.
     */
    bool isRemoved() const override;

    /**
     * @brief remove marks the actor as removed.
     * @pre Actor is not removed already.
     * @post Actor is removed, after this isRemoved() returns `true`. Exception guarantee: basic.
     */
    void remove() override;


private:
    virtual bool sceneEvent(QEvent *ev) override;
    bool should_move(QPointF pos, QRectF bound);

    Interface::Location loc_;
    bool is_removed_;
    bool is_mouse_pressed_;
};

} // GameImplementation

#endif // DRONEACTOR_H
