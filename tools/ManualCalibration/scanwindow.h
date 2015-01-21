#ifndef SCANWINDOW_H
#define SCANWINDOW_H
#include <3dUnitDriver.hpp>
#include <QDialog>

namespace Ui {
class scanWindow;
}

class scanWindow : public QDialog
{
    Q_OBJECT

public:
    explicit scanWindow(QWidget *parent = 0);
    ~scanWindow();
     m3d::rawPointcloud *rawPc1;
     m3d::rawPointcloud *rawPc2;

private:
    Ui::scanWindow *ui;

public slots:
    void makeScan();

};

#endif // SCANWINDOW_H
