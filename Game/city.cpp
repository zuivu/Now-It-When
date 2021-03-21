#include "city.hh"
#include "actors/passenger.hh"
#include "actors/nysse.hh"
#include "errors/initerror.hh"
#include "customgraphics.h"
#include <algorithm>
#include <iostream>
#include <QDebug>

namespace GameImplementation {

City::City() :
    map_(nullptr),
    basic_background(":/offlinedata/offlinedata/kartta_pieni_500x500.png"),
    big_background("::/offlinedata/offlinedata/kartta_iso_1095x592.png"),
    time_(0,0,0),
    actors_({}),
    stops_({}),
    game_over_(false)
{
    setBackground(basic_background, big_background);
}

City::City(QGraphicsScene *mainwindow_map) :
    map_(mainwindow_map),
    basic_background(":/offlinedata/offlinedata/kartta_pieni_500x500.png"),
    big_background("::/offlinedata/offlinedata/kartta_iso_1095x592.png"),
    time_(0,0,0),
    actors_({}),
    stops_({}),
    game_over_(false)
{
    setBackground(basic_background, big_background);
}

std::shared_ptr<Interface::IActor> City::getActorByLocation(Interface::Location location)
{
    auto nearby = getNearbyActors(location);
    if(!nearby.empty()) {
        return nearby.at(0);
    }
    return nullptr;
}

void City::setIsGameOver(bool val)
{
    game_over_ = val;
}

void City::startGame()
{
    return;
}

void City::setClock(QTime clock)
{
    time_ = clock;
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    // Check if stop is null pointer
    if(stop == nullptr){
        qDebug() << "There's no new stop to add";
        return;
    }

    Interface::Location loc = stop->getLocation();
    auto graphic_stop = new GameImplementation::CustomGraphics(loc.giveX(), loc.giveY(), STOP);

    map_->addItem(graphic_stop);
    stops_.insert(std::make_pair(stop, graphic_stop));
}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    map_->setBackgroundBrush(basicbackground);
    //throw Interface::InitError("Background picture cannot be set!");
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    if(!newactor) {return;}
    Interface::Location loc = newactor->giveLocation();

    // Check type of actor and draw graphic here
    if (auto passenger = std::dynamic_pointer_cast<CourseSide::Passenger>(newactor)) {
        auto graphic_actor = new GameImplementation::CustomGraphics(loc.giveX(), loc.giveY(), PASSENGER);
        map_->addItem(graphic_actor);
        actors_.insert(std::make_pair(newactor, graphic_actor));
    }
    else if (auto vehicle = std::dynamic_pointer_cast<CourseSide::Nysse>(newactor)) {
        auto graphic_actor = new GameImplementation::CustomGraphics(loc.giveX(), loc.giveY(), BUS);
        map_->addItem(graphic_actor);
        actors_.insert(std::make_pair(newactor, graphic_actor));
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    auto to_remove = actors_[actor];
    if(to_remove){
        map_->removeItem(to_remove);
        actor->remove();
        actors_.erase(actor);
        delete to_remove;
    }
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    return (actors_.find(actor) != actors_.end());
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    actor->remove();
    actors_.erase(actor);
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor> > nearby_ = {};

    for (std::pair< std::shared_ptr<Interface::IActor>, QGraphicsItem* > actor_pair : actors_) {
        std::shared_ptr<Interface::IActor> actor = actor_pair.first;
        if (loc.isClose(actor_pair.first->giveLocation())) {
            nearby_.push_back(actor_pair.first);
        }
    }
    return nearby_;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    QGraphicsItem* graphic_actor = actors_.at(actor);
    Interface::Location new_loc = actor->giveLocation();
    int delta_x = new_loc.giveX() - graphic_actor->x();
    int delta_y = new_loc.giveY() - graphic_actor->y();
    graphic_actor->moveBy(delta_x, delta_y);
}

bool City::isGameOver() const
{
    return game_over_;
}

} // GameImplementation
