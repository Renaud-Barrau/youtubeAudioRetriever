#ifndef APISETTINGS_H
#define APISETTINGS_H

#include <memory> // For std::shared_ptr

#include "paramfile.h"
#include <QDialog>

namespace Ui {
class apiSettings;
}

class apiSettings : public QDialog
{
    Q_OBJECT

public:
    std::shared_ptr<paramFile> paramFileObject;


    apiSettings(std::shared_ptr<paramFile> paramFilePtr);
    ~apiSettings();



private slots:
    void on_lockApiSettingsCheckBox_stateChanged(int arg1);

    void on_saveParamsButton_clicked();

private:
    Ui::apiSettings *ui;

};

#endif // APISETTINGS_H
