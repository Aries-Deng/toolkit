#ifndef SONWIDGET2_H
#define SONWIDGET2_H

#include <QWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QVector>

namespace Ui {
class SonWidget2;
}

class SonWidget2 : public QWidget
{
    Q_OBJECT

public:
    friend class SonWidget1;
    friend class MainWidget;
    explicit SonWidget2(QWidget *parent = nullptr);
    void Reshape();
    ~SonWidget2();

private:
    Ui::SonWidget2 *ui;

public:
    //QLineEdit* option[10];
    QVector<QLineEdit*> option;
    QVector<QPushButton*> button;
    int count=1;

private slots:
    void addOption();
};


#endif // SONWIDGET2_H
