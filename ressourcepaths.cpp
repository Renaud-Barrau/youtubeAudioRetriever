#include "ressourcepaths.h"
#include "ui_ressourcepaths.h"

ressourcePaths::ressourcePaths(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ressourcePaths)
{
    ui->setupUi(this);
}

ressourcePaths::~ressourcePaths()
{
    delete ui;
}
