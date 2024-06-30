//
// Created by cxk_zjq on 2024/5/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_addComponent.h" resolved

#include "addcomponent.h"
#include "ui_addComponent.h"


addComponent::addComponent(QWidget *parent) :
        QDialog(parent), ui(new Ui::addComponent)
{
    ui->setupUi(this);
    setWindowTitle("新建");
    // 关闭窗口时发出信号
    connect(this,&QDialog::rejected,[=](){ // rejected是关闭窗口的信号
        QString date=ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
        QString info=ui->plainTextEdit->toPlainText();
        QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QStringList list;
        list.append(time);
        list.append(info);
        list.append(date);
        emit addComponentSignal(list);
    });
}

addComponent::~addComponent()
{
    delete ui;
}
