#ifndef CREATEPROFILE_H
#define CREATEPROFILE_H

#include <QDialog>
#include <QComboBox>
#include <QMessageBox>
#include <QCloseEvent>
#include <QStandardPaths>

namespace Ui {
class CreateProfile;
}

class CreateProfile : public QDialog
{
    Q_OBJECT
private:
    Ui::CreateProfile *ui;
    QStringList existing = {""}; //existing profile names
    QStringList periods = { "monthly", "weekly"};//default averaging period

public:
    explicit CreateProfile(QStringList const &e = {""}, QWidget *parent = nullptr);
    ~CreateProfile();
    //check if there is no existing profile with the same name as a new one
    bool isUniq(QString const &name);

signals:

    /**
     * @brief send name only; send default settings
     * @param name
     * @param settings
     */
    void profileCreated(QString const &name, QVariantMap const &settings);

private slots:
    void on_pbCreateProfile_clicked();
};

#endif // CREATEPROFILE_H
