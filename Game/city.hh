#ifndef CITY_HH
#define CITY_HH

#include <QObject>
#include <QPoint>
#include <QTime>
#include <QImage>
#include <QPainter>
#include <map>
#include "core/logic.hh"
#include "core/location.hh"
#include "interfaces/istop.hh"
#include "interfaces/iactor.hh"
#include "interfaces/icity.hh"
#include "graphics/simpleactoritem.hh"

namespace GameImplementation {

/**
* @brief City is a class, which handles the city's operations.
*/
class City : public Interface::ICity
{
public:
    City();

    /**
      * @brief Constructor of City
      * @param mainwindow_map pointer of map initialized from Mainwindow
      * @post City is at initialization state.
      */
    City(QGraphicsScene *mainwindow_map);

    /**
     * @brief getActorByLocation return the pointer the first actor of the list in the near range (<= 10) from the given location
     * @param location location on map we want to find a near actor
     * @pre -
     * @return pointer to the first actor of the list of actors from the range
     * @post Exception guarantee: nothrow
     */
    std::shared_ptr<Interface::IActor> getActorByLocation(Interface::Location location);

    /**
     * @brief setIsGameOver tell the game whether it's over according to boolean parameter val
     * @param val true if game is over, false otherwise
     * @post Exception guarantee: nothrow
     */
    void setIsGameOver(bool val);

    // Handle game interface

    /**
     * @brief Implement virtual function startGame just to not make this class as abstract
     * @pre -
     * @return -
     * @post Exception guarantee: nothrow.
     */
    void startGame() override;

    /**
     * @brief setClock sets the time of the game clock.
     * @param clock Game clock time at the function call.
     * @pre -
     * @post Time is set. Exception guarantee: nothrow.
     */
    void setClock(QTime clock) override;

    /**
     * @brief setBackground sets the bitmap picture of the game area.
     * @param basicbackground  Normal sized picture used as the game area. Bottom left position of the picture in pixelcoordinates can be found out using the offset()-method.
     * @param bigbackground  Background of the game that is bigger than normal. Used only if doing Scrolling map-expansion. Bottom left position of the picture in pixelcoordinates can be found out using the offset()-method.
     * @pre City is in init state.
     * @post Picture for the game area is set. Exception guarantee: nothrow.
     */
    void setBackground(QImage &basicbackground, QImage &bigbackground) override;

    /**
     * @brief addStop adds a stop to the city.
     * @param stop pointer to a stop object.
     * @pre City is in init state.
     * @post Stop is added to the city. Exception guarantee: nothrow
     */
    void addStop(std::shared_ptr<Interface::IStop> stop) override;

    /**
     * @brief isGameOver tells wether the game is overor not.
     * @pre City is in gamestate.
     * @return `true`, if game is over, else ´false´
     * @post Exception guarantee: nothrow.
     */
    bool isGameOver() const override;

    // Handle actors
    /**
     * @brief addActor adds a new actor to the city and draw it on the map
     * @param newactor actor to be added to the city that fulfills ActorIF.
     * @pre actor is not in the city
     * @post Actor is added to the city. Exception guarantee: nothrow
     */
    void addActor(std::shared_ptr<Interface::IActor> newactor) override;

    /**
     * @brief findActor checks if the given actor is in the city.
     * @param actor Actor that that is looked for in the city.
     * @pre -
     * @return Boolean that tells wether the actor is in the city.
     * @post Exception guarantee: nothrow.
     */
    bool findActor(std::shared_ptr<Interface::IActor> actor) const override;

    /**
     * @brief removeActor removes the actor from the city.
     * @param actor Actor to be removed.
     * @pre City is in gamestate.
     * @post Actor is removed from the city. Exception guarantee: strong
     */
    void removeActor(std::shared_ptr<Interface::IActor> actor) override;

    /**
     * @brief actorRemoved tells the city that actor is removed ingame.
     * @param actor Actor that is set removed ingame.
     * @pre City is in gamestate. Given actor is found in the city. Actor has `actor.isRemoved() == true`.
     * @post Exception guarantee: strong.
     */
    void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;

    /**
     * @brief actorMoved is an operation that is used to tell wether certain actor has moved.
     * @param actor Actor that has moved.
     * @pre City is in gamestate. Given actor is found in the city.
     * @post Exception guarantee: basic.
     */
    void actorMoved(std::shared_ptr<Interface::IActor> actor) override;

    /**
     * @brief getNearbyActors returns actors that are close to given position.
     * @param loc Location for getting the actors close to it.
     * @pre City is in gamestate.
     * @return Vector containing actors close to the location, that pass `getLocation().isClose(loc) == true`.
     * @post Exception guarantee: strong.
     */
    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const override;

private:
    QGraphicsScene *map_;
    QImage basic_background;
    QImage big_background;
    QTime time_;

    enum {BUS, PASSENGER, STOP};
    std::map< std::shared_ptr<Interface::IActor>, QGraphicsItem* > actors_;
    std::map< std::shared_ptr<Interface::IStop>, QGraphicsItem* > stops_;


    bool game_over_;
};

} // GameImplementation

#endif // CITY_HH
