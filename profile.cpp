#include "profile.h"

Profile::Profile() {}


void Profile::setPath(QString const &path){
    this->dbPath = path;
    qDebug() << "Profile DB path set: " << this->dbPath;
}
void Profile::searchProfiles(){
    QVector<QString> item;
    QVector<QVector<QString>> profiles;

    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) qFatal("Cannot determine settings storage location");
    QDir d{path};
    QString thePath;
    if (d.mkpath(d.absolutePath()) && QDir::setCurrent(d.absolutePath())) {
        thePath = QDir::currentPath();
        qDebug() << "current path: " << thePath;// QDir::currentPath();
    }
    QStringList filter = {"*.sqlite"};
    this->names = d.entryList(filter);
    for (auto i:names){
        this->profiles.append(d.absoluteFilePath(i));
        qDebug() << i;
    }
    qDebug("QString list derived");
}
QStringList const & Profile::getProfiles(){
    return this->profiles;
}
QString const & Profile::getCurrentProfile(){
    return this->dbPath;
}
bool Profile::isEmpty(){
    return this->profiles.isEmpty();
}
int Profile::size(){
    return this->profiles.size();
}

QStringList const & Profile::getProfilesNames(){
    this->searchProfiles();
    for (int n = 0; n < this->names.size(); ++n){
        names[n] = names[n].mid(0,names[n].lastIndexOf(".sqlite"));

    }
    return names;
}
