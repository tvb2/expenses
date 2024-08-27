#include "database.h"

Database::Database(){
    this->path= QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty())
        qFatal("Database constructor: Cannot determine storage location");
    this->dir = path;
}

void Database::createDB(QString const &name){
    db = QSqlDatabase::addDatabase("QSQLITE");
    this->path =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
                 + "/"
                 + name
                 + ".sqlite";
    db.setDatabaseName(path);

    if (!db.open())
    {
        qDebug() << "Database::createDB. Error: connection with database failed";
    }
    else
    {
        QSqlQuery databaseQuery(this->db);
        databaseQuery.exec("CREATE TABLE expenses "
                           "(data date,"
                           "category text, "
                           "amount float, "
                           "currency text, "
                           "exchRate float, "
                           "finalAmount float, "
                           "reg int, "
                           "lastChangeDateTime text)");
        qDebug() << "Database::createDB. DB created: " << this->path;
    }
}

void Database::setCurrentDB(QString const &name){
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->path =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
        + "/"
        + name
        + ".sqlite";
    db.setDatabaseName(path);
    if (!db.open())
    {
        qDebug() << "Database::setCurrentDB. Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database::setCurrentDB. DB connection successful: " << this->path;
    }
}

bool Database::addRecord(Record const &record)
{
    qDebug("Databse::addRecord recieved signal");
    qDebug() << record.amount << "amount recieved";
    qDebug() << record.date << "date recieved";
    qDebug() << record.reg << " regular recieved";

    QString dateNow=QDateTime::currentDateTime().toString(Qt::DateFormat(1));//2024-08-25T10:30:51
    bool success = false;
    // you should check if args are ok first...
    QSqlQuery query;
    query.prepare("INSERT INTO expenses (data, category, amount, currency, exchRate, finalAmount, reg, lastChangeDateTime) "
                  "VALUES (:data, :category, :amount, :currency, :exchRate, :finalAmount, :reg, "
                  ":lastChDateTime)");

    query.bindValue(":data", record.date);
    query.bindValue(":category", record.cat);
    query.bindValue(":amount", record.amount);
    query.bindValue(":currency", record.currency);
    query.bindValue(":exchRate", record.rate);
    query.bindValue(":finalAmount", record.finalAmnt);
    query.bindValue(":reg", record.reg);
    query.bindValue(":lastChDateTime", dateNow);
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
                str.append(query.value("regular").toString());
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

void Database::getLatestN(int N){
    this->latest.clear();
    Record record;
    bool success = false;
    // you should check if args are ok first...
    if (!this->db.open())
    {
        qDebug() << "Database::getLatestN. Error: connection with database failed";
    }
    else{
        QString an = QString::number(N);
        QSqlQuery query;
        query.prepare("SELECT * FROM expenses ORDER BY lastChangeDateTime DESC LIMIT " + an);

        if(query.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "getLatestN error:"
                     << query.lastError();
        }
        while (query.next()) {
            this->latest.append(record);
            this->latest[this->latest.size() - 1].date = query.value(0).toString();
            this->latest[this->latest.size() - 1].cat = query.value(1).toString();
            this->latest[this->latest.size() - 1].amount = query.value(2).toDouble();
            this->latest[this->latest.size() - 1].currency = query.value(3).toString();
            this->latest[this->latest.size() - 1].rate = query.value(4).toDouble();
            this->latest[this->latest.size() - 1].finalAmnt = query.value(5).toDouble();
            this->latest[this->latest.size() - 1].chngDate = query.value(7).toString();
            qDebug() << this->latest[this->latest.size() - 1].date << " " << this->latest[this->latest.size() - 1].cat << " "
                     <<this->latest[this->latest.size() - 1].amount << " " << this->latest[this->latest.size() - 1].currency << " "
                     <<this->latest[this->latest.size() - 1].rate << " " << this->latest[this->latest.size() - 1].finalAmnt << " "
                     <<this->latest[this->latest.size() - 1].chngDate;
        }
    }
    if (!this->latest.empty())
        emit getLatest(this->latest);
}

double Database::getAverage(QString period){
    bool success = false;
    // you should check if args are ok first...
    if (!this->db.open())
    {
        qDebug() << "Database::getAverage Error: connection with database failed";
    }
    else{
        QString condition;
        if (period == "weekly"){
//to be completed
        }
        else if (period == "monthly"){

        }
        QSqlQuery query;
        query.prepare("SELECT AVG(finalAmount) FROM expenses WHERE data>'2024-08-25' ");

        if(query.exec())
        {
            query.next();
            return query.value(0).toDouble();
        }
        else
        {
            qDebug() << "getLatestN error:"
                     << query.lastError();
        }
    }
}
