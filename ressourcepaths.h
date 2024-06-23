#ifndef RESSOURCEPATHS_H
#define RESSOURCEPATHS_H

#include <QDialog>
#include <QFileDialog>
#include "paramfile.h"

namespace Ui {
class ressourcePaths;
}

class ressourcePaths : public QDialog
{
    Q_OBJECT

public:
    std::shared_ptr<paramFile> paramFileObject;


    ressourcePaths(std::shared_ptr<paramFile> paramFilePtr);
    ~ressourcePaths();

private slots:
    void on_locateMusicFolderButton_clicked();
    void on_locateFfpmegButton_clicked();

private:
    Ui::ressourcePaths *ui;
};

#endif // RESSOURCEPATHS_H
