#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, ConcreteDispatch *d)
    : QMainWindow(parent)
    , dsptch(d)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getDispatch(ConcreteDispatch *d){
    this->dsptch = d;
}

void MainWindow::getObjects(ConcreteDispatch *d,
                Profile *p,
                Database *db,
                Settings *s){
    this->dsptch = d;
    this->profile = p;
    this->database = db;
    this->settings = s;
}

void MainWindow::on_pushButton_clicked(){
    this->profile->DoA();
    this->database->DoD();

}

