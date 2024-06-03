#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "expression.h"
#include "numberExpression.h"
#include "binaryExpression.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    void printTree(Expression *node);
    string error;
    bool resetDisplay = false;
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void expandExpression();
    void clearBtnPressed();
    void clearAllBtnPressed();
    int equalBtnPressed();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
