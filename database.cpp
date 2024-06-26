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
        databaseQuery.exec("CREATE TABLE expenses "
                           "(id int primary key, "
                           "data date,"
                           "category text, "
                           "amount float, "
                           "currency text, "
                           "reg int)");
        qDebug() << "DB path set: " << path;
    }
}

bool Database::addExpense(const QString& cat)
{
    bool success = false;
    // you should check if args are ok first...
    QSqlQuery query;
    query.prepare("INSERT INTO expenses (category, amount, currency, reg) "
                  "VALUES (:category, :amount, :currency, :reg)");
    // query.prepare("INSERT INTO expenses (category, amount, currency, regular) "
    //               "VALUES (:category, :amount, :currency, :reg)");
    query.bindValue(":category", "laundry");
    query.bindValue(":amount", 67.9f);
    query.bindValue(":currency", "CAD");
    query.bindValue(":reg", 1);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addExpense error:"
                 << query.lastError();
    }

    return success;
}

void Database::printExpenses(){
QSqlQuery query("SELECT id, category, amount, currency, reg FROM expenses");
    QStringList str;
    QVector<QStringList> list;
    if (!query.exec()) {
        qDebug() << "Query failed!";
    } else {
        while (query.next()){
                str.append(query.value("id").toString());
                str.append(query.value("category").toString());
                str.append(query.value("amount").toString());
                str.append(query.value("currency").toString());
                str.append(query.value("reg").toString());
                list.append(str);
                str.clear();
            }
        }
    foreach (auto i, list) {
        QString out = "";
        foreach(auto j, i){
            out += j + " ";
        }
        qDebug() << out;
        out.clear();
            }

}
