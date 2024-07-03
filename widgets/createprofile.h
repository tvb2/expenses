#ifndef CREATEPROFILE_H
#define CREATEPROFILE_H

#include <QDialog>

namespace Ui {
class CreateProfile;
}

class CreateProfile : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProfile(QWidget *parent = nullptr);
    ~CreateProfile();
signals:
    void setProfileName(QString &nm);

private slots:
    void on_pbCreateProfile_clicked();

private:
    Ui::CreateProfile *ui;
};

#endif // CREATEPROFILE_H
