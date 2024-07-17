#ifndef DISPATCH_H
#define DISPATCH_H

#include <QWidget>
#include <QStandardPaths>
#include <QDir>

class BaseComponent;
/*
 * Manage navigation in the app and call various
 * functions and other classes as needed
 */

class Dispatch{
public:
    virtual void Notify(BaseComponent *sender, std::string event) const = 0;
    virtual void Notify(QWidget *sender, std::string event) const = 0;
};

#endif // DISPATCH_H
