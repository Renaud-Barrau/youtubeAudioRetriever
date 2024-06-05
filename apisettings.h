#ifndef APISETTINGS_H
#define APISETTINGS_H

#include <QDialog>

namespace Ui {
class apiSettings;
}

class apiSettings : public QDialog
{
    Q_OBJECT

public:
    explicit apiSettings(QWidget *parent = nullptr);
    ~apiSettings();

private:
    Ui::apiSettings *ui;
};

#endif // APISETTINGS_H
