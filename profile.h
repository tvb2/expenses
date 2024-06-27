#ifndef PROFILE_H
#define PROFILE_H

#include <QDebug>

#include "basecomponent.h"

class Profile : public BaseComponent
{
private:
    QString dbPath;
    QStringList profiles;
public:
    Profile();

    //set profile path
    void setPath(QString const &path);

    //search profiles in the dbPath
    void searchProfiles();

    //this->profiles is empty
    bool isEmpty();
    //size of this->profiles
    int size();
    //get profiles list
    QStringList const  & getProfiles();
    //return current profile
    QString const & getCurrentProfile();
};

#endif // PROFILE_H
