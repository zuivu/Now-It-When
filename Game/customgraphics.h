#ifndef CUSTOMGRAPHICS_H
#define CUSTOMGRAPHICS_H

#include <QGraphicsItem>
#include <core/location.hh>
#include <graphics/simpleactoritem.hh>

namespace GameImplementation {

class CustomGraphics : public CourseSide::SimpleActorItem
{
public:
    CustomGraphics() = delete;

    /**
      * @brief Constructor for the CustomGraphics
      * @param x x-coordinate of drone location
      * @param y y-coordinate of drone location
      * @param type type of graphics
      * @post Actor isn't in removed-state by default
      */
    CustomGraphics(int x, int y, int type);

    /**
      * @brief Overridden function from base class QGraphicsItem
      */
    QRectF boundingRect() const override;

    /**
      * @brief Overridden function from base class QGraphicsItem which is used to draw the graphics on a scene
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int x_;
    int y_;
    int type_;

    const int WIDTH = 5;
    const int HEIGHT = 5;
};

} // GameImplementation

#endif // CUSTOMGRAPHICS_H
