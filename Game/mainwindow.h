#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTime>
#include <QTimer>

#include <core/logic.hh>
#include <graphics/simpleactoritem.hh>

#include "droneactor.h"
#include "enemy.hh"
#include "statistics.h"
#include "askinfo.hh"
#include "city.hh"

using namespace GameImplementation;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
      * @brief Constructor for the MainWindow
      * @post MainWindow is created
      */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
      * @brief Destructor for the MainWindow
      * @post MainWindow is destroyed
      */
    ~MainWindow();

    /**
      * @brief setSize sets the size of mainwindow
      * @param w is width of said size
      * @param h is height of said size
      * @post MainWindow is resized
      */
    void setSize(int w, int h);

    /**
      * @brief addDrone adds a drone in scene
      * @param locX is x-coordinate of drone location
      * @param locY is y-coordinate of drone location
      * @post Exception guarantee weak
      */
    void addDrone(int locX, int locY);

    /**
      * @brief addEnemy adds an enemy in scene
      * @param locX is x-coordinate of enemy location
      * @param locY is y-coordinate of enemy location
      * @post Exception guarantee weak
      */
    void addEnemy(int locX, int locY);

    /**
      * @brief chasingDrone let the enemy chasing the drone
      * @param drone_loc is drone location
      * @post Exception: nothrow
      */
    void chasingDrone(Interface::Location drone_loc);

    /**
      * @brief createScene creates the game scene
      * @post Exception guarantee weak
      */
    void createScene();

    /**
      * @brief startGame initializes the game scene and logic to start the game
      * @post Exception guarantee weak
      */
    void startGame();

private slots:

    /**
      * @brief on_start_button_clicked is the slot for start button clicked from the main window
      * @post A dialog window is opened
      */
    void on_start_button_clicked();

    /**
      * @brief timerTimeout is the slot for timer timeout to update the time on game screen
      * @post Timer is updated on game screen
      */
    void timerTimeout();

private:

    /**
      * @brief eventFilter gets all the events happening on mainwindow and captures and calculates the drone movements and bus shootings
      */
    virtual bool eventFilter(QObject *object, QEvent *ev) override;

    Ui::MainWindow *ui_;
    AskInfo *infoDialog_;
    QGraphicsScene *map_;
    DroneActor *drone_actor_;
    Enemy *enemy_actor_;

    QVector<QGraphicsItem*> actors_;
    std::shared_ptr<City> city_;
    std::shared_ptr<CourseSide::Logic> logic_;
    QTimer timer_;
    QDateTime startDateTime_;
    Statistics game_stats_;
    int GAME_LEVEL_;
    int width_, height_;
};

#endif // MAINWINDOW_H
