#include "widget.h"
#include "ui_widget.h"
#include "evaluator.h"
#include "syntaxKind.h"
#include "parser.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPushButton *numButtons[10];

    //save numbered buttons in an array and assign connect to them
    for(int i = 0; i < 10; i++) {
        QString btnName = "n" + QString::number(i);
        numButtons[i] = Widget::findChild<QPushButton *>(btnName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(expandExpression()));
    }

     connect(Widget::findChild<QPushButton *>("add"), SIGNAL(released()), this, SLOT(expandExpression()));
     connect(Widget::findChild<QPushButton *>("sub"), SIGNAL(released()), this, SLOT(expandExpression()));
     connect(Widget::findChild<QPushButton *>("mul"), SIGNAL(released()), this, SLOT(expandExpression()));
     connect(Widget::findChild<QPushButton *>("div"), SIGNAL(released()), this, SLOT(expandExpression()));
     connect(Widget::findChild<QPushButton *>("dot"), SIGNAL(released()), this, SLOT(expandExpression()));
     connect(Widget::findChild<QPushButton *>("openP"), SIGNAL(released()), this, SLOT(expandExpression()));
     connect(Widget::findChild<QPushButton *>("closeP"), SIGNAL(released()), this, SLOT(expandExpression()));
     connect(Widget::findChild<QPushButton *>("clear"), SIGNAL(released()), this, SLOT(clearBtnPressed()));
     connect(Widget::findChild<QPushButton *>("clearAll"), SIGNAL(released()), this, SLOT(clearAllBtnPressed()));
     connect(Widget::findChild<QPushButton *>("equal"), SIGNAL(released()), this, SLOT(equalBtnPressed()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::expandExpression()
{
    //add a character assigned to the pressed button to the display
    QPushButton *btn = (QPushButton *)sender();
    QString btnValue = btn->text();
    QString displayValue = ui->display->text();

    //initial state, blank display
    if(displayValue == "0.00" || resetDisplay) {
        ui->display->setText(btnValue);
    }
    //if the display is no longer blank
    else {
        QString newValue = displayValue + btnValue;
        ui->display->setText(displayValue + btnValue);
    }
    resetDisplay = false;
}

void Widget::clearBtnPressed() {
    QString displayValue = ui->display->text();

    if(displayValue.size() > 0) {
        QString c = displayValue.last(1);

        if(QString::compare(c, " ", Qt::CaseInsensitive) == 0) {
             //delete empty space, then mathematical operator and delete the empty space before it
             displayValue.chop(3);
        }
        else {
            displayValue.chop(1);
        }
        ui->display->setText(displayValue);
    }
}

void Widget::clearAllBtnPressed() {
     ui->display->setText("");
}

int Widget::equalBtnPressed() {
    error = "";
    string displayValue = ui->display->text().toStdString();

    if(displayValue == "") {
        return -1;
    }

    Parser *parser = new Parser(displayValue, &error);
    Expression *expression = parser->parse();
    Evaluator* eva = new Evaluator(expression);
    double result = eva->evaluate();
    resetDisplay = true;

    if(error != "") {
        ui->display->setText(QString::fromStdString(error));
        return -1;
    }

    QString newText = QString::number(result);
    if(QString::compare(newText, "inf") == 0) {
         ui->display->setText("Hiba: nullával nem osztunk");
         return -1;
    }

    ui->display->setText(QString::number(result));
}
