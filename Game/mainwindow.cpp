#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QDate>
#include <QRandomGenerator>

#include <creategame.hh>
#include <actors/stop.hh>
#include <errors/gameerror.hh>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    installEventFilter(this);

    width_ = 500;
    height_ = 500;
    GAME_LEVEL_ = 0;
    connect(&timer_, SIGNAL(timeout()), this, SLOT(timerTimeout()));
}

MainWindow::~MainWindow()
{
    delete ui_;
    delete infoDialog_;
    delete map_;
    delete drone_actor_;
    delete enemy_actor_;
}

void MainWindow::addDrone(int locX, int locY)
{
    drone_actor_ = new DroneActor(locX, locY);
    actors_.push_back(drone_actor_);
    map_->addItem(drone_actor_);
}

void MainWindow::addEnemy(int locX, int locY)
{
    enemy_actor_ = new Enemy(locX, locY);
    actors_.push_back(enemy_actor_);
    map_->addItem(enemy_actor_);
}

void MainWindow::chasingDrone(Interface::Location drone_loc)
{
    const int STEP = GAME_LEVEL_;

    Interface::Location enemy_loc = enemy_actor_->getLocation();
    int cur_x = enemy_loc.giveX();
    int cur_y = enemy_loc.giveY();
    int dx = cur_x - drone_loc.giveX();
    int dy = cur_y - drone_loc.giveY();

    Interface::Location chasing_loc;
    if (dx > 0) {
        cur_x -= STEP;
    } else if (dx < 0) { cur_x += STEP; }

    if (dy > 0) {
        cur_y -= STEP;
    } else if (dy < 0) { cur_y += STEP; }

    chasing_loc.setXY(cur_x, cur_y);
    try {
        enemy_actor_->move(chasing_loc);
    }  catch (Interface::GameError ge) {
        qDebug() << ge.giveMessage();
    }
}

void MainWindow::createScene()
{
    map_ = new QGraphicsScene(this);
    ui_->gameView->setScene(map_);
    map_->setSceneRect(0,0,width_,height_);
    city_ = std::make_shared<City>(map_);
}

void MainWindow::startGame()
{
    ui_->label_score->setText("Score: " + QString::number(game_stats_.getScore()));
    ui_->label->setText("Game Running!");
    createScene();
    startDateTime_ = QDateTime::currentDateTime();
    QRandomGenerator generator(startDateTime_.toTime_t());
    logic_ = std::make_shared<CourseSide::Logic>();
    logic_->takeCity(city_);
    logic_->fileConfig();
    logic_->setTime( generator.bounded(7, 19) , generator.bounded(0, 59));
    logic_->finalizeGameStart();
    addDrone(0, 0);
    addEnemy(230, 230);
    timer_.start(100);
}

bool MainWindow::eventFilter(QObject *object, QEvent *ev)
{
    QKeyEvent *key_evt = (QKeyEvent*)ev;
    if (ev->type() == QEvent::KeyPress && (key_evt->key() & Qt::Key_Space) && drone_actor_->is_dragging())
    {
        Interface::Location drone_location = drone_actor_->getLocation();
        auto actor_to_remove = city_->getActorByLocation(drone_location);
        if(auto vehicle = std::dynamic_pointer_cast<CourseSide::Nysse>(actor_to_remove)){
            vehicle->remove();
            city_->removeActor(actor_to_remove);
            game_stats_.nysseRemoved();
        }
        ui_->label_score->setText("Score: " + QString::number(game_stats_.getScore()));
    }
    return false;
}

void MainWindow::on_start_button_clicked()
{
    infoDialog_ = new AskInfo(this);
    int confirm = infoDialog_->exec();

    if(confirm == QDialog::Accepted) { // Press OK
        ui_->label_name->setText("Name: " + infoDialog_->get_name() + " Level: " + QString::number(infoDialog_->get_level()));
        GAME_LEVEL_ = infoDialog_->get_level();
        ui_->start_button->setDisabled(true);
        startGame();
    }
    else { // Press Exit
        infoDialog_->close();
        MainWindow::close();
    }
}

void MainWindow::timerTimeout()
{
    // Update time
    QDateTime curDateTime = QDateTime::currentDateTime();
    qint64 millisecondsDiff = startDateTime_.msecsTo(curDateTime);
    QDateTime deltaTime;
    deltaTime.setMSecsSinceEpoch(millisecondsDiff);
    ui_->label->setText(deltaTime.toString("mm:ss"));

    // Let enemy chasing drone
    chasingDrone(drone_actor_->giveLocation());

    // Check game over
    bool lose_condition = enemy_actor_->isCloseToDrone(drone_actor_->getLocation()) && !city_->isGameOver();
    bool win_condition = game_stats_.getScore() >= 100 && !city_->isGameOver();
    if (lose_condition || win_condition) {
        city_->setIsGameOver(true);
        if (lose_condition) {
            ui_->label->setText("You lose!");
            ui_->ending_time->setText("Game Time: " + deltaTime.toString("mm:ss"));
        } else {
            ui_->label->setText("You win!");
            ui_->ending_time->setText("Completion Time: " + deltaTime.toString("mm:ss"));
        }

        // Reset the game to initial state
        map_->clear();
        timer_.stop();
    }
}
