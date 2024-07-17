#include <QApplication>
#include <QObject>
#include <QLineEdit>
#include <QPushButton>

#include "mainwindow.h"
#include <QDebug>
#include <memory.h>

#include "concretedispatch.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug("start");
    a.setOrganizationDomain("github.com/tvb2/expenses");
    a.setApplicationName("expensesApp");


    Profile *profile = new Profile;
    Database *db = new Database;
    Settings *settings = new Settings;
    ConcreteDispatch *dispatch = new ConcreteDispatch(profile, db, settings);

    //launch start module and hand over selected DB to DB manager
    dispatch->Launcher();

    return a.exec();
}
