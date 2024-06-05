#include "apisettings.h"
#include "ui_apisettings.h"

apiSettings::apiSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::apiSettings)
{
    ui->setupUi(this);
}

apiSettings::~apiSettings()
{
    delete ui;
}
