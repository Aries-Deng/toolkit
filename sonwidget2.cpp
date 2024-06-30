#include "sonwidget2.h"
#include "ui_sonwidget2.h"

SonWidget2::SonWidget2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SonWidget2)
{
    ui->setupUi(this);
    option.push_back(ui->firstEdit);
    connect(ui->addButton,&QPushButton::clicked,this,&SonWidget2::addOption);
    addOption();addOption();
    option[0]->setText("线代");
    option[1]->setText("高数");
    option[2]->setText("程设");
}

SonWidget2::~SonWidget2()
{
    delete ui;
}

void SonWidget2::addOption()
{
    if(count>=8)
    {
        return;
    }
    option.push_back(new QLineEdit(this));
    count++;
    int newy = option[count-2]->geometry().y() + 50;
    option[count-1]->setGeometry(80,newy,200,40);
    option[count-1]->setFont(option[count-2]->font());
    option[count-1]->setAlignment(Qt::AlignHCenter);
    option[count-1]->show();
    ui->addButton->setGeometry(350,newy,40,40);
    QPushButton* deleteButton=new QPushButton(this);
    deleteButton->setStyleSheet("QPushButton{background-color:rgb(175, 175, 175);color:rgb(255, 255, 255);border-radius:15px;}QPushButton:hover{background-color:rgb(200,200,200);}");
    deleteButton->setText("×");
    deleteButton->setFont(QFont("Consolas",16));
    deleteButton->setGeometry(290,newy+5,30,30);
    deleteButton->show();
    button.push_back(deleteButton);
    switch(count-1)
    {
    case 1:
        connect(deleteButton,&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[1];option.erase(option.begin()+1);tmp->deleteLater();
            QPushButton* temp=button[0];button.erase(button.begin());temp->deleteLater();SonWidget2::Reshape();});
        break;
    case 2:
        connect(deleteButton,&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[2];option.erase(option.begin()+2);tmp->deleteLater();
            QPushButton* temp=button[1];button.erase(button.begin()+1);temp->deleteLater();SonWidget2::Reshape();});
        break;
    case 3:
        connect(deleteButton,&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[3];option.erase(option.begin()+3);tmp->deleteLater();
            QPushButton* temp=button[2];button.erase(button.begin()+2);temp->deleteLater();SonWidget2::Reshape();});
        break;
    case 4:
        connect(deleteButton,&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[4];option.erase(option.begin()+4);tmp->deleteLater();
            QPushButton* temp=button[3];button.erase(button.begin()+3);temp->deleteLater();SonWidget2::Reshape();});
        break;
    case 5:
        connect(deleteButton,&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[5];option.erase(option.begin()+5);tmp->deleteLater();
            QPushButton* temp=button[4];button.erase(button.begin()+4);temp->deleteLater();SonWidget2::Reshape();});
        break;
    case 6:
        connect(deleteButton,&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[6];option.erase(option.begin()+6);tmp->deleteLater();
            QPushButton* temp=button[5];button.erase(button.begin()+5);temp->deleteLater();SonWidget2::Reshape();});
        break;
    case 7:
        connect(deleteButton,&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[7];option.erase(option.begin()+7);tmp->deleteLater();
            QPushButton* temp=button[6];button.erase(button.begin()+6);temp->deleteLater();SonWidget2::Reshape();});
        break;
    }
}

void SonWidget2::Reshape()
{
    count--;
    for(int i=0;i<count;i++)
    {
        option[i]->setGeometry(80,140+i*50,200,40);
        option[i]->disconnect();
    }
    for(int i=0;i<count-1;i++)
    {
        button[i]->setGeometry(290,195+i*50,30,30);
        button[i]->disconnect();
    }
    ui->addButton->setGeometry(350,140+(count-1)*50,40,40);
    for(int i=1;i<count;i++)
    {
        switch(i)
        {
        case 1:
            connect(button[0],&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[1];option.erase(option.begin()+1);tmp->deleteLater();
            QPushButton* temp=button[0];button.erase(button.begin());temp->deleteLater();SonWidget2::Reshape();});
            break;
        case 2:
            connect(button[1],&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[2];option.erase(option.begin()+2);tmp->deleteLater();
            QPushButton* temp=button[1];button.erase(button.begin()+1);temp->deleteLater();SonWidget2::Reshape();});
            break;
        case 3:
            connect(button[2],&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[3];option.erase(option.begin()+3);tmp->deleteLater();
            QPushButton* temp=button[2];button.erase(button.begin()+2);temp->deleteLater();SonWidget2::Reshape();});
            break;
        case 4:
            connect(button[3],&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[4];option.erase(option.begin()+4);tmp->deleteLater();
            QPushButton* temp=button[3];button.erase(button.begin()+3);temp->deleteLater();SonWidget2::Reshape();});
            break;
        case 5:
            connect(button[4],&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[5];option.erase(option.begin()+5);tmp->deleteLater();
            QPushButton* temp=button[4];button.erase(button.begin()+4);temp->deleteLater();SonWidget2::Reshape();});
            break;
        case 6:
            connect(button[5],&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[6];option.erase(option.begin()+6);tmp->deleteLater();
            QPushButton* temp=button[5];button.erase(button.begin()+5);temp->deleteLater();SonWidget2::Reshape();});
            break;
        case 7:
            connect(button[6],&QPushButton::clicked,this,[this]{QLineEdit* tmp=option[7];option.erase(option.begin()+7);tmp->deleteLater();
            QPushButton* temp=button[6];button.erase(button.begin()+6);temp->deleteLater();SonWidget2::Reshape();});
            break;
        }
    }
}
