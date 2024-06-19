#include "profile.h"

Profile::Profile() {}
void Profile::DoA() {
    qDebug ("Profile does Pr");
    this->dispatch->Notify(this, "Pr");
}
