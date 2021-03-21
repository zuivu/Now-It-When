#ifndef ENEMY_HH
#define ENEMY_HH

#include <QObject>
#include <QPoint>
#include <QPainter>
#include <qgraphicsitem.h>
#include <interfaces/iactor.hh>
#include <graphics/simpleactoritem.hh>
#include <core/location.hh>

namespace GameImplementation {

/**
 * @brief Enemy is a class, which DroneActor have to avoid
 */
class Enemy : public CourseSide::SimpleActorItem, public Interface::IActor
{
public:
    Enemy() = delete;
    /**
      * @brief Constructor for the Enemy
      * @param x x-coordinate of drone location
      * @param y y-coordinate of drone location
      * @post Actor isn't in removed-state by default
      */
    Enemy(int x, int y);

    /**
      * @brief isCloseToDrone check whether Enemy object is so closed to Drone actor that could make the game over
      * pre game is playing
      * @param drone_loc drone's location
      * @post game is over
      */
    bool isCloseToDrone(Interface::Location drone_loc);

    /**
      * @brief getLocation returns the current Enemy location
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
    bool should_move(QPointF pos, QRectF bound);

    Interface::Location loc_;
    bool is_removed_;
};

}
#endif // ENEMY_HH
