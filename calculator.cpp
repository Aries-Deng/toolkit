#include "Calculator.h"
#include "./ui_Calculator.h"
#include <QMap>
#include <QStringList>
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    setWindowTitle("亲属关系计算");
    connect(ui->buttonH, &QPushButton::clicked, this, &Calculator::appendRelation);
    connect(ui->buttonW, &QPushButton::clicked, this, &Calculator::appendRelation);
    connect(ui->buttonF, &QPushButton::clicked, this, &Calculator::appendRelation);
    connect(ui->buttonM, &QPushButton::clicked, this, &Calculator::appendRelation);
    connect(ui->buttonOb, &QPushButton::clicked, this, &Calculator::appendRelation);
    connect(ui->buttonLb, &QPushButton::clicked, this, &Calculator::appendRelation);
    connect(ui->buttonOs, &QPushButton::clicked, this, &Calculator::appendRelation);
    connect(ui->buttonLs, &QPushButton::clicked, this, &Calculator::appendRelation);
    connect(ui->buttonS, &QPushButton::clicked, this, &Calculator::appendRelation);
    connect(ui->buttonD, &QPushButton::clicked, this, &Calculator::appendRelation);

    connect(ui->delButton, &QPushButton::clicked, this, &Calculator::onDelClicked);
    connect(ui->clrButton, &QPushButton::clicked, this, &Calculator::onClrClicked);
    connect(ui->calcButton, &QPushButton::clicked, this, &Calculator::onCalcClicked);

    initRelationshipMap();
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::appendRelation()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString buttonText = button->text();
        QString currentText = ui->lineEdit->text();
        currentText.append(buttonText+"的");
        ui->lineEdit->setText(currentText);
    }
}

void Calculator::onDelClicked()
{
    QString text = ui->lineEdit->text();
    text.chop(1); // 删除最后一个字符
    ui->lineEdit->setText(text);
}

void Calculator::onClrClicked()
{
    ui->lineEdit->clear(); // 清空输入框
}

void Calculator::onCalcClicked()
{
    QString relationship = ui->lineEdit->text();
    QString result = calculateRelationship(relationship);
    ui->resultLabel->setText(result);
}

QString Calculator::calculateRelationship(const QString &relationship)
{
    QStringList parts = relationship.split("的");
    QStringList relationshipChain;
    for (const QString &part : parts) {
        if (part == "丈夫") {
            relationshipChain.append("h");
        } else if (part == "妻子") {
            relationshipChain.append("w");
        } else if (part == "父亲") {
            relationshipChain.append("f");
        } else if (part == "母亲") {
            relationshipChain.append("m");
        } else if (part == "哥哥") {
            relationshipChain.append("ob");
        } else if (part == "弟弟") {
            relationshipChain.append("lb");
        } else if (part == "姐姐") {
            relationshipChain.append("os");
        } else if (part == "妹妹") {
            relationshipChain.append("ls");
        } else if (part == "儿子") {
            relationshipChain.append("s");
        } else if (part == "女儿") {
            relationshipChain.append("d");
        }
    }

    // 将关系链转换为字符串形式
    QString relationshipKey = relationshipChain.join(",");

    // 查找关系链对应的称呼
    if (relationshipMap.contains(relationshipKey)) {
        return relationshipMap.value(relationshipKey).join("/");
    } else {
        return "未知关系";
    }
}

