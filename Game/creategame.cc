#include <creategame.hh>
#include "city.hh"


std::shared_ptr<Interface::ICity> createGame(){
    std::shared_ptr<Interface::ICity> city = std::make_shared<GameImplementation::City>();
    return city;
}
