#include "profile.h"

Profile::Profile() {
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty())
        qFatal("Profile: Cannot determine storage location");
    this->dir = path;
}

void Profile::searchProfiles(){
    if (this->dir.mkpath(this->dir.absolutePath()) && QDir::setCurrent(this->dir.absolutePath())) {
        qDebug() << "Profile: current path: " << QDir::currentPath();// QDir::currentPath();
    }

    QStringList filter = {"*.sqlite"};
    this->accounts.clear();
    addProfiles(filter);
}

/**
 * @brief multiple profiles as a QStringList of full path
 * @param profiles
 */
void Profile::addProfiles(QStringList const & profiles){
    //update files member (*.sqlite files with extensions)
    QStringList fileList = this->dir.entryList(profiles);

    foreach (auto i, fileList) {
        QString name = i.mid(0,i.lastIndexOf(".sqlite"));
        QString prof = this->dir.absoluteFilePath(i);
        accounts[name].file = i;
        accounts[name].fullPath = prof;
        accounts[name].name = name;
    }
}

/**
 * @brief add single profile. Update current profile name and path
 * @param profile
 */
void Profile::addProfile(QString const &newProfileName){
    this->accounts[newProfileName].name = newProfileName;
    this->profileName = newProfileName;
    QString newFile = newProfileName + ".sqlite";
    this->accounts[newProfileName].file = newFile;
    this->accounts[newProfileName].fullPath =
        this->dir.absolutePath()
        + "/"
        + newFile;
    this->path = this->accounts[newProfileName].fullPath;
}
