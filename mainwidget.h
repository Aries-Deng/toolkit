#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "sonwidget1.h"
#include "sonwidget2.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    SonWidget1 *wid1;
    SonWidget2 *wid2;

private slots:
    void two2one();
    void one2two();

};
#endif // MAINWIDGET_H
