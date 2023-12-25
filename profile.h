#ifndef PROFILE_H
#define PROFILE_H

#include <QtSql>
#include <QApplication>
#include <QString>


class Profile
{
public:
    Profile();
    Profile(QSqlDatabase &db);

    QSqlDatabase & selectProfile();
    QString createProfile(QApplication &a);
    void deleteProfile();
    void backupProfile();

};

#endif // PROFILE_H
