#include "database.h"

Database::Database() {}

void Database::DoD() {
    qDebug ("Database does DB");
    this->dispatch->Notify(this, "DB");
}
