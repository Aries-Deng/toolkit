//
// Created by cxk_zjq on 2024/5/27.
//

#ifndef COMPONENT_ADDCOMPONENT_H
#define COMPONENT_ADDCOMPONENT_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class addComponent;
}
QT_END_NAMESPACE

class addComponent : public QDialog {
Q_OBJECT

public:
    explicit addComponent(QWidget *parent = nullptr);



    ~addComponent() override;
signals:
    void addComponentSignal(const QStringList &list);
private:
    Ui::addComponent *ui;
};


#endif //COMPONENT_ADDCOMPONENT_H
