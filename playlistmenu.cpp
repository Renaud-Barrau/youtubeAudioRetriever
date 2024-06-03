#include "playlistmenu.h"
#include "ui_playlistmenu.h"

playlistMenu::playlistMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::playlistMenu)
{
    ui->setupUi(this);
}

playlistMenu::~playlistMenu()
{
    delete ui;
}
