#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "mainwindow.h"
#include "Calculator.h"
#include "mainwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Menu;
}
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

protected slots:
    void GotoDecision();
    void GotoDate();
    void GotoCalculator();

private:
    Ui::Menu *ui;
    MainWindow *date;
    Calculator *cal;
    MainWidget *decision;
};
#endif // MENU_H
