//
// Created by cxk_zjq on 2024/5/27.
//

#ifndef CALANDAR_COMPONENT_H
#define CALANDAR_COMPONENT_H

#include <QWidget>
#include <QMenu>
#include <QAction>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class Component;
}
QT_END_NAMESPACE

class Component : public QWidget {
Q_OBJECT

public:
    explicit Component(QWidget *parent = nullptr);

    void setComponent(const QStringList& list);
    QStringList getComponentInfo();

    ~Component() override;

signals:
    void deleteComponentSignal(Component* component);

private:
    Ui::Component *ui;
    QMenu* menu;
    QAction* deleteAction;
    QAction* editAction;

};


#endif //CALANDAR_COMPONENT_H
