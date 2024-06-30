//
// Created by cxk_zjq on 2024/5/27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Component.h" resolved

#include <QDateTime>
#include "component.h"
#include "ui_Component.h"
#include "addcomponent.h"


Component::Component(QWidget *parent) :
        QWidget(parent), ui(new Ui::Component)
{
    ui->setupUi(this);

    // 右键菜单
    setContextMenuPolicy(Qt::CustomContextMenu); // 右键菜单
    menu = new QMenu(this);
    deleteAction = new QAction("删除", this);
    editAction = new QAction("编辑", this);
    menu->addAction(deleteAction);
    menu->addAction(editAction);
    connect(deleteAction, &QAction::triggered, [=](){
        emit deleteComponentSignal(this);
        this->deleteLater();
    });
    connect(editAction, &QAction::triggered, [=](){
        addComponent *addComponent = new class addComponent(this);
        addComponent->show();
        connect(addComponent, &addComponent::addComponentSignal, [=](const QStringList &list){
            this->setComponent(list);
        });
    });

    connect(this, &Component::customContextMenuRequested, [=](const QPoint &pos){
        menu->exec(this->mapToGlobal(pos));
    });

}

Component::~Component()
{
    delete ui;
}

void Component::setComponent(const QStringList &list)
{
    QString time=list[0];
    QString info=list[1];
    QString date=list[2].split(" ")[0];

    // 计算时间差
    QDateTime current_date_time = QDateTime::currentDateTime();
    QDateTime target_date_time = QDateTime::fromString(date, "yyyy-MM-dd");
    // 差了多少天
    int days = current_date_time.daysTo(target_date_time);

    // 获取date是星期几
    QString week = target_date_time.toString("dddd");
    if(week.size() !=0) {
        switch (week[0].toLatin1()) {
            case 'M':
                week = "周一";
                break;
            case 'T':
                week = "周二";
                break;
            case 'W':
                week = "周三";
                break;
            case 'F':
                week = "周五";
                break;
            case 'S':
                week = "周六";
                break;
            case 'U':
                week = "周日";
                break;
            default:
                break;

        }
    }
    date = date + " " + week;
    ui->time->setText(time);
    ui->date->setText(date);
    ui->label_2->setText(info);


    // 如果当前时间大于设定时间，那么设置为黄色
    if (days < 0) {
        ui->time->setStyleSheet("background-color: rgba(246, 255, 169, 125);\n"
                                "color:rgb(255, 205, 3);\n"
                                "border-top-left-radius:20px;\n"
                                "border-top-right-radius:20px;");
        ui->time->setText("已"+QString::number(-days)+"天");
        ui->progressBar->setValue(365);
        return;
    }
    ui->time->setText("剩余"+QString::number(days)+"天");
    ui->progressBar->setValue(365-days);
}

QStringList Component::getComponentInfo()
{
    QStringList list;
    if(ui->time->text().isEmpty()||ui->label_2->text().isEmpty()||ui->date->text().isEmpty()) return list;
    list.append(ui->time->text());
    list.append(ui->label_2->text());
    list.append(ui->date->text());
    return list;
}