void Calculator::initRelationshipMap()
{
    relationshipMap.insert("h", QStringList{"丈夫"});
    relationshipMap.insert("h,w", QStringList{"自己"});
    relationshipMap.insert("h,f", QStringList{"公公"});
    relationshipMap.insert("h,m", QStringList{"婆婆"});
    relationshipMap.insert("h,ob", QStringList{"大伯"});
    relationshipMap.insert("h,lb", QStringList{"小叔"});
    relationshipMap.insert("h,os", QStringList{"大姑子"});
    relationshipMap.insert("h,ls", QStringList{"小姑子"});
    relationshipMap.insert("h,s", QStringList{"儿子"});
    relationshipMap.insert("h,d", QStringList{"女儿"});

    relationshipMap.insert("w", QStringList{"妻子"});
    relationshipMap.insert("w,h", QStringList{"自己"});
    relationshipMap.insert("w,f", QStringList{"岳父"});
    relationshipMap.insert("w,m", QStringList{"岳母"});
    relationshipMap.insert("w,ob", QStringList{"大舅子"});
    relationshipMap.insert("w,lb", QStringList{"小舅子"});
    relationshipMap.insert("w,os", QStringList{"大姨子"});
    relationshipMap.insert("w,ls", QStringList{"小姨子"});
    relationshipMap.insert("w,s", QStringList{"儿子"});
    relationshipMap.insert("w,d", QStringList{"女儿"});

    relationshipMap.insert("f", QStringList{"父亲", "爸爸"});
    relationshipMap.insert("f,w", QStringList{"母亲", "妈妈"});
    relationshipMap.insert("f,f", QStringList{"祖父", "爷爷"});
    relationshipMap.insert("f,m", QStringList{"祖母", "奶奶"});
    relationshipMap.insert("f,ob", QStringList{"伯父"});
    relationshipMap.insert("f,lb", QStringList{"叔父"});
    relationshipMap.insert("f,os", QStringList{"姑母", "大姑"});
    relationshipMap.insert("f,ls", QStringList{"姑妈", "小姑"});
    relationshipMap.insert("f,s", QStringList{"自己", "兄弟"});
    relationshipMap.insert("f,d", QStringList{"自己", "姐妹"});

    relationshipMap.insert("m", QStringList{"母亲", "妈妈"});
    relationshipMap.insert("m,h", QStringList{"父亲", "爸爸"});
    relationshipMap.insert("m,f", QStringList{"外祖父", "姥爷"});
    relationshipMap.insert("m,m", QStringList{"外祖母", "姥姥"});
    relationshipMap.insert("m,ob", QStringList{"舅父", "舅舅"});
    relationshipMap.insert("m,lb", QStringList{"舅父", "舅舅"});
    relationshipMap.insert("m,os", QStringList{"姨母", "大姨"});
    relationshipMap.insert("m,ls", QStringList{"姨母", "小姨"});
    relationshipMap.insert("m,s", QStringList{"自己", "兄弟"});
    relationshipMap.insert("m,d", QStringList{"自己", "姐妹"});

    relationshipMap.insert("ob", QStringList{"哥哥"});
    relationshipMap.insert("ob,w", QStringList{"嫂子"});
    relationshipMap.insert("ob,f", QStringList{"父亲", "爸爸"});
    relationshipMap.insert("ob,m", QStringList{"母亲", "妈妈"});
    relationshipMap.insert("ob,ob", QStringList{"哥哥"});
    relationshipMap.insert("ob,lb", QStringList{"弟弟"});
    relationshipMap.insert("ob,os", QStringList{"姐姐"});
    relationshipMap.insert("ob,ls", QStringList{"妹妹"});
    relationshipMap.insert("ob,s", QStringList{"侄子"});
    relationshipMap.insert("ob,d", QStringList{"侄女"});

    relationshipMap.insert("lb", QStringList{"弟弟"});
    relationshipMap.insert("lb,w", QStringList{"弟媳"});
    relationshipMap.insert("lb,f", QStringList{"父亲", "爸爸"});
    relationshipMap.insert("lb,m", QStringList{"母亲", "妈妈"});
    relationshipMap.insert("lb,ob", QStringList{"哥哥"});
    relationshipMap.insert("lb,lb", QStringList{"弟弟"});
    relationshipMap.insert("lb,os", QStringList{"姐姐"});
    relationshipMap.insert("lb,ls", QStringList{"妹妹"});
    relationshipMap.insert("lb,s", QStringList{"侄子"});
    relationshipMap.insert("lb,d", QStringList{"侄女"});

    relationshipMap.insert("os", QStringList{"姐姐"});
    relationshipMap.insert("os,h", QStringList{"姐夫"});
    relationshipMap.insert("os,f", QStringList{"父亲", "爸爸"});
    relationshipMap.insert("os,m", QStringList{"母亲", "妈妈"});
    relationshipMap.insert("os,ob", QStringList{"哥哥"});
    relationshipMap.insert("os,lb", QStringList{"弟弟"});
    relationshipMap.insert("os,os", QStringList{"姐姐"});
    relationshipMap.insert("os,ls", QStringList{"妹妹"});
    relationshipMap.insert("os,s", QStringList{"外甥"});
    relationshipMap.insert("os,d", QStringList{"外甥女"});

    relationshipMap.insert("ls", QStringList{"妹妹"});
    relationshipMap.insert("ls,h", QStringList{"妹夫"});
    relationshipMap.insert("ls,f", QStringList{"父亲", "爸爸"});
    relationshipMap.insert("ls,m", QStringList{"母亲", "妈妈"});
    relationshipMap.insert("ls,ob", QStringList{"哥哥"});
    relationshipMap.insert("ls,lb", QStringList{"弟弟"});
    relationshipMap.insert("ls,os", QStringList{"姐姐"});
    relationshipMap.insert("ls,ls", QStringList{"妹妹"});
    relationshipMap.insert("ls,s", QStringList{"外甥"});
    relationshipMap.insert("ls,d", QStringList{"外甥女"});

    relationshipMap.insert("s", QStringList{"儿子"});
    relationshipMap.insert("s,w", QStringList{"儿媳妇"});
    relationshipMap.insert("s,f", QStringList{"自己", "丈夫"});
    relationshipMap.insert("s,m", QStringList{"自己", "妻子"});
    relationshipMap.insert("s,ob", QStringList{"儿子"});
    relationshipMap.insert("s,lb", QStringList{"儿子"});
    relationshipMap.insert("s,os", QStringList{"女儿"});
    relationshipMap.insert("s,ls", QStringList{"女儿"});
    relationshipMap.insert("s,s", QStringList{"孙子"});
    relationshipMap.insert("s,d", QStringList{"孙女"});

    relationshipMap.insert("d", QStringList{"女儿"});
    relationshipMap.insert("d,h", QStringList{"女婿"});
    relationshipMap.insert("d,f", QStringList{"自己", "丈夫"});
    relationshipMap.insert("d,m", QStringList{"自己", "妻子"});
    relationshipMap.insert("d,ob", QStringList{"儿子"});
    relationshipMap.insert("d,lb", QStringList{"儿子"});
    relationshipMap.insert("d,os", QStringList{"女儿"});
    relationshipMap.insert("d,ls", QStringList{"女儿"});
    relationshipMap.insert("d,s", QStringList{"外孙"});
    relationshipMap.insert("d,d", QStringList{"外孙女"});

    relationshipMap.insert("f,f,w", QStringList{"祖母/奶奶"});
    relationshipMap.insert("f,f,f", QStringList{"曾祖父/太爷爷"});
    relationshipMap.insert("f,f,m", QStringList{"曾祖母/太奶奶"});
    relationshipMap.insert("f,f,f,w", QStringList{"曾祖母/太奶奶"});
    relationshipMap.insert("f,f,f,f", QStringList{"高祖父/老太爷爷"});
    relationshipMap.insert("f,f,f,m", QStringList{"高祖母/老太奶奶"});
    relationshipMap.insert("f,ob,w", QStringList{"伯母/姆姆"});
    relationshipMap.insert("f,lb,w", QStringList{"叔母/婶婶"});
    relationshipMap.insert("f,os,h", QStringList{"姑丈/姑夫"});
    relationshipMap.insert("f,ls,h", QStringList{"姑丈/姑夫"});
    relationshipMap.insert("f,ob,s", QStringList{"堂兄/堂哥/哥哥"});
    relationshipMap.insert("f,lb,s", QStringList{"堂弟/弟弟"});
    relationshipMap.insert("f,lb,w,s", QStringList{"堂弟/弟弟"});
    relationshipMap.insert("f,lb,w,d", QStringList{"堂妹/妹妹"});
    relationshipMap.insert("f,ob,s,w", QStringList{"堂嫂/嫂嫂"});
    relationshipMap.insert("f,lb,s,w", QStringList{"堂弟妇/弟妹"});
    relationshipMap.insert("f,ob,d", QStringList{"堂姐/堂姊"});
    relationshipMap.insert("f,ob,d,h", QStringList{"堂姐夫"});
    relationshipMap.insert("f,lb,d", QStringList{"堂妹"});
    relationshipMap.insert("f,lb,d,h", QStringList{"堂妹夫"});
    relationshipMap.insert("f,os,s", QStringList{"表兄/表哥"});
    relationshipMap.insert("f,os,s,w", QStringList{"表嫂"});
    relationshipMap.insert("f,ls,s", QStringList{"表弟"});
    relationshipMap.insert("f,ls,s,w", QStringList{"表弟妇"});
    relationshipMap.insert("f,os,d", QStringList{"表姐"});
    relationshipMap.insert("f,os,d,h", QStringList{"表姐夫"});
    relationshipMap.insert("f,ls,d", QStringList{"表妹"});
    relationshipMap.insert("f,ls,d,h", QStringList{"表妹夫"});
    relationshipMap.insert("f,f,os,s", QStringList{"表伯"});
    relationshipMap.insert("f,f,os,s,w", QStringList{"表姆"});
    relationshipMap.insert("f,f,ls,s", QStringList{"表叔"});
    relationshipMap.insert("f,f,ls,s,w", QStringList{"表婶"});
    relationshipMap.insert("f,f,os,d", QStringList{"表姑"});
    relationshipMap.insert("f,f,os,d,h", QStringList{"表姑夫"});
    relationshipMap.insert("f,f,ls,d", QStringList{"表姑"});
    relationshipMap.insert("f,f,ls,d,h", QStringList{"表姑夫"});
    relationshipMap.insert("f,m,ob", QStringList{"舅祖父/舅公"});
    relationshipMap.insert("f,m,ob,w", QStringList{"舅祖母/妗婆"});
    relationshipMap.insert("f,m,lb", QStringList{"舅祖父/舅公"});
    relationshipMap.insert("f,m,lb,w", QStringList{"舅祖母/妗婆"});
    relationshipMap.insert("f,f,ob", QStringList{"伯祖父"});
    relationshipMap.insert("f,f,f,ob,s", QStringList{"堂伯祖父"});
    relationshipMap.insert("f,f,ob,w", QStringList{"伯祖母"});
    relationshipMap.insert("f,f,f,ob,s,w", QStringList{"堂伯祖母"});
    relationshipMap.insert("f,f,lb", QStringList{"叔祖父"});
    relationshipMap.insert("f,f,f,lb,s", QStringList{"堂叔祖父"});
    relationshipMap.insert("f,f,lb,w", QStringList{"叔祖母"});
    relationshipMap.insert("f,f,f,lb,s,w", QStringList{"堂叔祖母"});
    relationshipMap.insert("f,f,os", QStringList{"祖姑母/姑婆"});
    relationshipMap.insert("f,f,ls", QStringList{"祖姑母/姑婆"});
    relationshipMap.insert("f,f,f,ob,d", QStringList{"祖姑母/姑婆"});
    relationshipMap.insert("f,f,f,lb,d", QStringList{"祖姑母/姑婆"});
    relationshipMap.insert("f,f,os,h", QStringList{"祖姑丈/姑婆公"});
    relationshipMap.insert("f,f,ls,h", QStringList{"祖姑丈/姑婆公"});
    relationshipMap.insert("f,f,f,ob,d,h", QStringList{"祖姑丈/姑婆公"});
    relationshipMap.insert("f,f,f,lb,d,h", QStringList{"祖姑丈/姑婆公"});
    relationshipMap.insert("f,f,f,ob", QStringList{"曾伯祖父"});
    relationshipMap.insert("f,f,f,f,ob,s", QStringList{"曾伯祖父"});
    relationshipMap.insert("f,f,f,ob,w", QStringList{"曾伯祖母"});
    relationshipMap.insert("f,f,f,f,ob,s,w", QStringList{"曾伯祖母"});
    relationshipMap.insert("f,f,f,lb", QStringList{"曾叔祖父"});
    relationshipMap.insert("f,f,f,f,lb,s", QStringList{"曾叔祖父"});
    relationshipMap.insert("f,f,f,lb,w", QStringList{"曾叔祖母"});
    relationshipMap.insert("f,f,f,f,lb,s,w", QStringList{"曾叔祖母"});
    relationshipMap.insert("f,f,f,os", QStringList{"曾祖姑母/太姑婆"});
    relationshipMap.insert("f,f,f,ls", QStringList{"曾祖姑母/太姑婆"});
    relationshipMap.insert("f,f,f,f,ob,d", QStringList{"曾祖姑母/太姑婆"});
    relationshipMap.insert("f,f,f,f,lb,d", QStringList{"曾祖姑母/太姑婆"});
    relationshipMap.insert("f,f,f,os,h", QStringList{"曾祖姑丈/太姑婆公"});
    relationshipMap.insert("f,f,f,ls,h", QStringList{"曾祖姑丈/太姑婆公"});
    relationshipMap.insert("f,f,f,f,ob,d,h", QStringList{"曾祖姑丈/太姑婆公"});
    relationshipMap.insert("f,f,f,f,lb,d,h", QStringList{"曾祖姑丈/太姑婆公"});
    relationshipMap.insert("f,f,f,f,ob", QStringList{"高伯祖父/老太公"});
    relationshipMap.insert("f,f,f,f,f,ob,s", QStringList{"高伯祖父/老太公"});
    relationshipMap.insert("f,f,f,f,ob,w", QStringList{"高伯祖母/老太婆"});
    relationshipMap.insert("f,f,f,f,f,ob,s,w", QStringList{"高伯祖母/老太婆"});
    relationshipMap.insert("f,f,f,f,lb", QStringList{"高叔祖父/老太公"});
    relationshipMap.insert("f,f,f,f,f,lb,s", QStringList{"高叔祖父/老太公"});
    relationshipMap.insert("f,f,f,f,lb,w", QStringList{"高叔祖母/老太婆"});
    relationshipMap.insert("f,f,f,f,f,lb,s,w", QStringList{"高叔祖母/老太婆"});
    relationshipMap.insert("f,f,f,f,os", QStringList{"高祖姑母/老太姑婆"});
    relationshipMap.insert("f,f,f,f,ls", QStringList{"高祖姑母/老太姑婆"});
    relationshipMap.insert("f,f,f,f,f,ob,d", QStringList{"高祖姑母/老太姑婆"});
    relationshipMap.insert("f,f,f,f,f,lb,d", QStringList{"高祖姑母/老太姑婆"});
    relationshipMap.insert("f,f,f,f,os,h", QStringList{"高祖姑丈/老太姑婆公"});
    relationshipMap.insert("f,f,f,f,ls,h", QStringList{"高祖姑丈/老太姑婆公"});
    relationshipMap.insert("f,f,f,f,f,ob,d,h", QStringList{"高祖姑丈/老太姑婆公"});
    relationshipMap.insert("f,f,f,f,f,lb,d,h", QStringList{"高祖姑丈/老太姑婆公"});
    relationshipMap.insert("m,f,f", QStringList{"大外祖父/外太公/太姥爷"});
    relationshipMap.insert("m,f,f,w", QStringList{"大外祖母/外太婆/太姥姥"});
    relationshipMap.insert("m,f,m", QStringList{"大外祖母/外太婆/太姥姥"});
    relationshipMap.insert("m,ob,w", QStringList{"舅母/舅妈"});
    relationshipMap.insert("m,lb,w", QStringList{"舅母/舅妈"});
    relationshipMap.insert("m,os,h", QStringList{"姨丈/姨夫"});
    relationshipMap.insert("m,ls,h", QStringList{"姨丈/姨夫"});
    relationshipMap.insert("m,ob,s", QStringList{"表哥/表弟"});
    relationshipMap.insert("m,lb,s", QStringList{"表哥/表弟"});
    relationshipMap.insert("m,ob,s,w", QStringList{"表嫂/表弟妇"});
    relationshipMap.insert("m,lb,s,w", QStringList{"表嫂/表弟妇"});
    relationshipMap.insert("m,ob,d", QStringList{"表姐/表妹"});
    relationshipMap.insert("m,ob,d,h", QStringList{"表姐夫/表妹夫"});
    relationshipMap.insert("m,lb,d", QStringList{"表姐/表妹"});
    relationshipMap.insert("m,lb,d,h", QStringList{"表姐夫/表妹夫"});
    relationshipMap.insert("m,os,s", QStringList{"表哥/表弟"});
    relationshipMap.insert("m,ls,s", QStringList{"表哥/表弟"});
    relationshipMap.insert("m,os,s,w", QStringList{"表嫂/表弟妇"});
    relationshipMap.insert("m,ls,s,w", QStringList{"表嫂/表弟妇"});
    relationshipMap.insert("m,os,d", QStringList{"表姐/表妹"});
    relationshipMap.insert("m,ls,d", QStringList{"表姐/表妹"});
    relationshipMap.insert("m,os,d,h", QStringList{"表姐夫/表妹夫"});
    relationshipMap.insert("m,ls,d,h", QStringList{"表姐夫/表妹夫"});
    relationshipMap.insert("m,f,os,s", QStringList{"表舅"});
    relationshipMap.insert("m,f,ls,s", QStringList{"表舅"});
    relationshipMap.insert("m,f,os,s,w", QStringList{"表妗"});
    relationshipMap.insert("m,f,ls,s,w", QStringList{"表妗"});
    relationshipMap.insert("m,f,os,d", QStringList{"表姨"});
    relationshipMap.insert("m,f,os,d,h", QStringList{"表姨夫"});
    relationshipMap.insert("m,f,ls,d", QStringList{"表姨"});
    relationshipMap.insert("m,f,ls,d,h", QStringList{"表姨夫"});
    relationshipMap.insert("m,m,ob", QStringList{"外舅祖父/外舅公"});
    relationshipMap.insert("m,m,lb", QStringList{"外舅祖父/外舅公"});
    relationshipMap.insert("m,m,ob,w", QStringList{"外舅祖母/外妗婆"});
    relationshipMap.insert("m,m,lb,w", QStringList{"外舅祖母/外妗婆"});
    relationshipMap.insert("m,f,ob", QStringList{"外伯祖父/外伯公"});
    relationshipMap.insert("m,f,lb", QStringList{"外叔祖父/外叔公"});
    relationshipMap.insert("m,f,ob,w", QStringList{"外伯祖母/外姆婆"});
    relationshipMap.insert("m,f,lb,w", QStringList{"外叔祖母/外婶婆"});
    relationshipMap.insert("m,f,f,ob,s", QStringList{"堂外伯祖父/堂外伯公"});
    relationshipMap.insert("m,f,f,lb,s", QStringList{"堂外叔祖父/堂外叔公"});
    relationshipMap.insert("m,f,f,ob,s,w", QStringList{"堂外伯祖母/堂外姆婆"});
    relationshipMap.insert("m,f,f,lb,s,w", QStringList{"堂外叔祖母/堂外婶婆"});
    relationshipMap.insert("m,f,os", QStringList{"外姑母/外姑婆"});
    relationshipMap.insert("m,f,ls", QStringList{"外姑母/外姑婆"});
    relationshipMap.insert("m,f,os,h", QStringList{"外姑丈/外姑婆公"});
    relationshipMap.insert("m,f,ls,h", QStringList{"外姑丈/外姑婆公"});
    relationshipMap.insert("m,f,f,ob,d", QStringList{"堂外姑母/堂外姑婆"});
    relationshipMap.insert("m,f,f,ob,d,h", QStringList{"堂外姑丈/堂外姑婆公"});
    relationshipMap.insert("m,f,f,lb,d", QStringList{"堂外姑母/堂外姑婆"});
    relationshipMap.insert("m,f,f,lb,d,h", QStringList{"堂外姑丈/堂外姑婆公"});
    relationshipMap.insert("w,f,f", QStringList{"太岳父"});
    relationshipMap.insert("w,f,m", QStringList{"太岳母"});
    relationshipMap.insert("w,f,f,w", QStringList{"太岳母"});
    relationshipMap.insert("w,ob,w", QStringList{"大妗"});
    relationshipMap.insert("w,lb,w", QStringList{"小妗"});
    relationshipMap.insert("w,os,h", QStringList{"襟兄"});
    relationshipMap.insert("w,ls,h", QStringList{"襟弟"});
    relationshipMap.insert("w,f,ob", QStringList{"伯岳父"});
    relationshipMap.insert("w,f,ob,w", QStringList{"伯岳母"});
    relationshipMap.insert("w,f,lb", QStringList{"叔岳父"});
    relationshipMap.insert("w,f,lb,w", QStringList{"叔岳母"});

}

