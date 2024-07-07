#ifndef CREATEPROFILE_H
#define CREATEPROFILE_H

#include <QDialog>
#include <QComboBox>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class CreateProfile;
}

class CreateProfile : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProfile(QStringList const &e = {""}, QWidget *parent = nullptr);
    ~CreateProfile();
    //check if there is no existing profile with the same name as a new one
    bool isUniq(QString const &name);

signals:
    void setProfileName(QString &nm);

private slots:
    void on_pbCreateProfile_clicked();

private:
    Ui::CreateProfile *ui;
    QStringList existing = {""}; //existing profile names
    QStringList periods = { "monthly", "weekly"};//default averaging period
};

#endif // CREATEPROFILE_H
