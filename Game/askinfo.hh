#ifndef ASKINFO_HH
#define ASKINFO_HH

#include <QDialog>
#include <QString>

namespace Ui {
class AskInfo;
}

namespace GameImplementation {

class AskInfo : public QDialog
{
    Q_OBJECT

public:

    /**
      * @brief Constructor for the dialog window AskInfo
      * @post Dialog window AskInfo is created
      */
    explicit AskInfo(QWidget *parent = nullptr);

    /**
      * @brief Destructor for the AskInfo
      * @post AskInfo is destroyed
      */
    ~AskInfo();

    /**
      * @brief get_name return the name of player
      * @return player's name typed in the dialog window.
      * @post Exception guarantee: nothrow.
      */
    QString get_name();

    /**
      * @brief get_level return the game level player choose to play
      * @return game level player choose in the dialog window.
      * @post Exception guarantee: nothrow.
      */
    int get_level();

private slots:
    /**
      * @brief on_nameLineEdit_editingFinished is the slot to get player's name written in QLineEdit space in the dialog window
      * after the dialog window is closed by pressing OK button
      * @post Exception guarantee: nothrow.
      */
    void on_nameLineEdit_editingFinished();

    /**
      * @brief on_levelSlider_valueChanged is the slot to get level player choose to play after the dialog window is closed by
      * sliding the level slide, or change number inside a box next to it by pressing OK button to confirm
      * @post Exception guarantee: nothrow.
      */
    void on_levelSlider_valueChanged(int value);

private:
    Ui::AskInfo *ui_askinfo;
    QString player_name_;
    int level_;
    const int LEVEL_MIN = 1;
    const int LEVEL_MAX = 5;
};

}
#endif // ASKINFO_HH

