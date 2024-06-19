#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "concretedispatch.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    ConcreteDispatch *dsptch;

public:
    explicit MainWindow(QWidget *parent = nullptr,ConcreteDispatch *d = nullptr);
    ~MainWindow();

    void getDispatch(ConcreteDispatch *d = nullptr);

private slots:
    void on_pushButton_clicked();

    void on_pB_Submit_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
