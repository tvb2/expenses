#ifndef PROFILE_H
#define PROFILE_H

#include <QtSql>

class Profile
{
public:
    Profile();
    Profile(QSqlDatabase &db);

    QSqlDatabase & selectProfile();
    QSqlDatabase & createProfile();
    void deleteProfile();
    void backupProfile();

};

#endif // PROFILE_H
