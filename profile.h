#ifndef PROFILE_H
#define PROFILE_H

#include <QDebug>
#include <QDir>

#include "basecomponent.h"

class Profile : public BaseComponent
{
private:
    QString dbPath;//current db path
    QDir dir;
    QStringList profiles; //all found profile paths and names in the working dir
    QStringList files; //all found profile names in the working dir
    QStringList names; //all found profile names in the working dir
public:
    Profile();



    /*
     * search profiles in the dbPath
     * populate member profiles (full path)
     * populate member files (only filenames with extension)
     * populate member names (only filenames without extension)
     */
    void searchProfiles();

    //this->profiles is empty

    bool isEmpty();
    //size of this->profiles

    int size();

    /*
     * get list of all profiles with paths
     */
    QStringList const  & getProfiles();

    /*
     * get profile filenames with extensions
     */
    QStringList const & getProfileFileNames();

    /*
    only get names of profiles without path
    */
    QStringList const & getProfileNames();

    /*
     *return current profile with full path
     */
    QString const & getCurrentProfile();


public slots:

    /*
     * set path for the current profile
     */
    void setPath(QString const &path);
};

#endif // PROFILE_H
