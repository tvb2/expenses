#ifndef PROFILECREATE_H
#define PROFILECREATE_H

#include <QWidget>
#include <QStandardPaths>
#include <QDir>
#include <QSqlDatabase>
#include <QCloseEvent>

namespace Ui {
class ProfileCreate;
}

class ProfileCreate : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileCreate(QWidget *parent = nullptr);
    ~ProfileCreate();
    void createProfile();

private slots:
    //create new profile
    void on_createPB_clicked();

private:
    Ui::ProfileCreate *ui;
    QString extension = ".sqlite";
};

#endif // PROFILECREATE_H
