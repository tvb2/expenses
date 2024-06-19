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
    Profile *profile;
    Database *database;
    Settings *settings;

public:
    explicit MainWindow(QWidget *parent = nullptr,ConcreteDispatch *d = nullptr);
    ~MainWindow();

    void getDispatch(ConcreteDispatch *d = nullptr);
    void getObjects(ConcreteDispatch *d = nullptr,
                    Profile *p = nullptr,
                    Database *db = nullptr,
                    Settings *s = nullptr);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
