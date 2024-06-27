#include "database.h"

Database::Database() {}

void Database::addExpense(){
    qDebug("Add expenses to database");
}

void Database::setDB(QString const &path){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        QSqlQuery databaseQuery(this->db);
        databaseQuery.prepare("CREATE TABLE IF NOT EXISTS expenses (id int not null primary key, tu text, data BLOB, puits integer);");
        qDebug() << "DB path set: " << path;
    }
}
