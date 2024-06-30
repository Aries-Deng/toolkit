#include "sonwidget1.h"
#include "ui_sonwidget1.h"

SonWidget1::SonWidget1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SonWidget1)
{
    ui->setupUi(this);
    moveAngle = 0;
    animation=new QPropertyAnimation;
    animation->setTargetObject(this);
    animation->setPropertyName("angle");
    animation->setDuration(5000);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    connect(ui->startBotton,&QPushButton::clicked,this,&SonWidget1::StartAnimate);
    connect(animation,&QVariantAnimation::valueChanged,this,&SonWidget1::RotatePie);
    connect(animation,&QPropertyAnimation::finished,this,&SonWidget1::ShowResult);
    connect(ui->clearButton,&QPushButton::clicked,this,&SonWidget1::Recover);
}

void SonWidget1::StartAnimate()
{
    animation->setStartValue(moveAngle);
    animation->setEndValue(QRandomGenerator::global()->bounded(3600,3960));
    animation->start();
}

void SonWidget1::RotatePie(const QVariant& val)
{
    update();
}

int SonWidget1::getAngle() const
{
    return moveAngle;
}

void SonWidget1::setAngle(const int& a)
{
    moveAngle = a;
}

void SonWidget1::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    painter.setPen(QPen(Qt::white));
    painter.translate(380,250);
    QPixmap arrow;
    arrow.load("../../arrow.png");
    painter.drawPixmap(140, -37, 74, 74, arrow);
    painter.rotate(moveAngle%360);
    QBrush brush1(QColor(122,189,154)),brush2(QColor(239,250,244)),brush3(QColor(148,203,172));
    QFont font("微软雅黑",12,QFont::Bold);
    painter.setFont(font);
    double cutAngle=360.0/tmp->count;
    for(int i=0;i<tmp->count;i++)
    {
        painter.setPen(QPen(Qt::white));
        if(i%2==0)
            painter.setBrush(brush1);
        else
            painter.setBrush(brush2);
        if(tmp->count%2==1&&i==tmp->count-1)
            painter.setBrush(brush3);
        painter.drawPie(-150,-150,300,300,cutAngle*i*16,cutAngle*16);
        if(i%2==0)
            painter.setPen(QPen(Qt::white));
        else
            painter.setPen(QPen(QColor(122,189,154)));
        QString str=tmp->option[i]->text();
        int width=tmp->option[i]->text().length()*10;
        painter.rotate(-cutAngle*(0.5+i));
        painter.drawText(75-width/2,0,str);
        painter.rotate(cutAngle*(0.5+i));
    }

}

void SonWidget1::ShowResult()
{
    int a=moveAngle%360;
    double cutAngle=360.0/tmp->count;
    int n=a/cutAngle;
    QString result=tmp->option[n]->text();
    ui->resultTitle->setText("最终结果");
    ui->label->setWordWrap(true);
    ui->label->setText(result.split("", Qt::SkipEmptyParts).join("\n"));
}

void SonWidget1::Recover()
{
    moveAngle=0;
    ui->resultTitle->clear();
    ui->label->clear();
    update();
}

SonWidget1::~SonWidget1()
{
    delete ui;
}
