#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QMap>
#include <QStringList>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void appendRelation();
    void onDelClicked();
    void onClrClicked();
    void onCalcClicked();

private:
    void initRelationshipMap();
    QString calculateRelationship(const QString &relationship);

private:
    Ui::Calculator *ui;
    QMap<QString, QStringList> relationshipMap;
};
#endif // CALCULATOR_H
