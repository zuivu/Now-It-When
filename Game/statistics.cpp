#include "statistics.h"

namespace GameImplementation {

Statistics::Statistics()
{
    score_ = 0;
    num_nysse_ = 0;
}

int Statistics::getScore()
{
    return score_;
}

int Statistics::getnumNysse()
{
    return num_nysse_;
}

int Statistics::getNumPassengers()
{
    return num_passengers_;
}

void Statistics::morePassengers(int num)
{
    if (num > 0) {
        num_passengers_ += num;
    }
}

void Statistics::nysseRemoved()
{
    num_nysse_--;
    score_ += 10;
}

void Statistics::newNysse()
{
    num_nysse_++;
}

void Statistics::nysseLeft()
{
    num_nysse_--;
}

} // GameImplementation
