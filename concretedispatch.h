#ifndef CONCRETEDISPATCH_H
#define CONCRETEDISPATCH_H

#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QVector>
#include <QStringList>

#include "dispatch.h"
#include "profile.h"
#include "database.h"
#include "settings.h"
#include "widgets/createprofile.h"

class ConcreteDispatch : public Dispatch
{
public:
    Profile *profile;
    Database *db;
    Settings *settings;

    ConcreteDispatch(Profile *pr, Database *databs, Settings *st) : profile(pr), db(databs), settings(st) {
        this->profile->set_dispatch(this);
        this->db->set_dispatch(this);
        this->settings->set_dispatch(this);
    }

void Notify(BaseComponent *sender, std::string event) const override;

//run when starting the app
void Launcher();

};

#endif // CONCRETEDISPATCH_H
