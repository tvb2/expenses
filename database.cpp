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
                           "(id int NOT NULL PRIMARY KEY,"
                           "data date,"
                           "category text, "
                           "amount float, "
                           "currency text, "
                           "exchRate float, "
                           "finalAmount float, "
                           "reg int, "
                           "lastChangeDateTime text,"
                           ")");
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
        //check if expense date is before global startDate, then update global startDate
        startDateCheck(QDate::fromString(record.date,"yyyy-MM-dd"), getLatestRowID());
    }
    else
    {
        qDebug() << "Database::addExpense error:"
                 << query.lastError();
    }
    if (record.reg)
        emit total(record.cat,record.finalAmnt);
    else
        emit nonReg(record.finalAmnt);
    return success;
}

void Database::getRecord(Record &record, int64_t id){
    bool success = false;
    // you should check if args are ok first...
    if (!this->db.open())
    {
        qDebug() << "Database::getRecord. Error: connection with database failed";
    }
    else{
        QSqlQuery query;
        QString rowID = QString::number(id);
        query.prepare("SELECT "
                      "rowid, data, category, amount, currency, exchRate, finalAmount, lastChangeDateTime, reg "
                      "FROM expenses "
                      "WHERE rowid = " + rowID);

        if(query.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "Database::getRecord error:"
                     << query.lastError();
        }
        while (query.next()) {
            record.id = query.value(0).toInt();
            record.date = query.value(1).toString();
            record.cat = query.value(2).toString();
            record.amount = query.value(3).toDouble();
            record.currency = query.value(4).toString();
            record.rate = query.value(5).toDouble();
            record.finalAmnt = query.value(6).toDouble();
            record.chngDate = query.value(7).toString();
            record.reg = query.value(8).toBool();
        }
    }
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
        //if N > 0 return N records. Otherwise return all records
        if (N > 0)
            query.prepare("SELECT rowid, data, category, amount, currency, exchRate, finalAmount, lastChangeDateTime "
                          "FROM expenses "
                          "ORDER BY lastChangeDateTime "
                          "DESC LIMIT " + an);
        else if (N == -1)
            query.prepare("SELECT rowid, data, category, amount, currency, exchRate, finalAmount, lastChangeDateTime "
                          "FROM expenses "
                          "ORDER BY lastChangeDateTime DESC");

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
            this->latest[this->latest.size() - 1].id = query.value(0).toInt();
            this->latest[this->latest.size() - 1].date = query.value(1).toString();
            this->latest[this->latest.size() - 1].cat = query.value(2).toString();
            this->latest[this->latest.size() - 1].amount = query.value(3).toDouble();
            this->latest[this->latest.size() - 1].currency = query.value(4).toString();
            this->latest[this->latest.size() - 1].rate = query.value(5).toDouble();
            this->latest[this->latest.size() - 1].finalAmnt = query.value(6).toDouble();
            this->latest[this->latest.size() - 1].chngDate = query.value(7).toString();
           /* qDebug() << "Latest transactions: \n"
                    << this->latest[this->latest.size() - 1].date << " " << this->latest[this->latest.size() - 1].cat << " "
                     <<this->latest[this->latest.size() - 1].amount << " " << this->latest[this->latest.size() - 1].currency << " "
                     <<this->latest[this->latest.size() - 1].rate << " " << this->latest[this->latest.size() - 1].finalAmnt << " "
                     <<this->latest[this->latest.size() - 1].chngDate;
            */
        }
    }
    if (!this->latest.empty())
        emit latestRecords(this->latest);
}

void Database::getRegTotals(QString const & cat){
    bool success = false;
    // you should check if args are ok first...
    if (!this->db.open())
    {
        qDebug() << "Database::getTotals. Error: connection with database failed";
    }
    else{
        //regular categories
        QSqlQuery query;
        query.prepare("SELECT SUM(finalAmount) FROM expenses WHERE"
                      " category = '" + cat + "'" +
                      " AND reg = 1");

        if(query.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "Database::getTotals (regular) error:"
                     << query.lastError();
        }
        while (query.next()) {
            qDebug() << "Cat: " << cat << " total = " << query.value(0).toDouble();
            emit total(cat, query.value(0).toDouble());
        }
    }
}

void Database::getNonRegTotals(){
        bool success = false;
        //non-regular categories
        QSqlQuery queryNonReg;
        queryNonReg.prepare("SELECT SUM(finalAmount) FROM expenses WHERE reg = 0");
        if(queryNonReg.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "Database::getTotals (non-regular) error:"
                     << queryNonReg.lastError();
        }
        while (queryNonReg.next()) {
            emit totalNonReg(queryNonReg.value(0).toDouble());
        }
}

//Following functions work together

