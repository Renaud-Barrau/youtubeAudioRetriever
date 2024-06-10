#ifndef RESSOURCEPATHS_H
#define RESSOURCEPATHS_H

#include <QDialog>

namespace Ui {
class ressourcePaths;
}

class ressourcePaths : public QDialog
{
    Q_OBJECT

public:
    explicit ressourcePaths(QWidget *parent = nullptr);
    ~ressourcePaths();

private:
    Ui::ressourcePaths *ui;
};

#endif // RESSOURCEPATHS_H
