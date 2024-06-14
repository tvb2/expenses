#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <QObject>
#include <QWidget>
#include "dispatch.h"

class BaseComponent {
protected:
    Dispatch *dispatch_;

public:
    BaseComponent(Dispatch *dispatch = nullptr) : dispatch_(dispatch) {
    }
    void set_dispatch(Dispatch *dispatch) {
        this->dispatch_ = dispatch;
    }
};

#endif // BASECOMPONENT_H
