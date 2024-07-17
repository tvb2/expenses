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

public:
    explicit CreateProfile(QStringList const &e = {""}, QWidget *parent = nullptr);
    ~CreateProfile();
    //check if there is no existing profile with the same name as a new one
    bool isUniq(QString const &name);

signals:
    /**
     * @brief send only full path
     * @param path
     */
    void setDBPath(QString &path);
    /**
     * @brief send only profile name as typed in the field
     * @param name
     */
    void setProfileName(QString &name);
    /**
     * @brief send name only; default currency and period
     * @param name
     * @param settings
     */
    void setSettings(QString const & name, QVariantMap &settings);

private slots:
    void on_pbCreateProfile_clicked();

private:
    Ui::CreateProfile *ui;
    QStringList existing = {""}; //existing profile names
    QStringList periods = { "monthly", "weekly"};//default averaging period
};

#endif // CREATEPROFILE_H
