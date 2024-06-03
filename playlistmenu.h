#ifndef PLAYLISTMENU_H
#define PLAYLISTMENU_H

#include <QDialog>

namespace Ui {
class playlistMenu;
}

class playlistMenu : public QDialog
{
    Q_OBJECT

public:
    explicit playlistMenu(QWidget *parent = nullptr);
    ~playlistMenu();

private:
    Ui::playlistMenu *ui;
};

#endif // PLAYLISTMENU_H
