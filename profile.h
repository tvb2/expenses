#ifndef PROFILE_H
#define PROFILE_H

#include <QDebug>

#include "basecomponent.h"

class Profile : public BaseComponent
{
private:
    QString dbPath;
public:
    Profile();
    void DoA();

    //set path for database
    void setPath(QString &path);
};

#endif // PROFILE_H
