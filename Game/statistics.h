#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include "interfaces/istatistics.hh"

namespace GameImplementation {
/**
 * @brief Statistics is a class, which defines an object that manages scoring statistics.
 */
class Statistics : public Interface::IStatistics
{
public:
    /**
      * @brief Default constructor for the Interface.
      * @post Scores are reset by default.
      */
    Statistics();

    /**
      * @brief Returns curent game score
      * @post Exception guarantee: noexcept
      */
    int getScore();

    /**
      * @brief Returns curent number of busses used for score calculation
      * @post Exception guarantee: noexcept
      */
    int getnumNysse();

    /**
      * @brief Returns curent number of passengers used for score calculation
      * @post Exception guarantee: noexcept
      */
    int getNumPassengers();

    /**
     * @brief morePassengers notifies, that more passangers are added to the game.
     * @param num how many new passangers are added.
     * @pre num > 0
     * @post Exception guarantee: noexcept
     */
    void morePassengers(int num) override;

    /**
     * @brief nysseRemoved notifies, that the nysse is removed ingame.
     * @pre -
     * @post Exception guarantee: noexcept
     */
    void nysseRemoved() override;

    /**
     * @brief newNysse notifies, that a new nysse is added to the game.
     * @pre -
     * @post Exception guarantee: noexcept
     */
    void newNysse() override;

    /**
     * @brief nysseLeft notifies, that a nysse has left the game.
     * @pre -
     * @post Exception guarantee: noexcept
     */
    void nysseLeft() override;

private:
    // The score variable to keep game score
    int score_;

    // The number of busses to keep game score
    int num_nysse_;

    // The number of passengers to keep game score
    int num_passengers_;
};

} // GameImplementation

#endif // STATISTICS_H