//private
QString Database::startDate(QString period){
    QDate targetStart = QDate::currentDate();
    if (period == Periods::weekly){
        qint64 today = QDate::currentDate().dayOfWeek();
        targetStart = QDate::fromJulianDay(QDate::currentDate().toJulianDay() - today);
    }
    else if (period == Periods::monthly){
        targetStart = QDate(QDate::currentDate().year(),QDate::currentDate().month(),1);
    }
    else if (period == Periods::overall){
        targetStart = this->sDate;
    }
    else{
        qDebug() << "Database::periodRegTotal. Something wrong with default period!";
        return 0;
    }
    return targetStart.toString("yyyy-MM-dd");
}

double Database::periodRegTotal(QString period){
        QString queryText = "SELECT SUM(finalAmount) FROM expenses WHERE "
                            "data >= '" + startDate(period) + "'" +
                      " AND reg = 1" +
                      " AND category != 'Income'";
        return executeQuery(queryText);
}

double Database::periodNonRegTotal(QString period){

        QString queryText = "SELECT SUM(finalAmount) FROM expenses WHERE"
                        " data >= '" + startDate(period) + "'" +
                      " AND reg = 0";
        return executeQuery(queryText);
}

double Database::periodIncomeTotal(QString period){
    QString queryText = "SELECT SUM(finalAmount) FROM expenses WHERE"
                        " data >= '" + startDate(period) + "'" +
                        " AND category = 'Income'";
    return executeQuery(queryText);
}

double Database::periodBalance(QString period){
    double balance{0};
    balance +=
        periodIncomeTotal(period) -
        periodRegTotal(period) -
        periodNonRegTotal(period);
    return balance;
}

double Database::periodTotal(QString period){

    QString queryText = "SELECT SUM(finalAmount) FROM expenses WHERE"
                        " data >= '" + startDate(period) + "'" +
                        " AND category != 'Income'";
    return executeQuery(queryText);
}

//private
double Database::executeQuery(QString queryText){
    bool success = false;
    if (!this->db.open())
    {
        qDebug() << "Database::periodTot. Error: connection with database failed";
        return 0;
    }
    else{
        QSqlQuery query;
        query.prepare(queryText);

        if(query.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "Database::executeQuery error:"
                     << query.lastError();
            return 0;
        }
        while (query.next()) {
            return query.value(0).toDouble();
        }
    }
}

//End of functions working together


void Database::updateRecord(Record const &record){
    QString date = record.date;
    startDateCheck(QDate::fromString(record.date,"yyyy-MM-dd"),record.id);
    QString dateNow=QDateTime::currentDateTime().toString(Qt::DateFormat(1));//2024-08-25T10:30:51

    QString queryText = "UPDATE expenses SET "
                        "data = \"" + date + "\", "
                        "category = \"" + record.cat + "\", " +
                        "amount = " + QString::number(record.amount) + ", " +
                        "currency = \"" + record.currency + "\", " +
                        "exchRate = " + QString::number(record.rate) + ", " +
                        "finalAmount = " + QString::number(record.finalAmnt) + ", " +
                        "reg = " + QString::number(record.reg) + ", " +
                        "lastChangeDateTime = \"" + dateNow + "\" " +
                        "WHERE rowid = " + QString::number(record.id);

    executeQuery(queryText);
}

int64_t Database::getLatestRowID(){
    QString queryText = "SELECT rowid FROM expenses ORDER BY rowid DESC LIMIT 1";
    return int64_t(executeQuery(queryText));
}

//private
void Database::startDateCheck(QDate newStartDate, int64_t row){
    //check if expense date is before global startDate, then update global startDate
    if (newStartDate < this->sDate){
        startDate(newStartDate, row);
        emit updateStartDate(this->sDate, this->startRow);
    }
    //if row is the same as start date and the date is different as sDate, new sDate needed
    else if (row != -1 && row == this->startRow && newStartDate != this->sDate){
        this->sDate = newStartDate;
        startDateUpdate();
    }
}

//private
void Database::startDateUpdate(){

    QSqlQuery query;
    QDate date;
    bool success = false;
    int64_t row = 0;
    query.prepare("SELECT data, rowid FROM expenses "
                  "WHERE rowid != " + QString::number(this->startRow) +
                  " "
                  "ORDER BY data ASC "
                  "LIMIT 1");

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Database::startDateUpdate error:"
                 << query.lastError();
    }
    while (query.next()) {
        date = QDate::fromString(query.value(0).toString(),"yyyy-MM-dd");
        // QDate d = QDate::fromString(date,"yyyy-MM-dd")
        row = query.value(1).toInt();
    }
    if (date < this->sDate){
        startDate(date, row);
    }
    emit updateStartDate(this->sDate, this->startRow);
}
