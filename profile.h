#ifndef PROFILE_H
#define PROFILE_H

#include "basecomponent.h"

#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <map>

struct Account
{
    QString fullPath;
    QString file;
    QString name;
};

class Profile : public BaseComponent
{

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
     * @brief add a single profile
     * @param profiles
     */
    void createProfile(QString const & newProfileName);

    /**
     * this->profiles is empty
     */
    bool isEmpty(){
        return this->accounts.empty();
    }

    /**
     * size of this->profiles
     */
    int size(){
        return this->accounts.size();
    }

    /**
    * only names of profiles w/o extensions
    */
    QStringList const & getProfileNames(QStringList &target){
        target.clear();
        for (auto l:this->accounts)
            target.append(l.second.name);
        return target;
    }

    /*
     *return current profile with full path
     */
    QString const & getCurrentProfilePath(){
            return this->path;
    }

    /**
     * current profile name without extension
     */
    QString const & getCurrentProfileName(){
        return this->profileName;
    }

public slots:

    /**
     * @brief set profileName (name only)
     * @param name
     */
    void setCurrentProfile(QString const &name){
        if (this->accounts.find(name) != this->accounts.end()){
            this->profileName = name;
            this->path = this->accounts[name].fullPath;
        }
        else
            qDebug("Profile::setCurrentProfile >> no such profile!!!");
    }
private:
    std::map<QString, Account> accounts;
    QString path;//current profile path
    QDir dir; //current app dir
    QString profileName; //current profile name without extension

    /**
     * @brief add several profiles
     * @param profiles
     */
    void addProfiles(QStringList const & profiles);

};

#endif // PROFILE_H
