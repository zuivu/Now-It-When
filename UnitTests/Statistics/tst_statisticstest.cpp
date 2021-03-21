#include <QtTest>
#include "statistics.h"

class StatisticTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testCreateStatistic();
    void testGetScore();
    void testgetNumNysse();
    void testgetNumPassengers();
    void testMorePassengers();
    void testNysseRemoved();
    void testNewNysse();
    void testNysseLeft();
};


void StatisticTest::testCreateStatistic()
{
    GameImplementation::Statistics stat;
    QCOMPARE(stat.getScore(), 0);
    QCOMPARE(stat.getnumNysse(), 0);
    QCOMPARE(stat.getNumPassengers(), 0);
}

void StatisticTest::testGetScore()
{
    GameImplementation::Statistics stat;
    stat.nysseRemoved();
    stat.nysseRemoved();
    QCOMPARE(stat.getScore(), 20);
}

void StatisticTest::testgetNumNysse()
{
    GameImplementation::Statistics stat;
    stat.newNysse();
    stat.nysseRemoved();
    QCOMPARE(stat.getnumNysse(), 0);

    stat.newNysse();
    stat.newNysse();
    stat.nysseLeft();
    QCOMPARE(stat.getnumNysse(), 1);

    stat.newNysse();
    stat.newNysse();
    QCOMPARE(stat.getnumNysse(), 3);
}

void StatisticTest::testgetNumPassengers()
{
    GameImplementation::Statistics stat;

    for ( int i = 0; i < 3; i++) {
        stat.morePassengers(i*2);
    }

    QCOMPARE(stat.getNumPassengers(), 6);
}

void StatisticTest::testMorePassengers()
{
    GameImplementation::Statistics stat;

    // Positive adding
    stat.morePassengers(3);
    QCOMPARE(stat.getNumPassengers(), 3);

    // Negative adding
    stat.morePassengers(-20);
    QCOMPARE(stat.getNumPassengers(), 3);

    // No new adding
    stat.morePassengers(0);
    QCOMPARE(stat.getNumPassengers(), 3);
}


void StatisticTest::testNysseRemoved()
{
    GameImplementation::Statistics stat;

    for ( int i = 0; i < 10; i++) {
        stat.newNysse();
    }

    for ( int i = 0; i < 3; i++) {
        stat.nysseRemoved();
        stat.newNysse();
    }

    for ( int i = 0; i < 2; i++) {
        stat.nysseRemoved();
    }

    QCOMPARE(stat.getnumNysse(), 8);
    QCOMPARE(stat.getScore(), 5);
}

void StatisticTest::testNewNysse()
{
    GameImplementation::Statistics stat;

    for ( int i = 0; i < 6; i++) {
        stat.newNysse();
    }

    QCOMPARE(stat.getnumNysse(), 6);
}

void StatisticTest::testNysseLeft()
{
    GameImplementation::Statistics stat;

    for ( int i = 0; i < 10; i++) {
        stat.newNysse();
    }

    for ( int i = 0; i < 3; i++) {
        stat.nysseLeft();
    }

    QCOMPARE(stat.getnumNysse(), 7);
}

QTEST_APPLESS_MAIN(StatisticTest)

#include "tst_statisticstest.moc"
