#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <QObject>
#include <QWidget>
#include "dispatch.h"

class BaseComponent : public QObject {//inherit from QObject to use singals and slots in child classes
    Q_OBJECT
protected:
    Dispatch *dispatch;

public:
    BaseComponent(Dispatch *disp = nullptr) : dispatch(disp) {
    }
    void set_dispatch(Dispatch *dispatch) {
        this->dispatch = dispatch;
    }
};

#endif // BASECOMPONENT_H
