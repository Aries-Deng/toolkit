//
// Created by cxk_zjq on 2024/5/27.
//

#ifndef COMPONENT_MAINWINDOW_H
#define COMPONENT_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "component.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    void loadInfo(const QString & filepath);
    void saveInfo();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *layout;
    QVector<Component*> components;
};


#endif //COMPONENT_MAINWINDOW_H
