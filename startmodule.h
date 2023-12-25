#ifndef STARTMODULE_H
#define STARTMODULE_H


#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QVector>
#include <QString>

#include <QDialog>

namespace Ui {
class Startmodule;
}

class Startmodule : public QDialog
{
    Q_OBJECT

public:
    explicit Startmodule(QWidget *parent = nullptr);
    ~Startmodule();

    //search app directory and find all existing profiles
    void getExistingProfiles();

    //return selected profile (db file)
    QDir selectProfile();

private slots:
    void on_okPB_clicked();

private:
    Ui::Startmodule *ui;
    QString extension = ".sqlite"; //expected extension of database (=profile) file
};

#endif // STARTMODULE_H
