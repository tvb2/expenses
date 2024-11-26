#include "allexpenses.h"
#include "ui_allexpenses.h"

AllExpenses::AllExpenses(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AllExpenses)
{
    ui->setupUi(this);
}

AllExpenses::~AllExpenses()
{
    delete ui;
}
