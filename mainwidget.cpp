#include "mainwidget.h"
#include "./ui_mainwidget.h"
#include "ui_sonwidget2.h"
#include"ui_sonwidget1.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("做个决定");
    wid1 = new SonWidget1;
    wid2 = new SonWidget2;
    ui->stackedWidget->addWidget(wid1);
    ui->stackedWidget->addWidget(wid2);
    ui->stackedWidget->setCurrentWidget(wid1);
    connect(wid2->ui->returnButton,&QPushButton::clicked,this,&MainWidget::two2one);
    connect(wid1->ui->editButton,&QPushButton::clicked,this,&MainWidget::one2two);
    wid1->tmp=wid2;
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::two2one()
{
    ui->stackedWidget->setCurrentWidget(wid1);
    QString title=wid2->ui->titleEdit->text();
    wid1->ui->titleLabel->setText(title);
}

void MainWidget::one2two()
{
    ui->stackedWidget->setCurrentWidget(wid2);
    wid1->Recover();
}
