#include "concretedispatch.h"

void ConcreteDispatch::Notify(BaseComponent *sender, std::string event) const {
    if (event == "Pr") {
        qDebug ("Dispatch recieves PROFILE and triggers following operations: ");
    }
    if (event == "DB") {
        qDebug ("Dispatch recieves DATABASE and triggers following operations: ");
    }
}
