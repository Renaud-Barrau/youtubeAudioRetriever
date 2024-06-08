#include "apisettings.h"
#include "ui_apisettings.h"

apiSettings::apiSettings(std::shared_ptr<paramFile> ptr)
    :
    paramFileObject(ptr),
    ui(new Ui::apiSettings)

{
    ui->setupUi(this);

    ui->apiKeyTextEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->apiKeyTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->clientIdTextEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->clientIdTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->clientSecretCodeTextEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->clientSecretCodeTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->refreshTokenTextEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->refreshTokenTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->lockApiSettingsCheckBox->setCheckState(Qt::Checked);



    ui->apiKeyTextEdit->setText(paramFileObject->readParam("apiKey"));
    ui->clientIdTextEdit->setText(paramFileObject->readParam("clientId"));
    ui->clientSecretCodeTextEdit->setText(paramFileObject->readParam("clientSecretCode"));
    ui->refreshTokenTextEdit->setText(paramFileObject->readParam("refreshToken"));
}

apiSettings::~apiSettings()
{
    delete ui;
}


void apiSettings::on_lockApiSettingsCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->apiKeyTextEdit->setReadOnly(false);
        ui->apiKeyTextEdit->setStyleSheet("QTextEdit { color: #000000; }");
        ui->clientIdTextEdit->setReadOnly(false);
        ui->clientIdTextEdit->setStyleSheet("QTextEdit { color: #000000; }");
        ui->clientSecretCodeTextEdit->setReadOnly(false);
        ui->clientSecretCodeTextEdit->setStyleSheet("QTextEdit { color: #000000; }");
        ui->refreshTokenTextEdit->setReadOnly(false);
        ui->refreshTokenTextEdit->setStyleSheet("QTextEdit { color: #000000; }");
    }
    else if(arg1 == 2){
        ui->apiKeyTextEdit->setReadOnly(true);
        ui->apiKeyTextEdit->setStyleSheet("QTextEdit { color: #808080; }");
        ui->clientIdTextEdit->setReadOnly(true);
        ui->clientIdTextEdit->setStyleSheet("QTextEdit { color: #808080; }");
        ui->clientSecretCodeTextEdit->setReadOnly(true);
        ui->clientSecretCodeTextEdit->setStyleSheet("QTextEdit { color: #808080; }");
        ui->refreshTokenTextEdit->setReadOnly(true);
        ui->refreshTokenTextEdit->setStyleSheet("QTextEdit { color: #808080; }");
    }
}


void apiSettings::on_saveParamsButton_clicked()
{

    cout << "Save params button pressed" << endl;
    paramFileObject->writeParam("apiKey", ui->apiKeyTextEdit->toPlainText());
    paramFileObject->writeParam("clientId", ui->clientIdTextEdit->toPlainText());
    paramFileObject->writeParam("clientSecretCode", ui->clientSecretCodeTextEdit->toPlainText());
    paramFileObject->writeParam("refreshToken", ui->refreshTokenTextEdit->toPlainText());
}

