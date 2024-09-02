#ifndef SETTINGSBUNDLE_H
#define SETTINGSBUNDLE_H

#include "QJsonObject"
#include "QVariant"
#include <QDate>

struct SettingsBunlde
{
    QJsonObject settings; //all json fields to be written to file

    QVariantMap exchRates;
    QVariantMap general;

    QVariantList regCat;
    QVariantList nonRegCat;

};
#endif // SETTINGSBUNDLE_H
