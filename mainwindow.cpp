//
// Created by cxk_zjq on 2024/5/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "component.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include "addcomponent.h"



MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("纪念日");
    // 添加10个组件
    layout = new QVBoxLayout();

    loadInfo("info.txt");

    this->setMinimumWidth(380);

    layout->setSpacing(20);

    ui->scrollAreaWidgetContents->setLayout(layout);

    // 添加组件
    connect(ui->pushButton, &QPushButton::clicked, [=](){
        addComponent *addComponent = new class addComponent(this);
        addComponent->show();
        connect(addComponent, &addComponent::addComponentSignal, [=](const QStringList &list){
            Component *component = new Component(this);
            components.append(component);
            component->setComponent(list);
            layout->addWidget(component);
        });
    });

}

MainWindow::~MainWindow()
{
    saveInfo();
    delete ui;
}

void MainWindow::loadInfo(const QString &filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()){
        QString line = in.readLine();
        if(line.isEmpty()) continue;
        QStringList list = line.split(" ");
        Component *component = new Component(this);
        components.append(component);
        component->setComponent(list);
        layout->addWidget(component);
    }
}

void MainWindow::saveInfo()
{
    QFile file("info.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    for (auto component : components) {
        if(component==nullptr||component->getComponentInfo().empty()) continue;
        QStringList list = component->getComponentInfo();
        out << list.join(" ") << "\n";
    }
    file.close();
}
