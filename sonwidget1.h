#ifndef SONWIDGET1_H
#define SONWIDGET1_H

#include <QWidget>
#include<QPropertyAnimation>
#include<QRandomGenerator>
#include<QPainter>
#include"sonwidget2.h"

namespace Ui {
class SonWidget1;
}

class SonWidget1 : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int angle READ getAngle WRITE setAngle)

public:
    friend class MainWidget;
    friend class SonWidget2;
    explicit SonWidget1(QWidget *parent = nullptr);
    ~SonWidget1();
    int getAngle() const;
    void setAngle(const int& a);

protected slots:
    void StartAnimate();
    void RotatePie(const QVariant& val);
    void ShowResult();
    void Recover();

protected:
    void paintEvent(QPaintEvent*);

private:
    Ui::SonWidget1 *ui;
    QPropertyAnimation *animation;
    int moveAngle;
    SonWidget2* tmp;
};

#endif // SONWIDGET1_H
