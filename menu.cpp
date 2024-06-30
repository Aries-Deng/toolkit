#include "menu.h"
#include "./ui_menu.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowTitle("菜单");
    date = new MainWindow;
    cal = new Calculator;
    decision = new MainWidget;
    connect(ui->DecisionButton,&QPushButton::clicked,this,&Menu::GotoDecision);
    connect(ui->DateButton,&QPushButton::clicked,this,&Menu::GotoDate);
    connect(ui->CalculatorButton,&QPushButton::clicked,this,&Menu::GotoCalculator);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::GotoDecision()
{
    decision->show();
}

void Menu::GotoDate()
{
    date->show();
}

void Menu::GotoCalculator()
{
    cal->show();
}
