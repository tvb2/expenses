#include "profile.h"

Profile::Profile() {}
void Profile::DoA() {
    qDebug ("Profile does Pr");
    this->dispatch->Notify(this, "Pr");
}

void Profile::setPath(QString &path){
    this->dbPath = path;
    qDebug() << "Profile DB path set: " << this->dbPath;
}
