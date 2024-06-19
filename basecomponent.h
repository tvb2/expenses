#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <QObject>
#include <QWidget>
#include "dispatch.h"

class BaseComponent {
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
