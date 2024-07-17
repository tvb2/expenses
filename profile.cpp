#include "profile.h"

Profile::Profile() {
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty())
        qFatal("Profile: Cannot determine storage location");
    this->dir = path;
}

void Profile::searchProfiles(){
    QString thePath;
    if (this->dir.mkpath(this->dir.absolutePath()) && QDir::setCurrent(this->dir.absolutePath())) {
        thePath = QDir::currentPath();
        qDebug() << "Profile: current path: " << thePath;// QDir::currentPath();
    }

    QStringList filter = {"*.sqlite"};

    //update filenames member (with extension)
    this->files.clear();
    this->files = this->dir.entryList(filter);

    //update profiles member (full paths)
    this->profiles.clear();
    for (auto i:this->files){
        this->profiles.append(this->dir.absoluteFilePath(i));
        qDebug() << "found file: " << i ;
    }

    //update names member (no extension)
    this->names.clear();
    foreach(auto i, this->files){
        this->names.append(i.mid(0,i.lastIndexOf(".sqlite")));
    }
    qDebug("QString list derived");
}
