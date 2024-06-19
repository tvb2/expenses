#ifndef CONCRETEDISPATCH_H
#define CONCRETEDISPATCH_H

#include <QDebug>

#include "dispatch.h"
#include "profile.h"
#include "database.h"
#include "settings.h"

class ConcreteDispatch : public Dispatch
{
private:
    Profile *profile;
    Database *db;
    Settings *settings;
public:
    ConcreteDispatch(Profile *pr, Database *databs, Settings *st) : profile(pr), db(databs), settings(st) {
        this->profile->set_dispatch(this);
        this->db->set_dispatch(this);
        this->settings->set_dispatch(this);
    }

void Notify(BaseComponent *sender, std::string event) const override;


};

#endif // CONCRETEDISPATCH_H
