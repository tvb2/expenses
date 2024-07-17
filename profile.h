#ifndef PROFILE_H
#define PROFILE_H

#include <QDebug>
#include <QDir>

#include "basecomponent.h"

class Profile : public BaseComponent
{
private:
    QString dbPath;//current db path
    QDir dir; //current app dir
    QStringList profiles; //all found profile paths and names in the working dir
    QStringList files; //all found profile names with extensions in the working dir
    QStringList names; //all found profile names w/o extensions in the working dir
    QString profileName; //current profile name without extension
public:
    Profile();



    /**
     * search profiles in the dbPath
     * populate members profiles (full path),
     * files (filenames with ext),
     * names (filenames w/0 ext)
     * current profile name (w/o ext)
     */
    void searchProfiles();

    /**
     * this->profiles is empty
     */
    bool isEmpty(){
            return this->profiles.isEmpty();
    }

    /**
     * size of this->profiles
     */
    int size(){
        return this->profiles.size();
    }

    /**
     * list of all profiles with paths
     */
    QStringList const  & getProfiles(){
            return this->profiles;
    }

    /**
     * list of profile filenames with extensions
     */
    QStringList const & getProfileFileNames(){
            return this->files;
    }

    /**
    * only names of profiles w/o extensions
    */
    QStringList const & getProfileNames(){
            return this->names;
    }

    /*
     *return current profile with full path
     */
    QString const & getCurrentProfile(){
            return this->dbPath;
    }

    /**
     * current profile name without extension
     */
    QString const & getCurrentProfileName(){
        return this->profileName;
    }

public slots:

    /**
     * set path for the current profile (including filename+ext
     */
    void setPath(QString const &path){
        this->dbPath = path;
        qDebug() << "Profile DB path set: " << this->dbPath;
    }
    /**
     * @brief set profileName (name only)
     * @param name
     */
    void setName(QString const &name){
        this->profileName = name;
    }
};

#endif // PROFILE_H
