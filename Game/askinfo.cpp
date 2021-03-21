#include "askinfo.hh"
#include "ui_askinfo.h"

namespace GameImplementation {

AskInfo::AskInfo(QWidget *parent) :
    QDialog(parent),
    ui_askinfo(new Ui::AskInfo)
{
    ui_askinfo->setupUi(this);

    ui_askinfo->levelSlider->setTickInterval(LEVEL_MIN);
    ui_askinfo->levelSlider->setMinimum(LEVEL_MIN);
    ui_askinfo->levelSlider->setMaximum(LEVEL_MAX);

    ui_askinfo->levelSpinBox->setMinimum(LEVEL_MIN);
    ui_askinfo->levelSpinBox->setMaximum(LEVEL_MAX);

    connect(ui_askinfo->okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui_askinfo->exitButton, &QPushButton::clicked, this, &QDialog::reject);
}

AskInfo::~AskInfo()
{
    delete ui_askinfo;
}

QString AskInfo::get_name()
{
    return player_name_;
}

int AskInfo::get_level()
{
    return level_;
}

void AskInfo::on_nameLineEdit_editingFinished()
{
    player_name_ = ui_askinfo->nameLineEdit->text();
}

void AskInfo::on_levelSlider_valueChanged(int value)
{
    level_ = value;
}

}
