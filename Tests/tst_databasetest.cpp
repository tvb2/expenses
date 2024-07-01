#include <QCoreApplication>
#include <QtTest>
#include <QObject>

// add necessary includes here
#include "../database.h"

class databaseTest : public QObject
{
    Q_OBJECT

public:
    databaseTest();
    ~databaseTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void test_db_print();
};

databaseTest::databaseTest() {}

databaseTest::~databaseTest() {}

void databaseTest::initTestCase() {}

void databaseTest::cleanupTestCase() {}

void databaseTest::test_case1() {
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

void databaseTest::test_db_print(){
    // Profile *p = new Profile;
    Database *db = new Database;
    db->setDB("C:\\Users\\bogda\\qt\\expenses\\Tests\\cases\\profile (3).sqlite");
    db->printExpenses();
    QVERIFY(true == 1);
}

QTEST_MAIN(databaseTest)

#include "tst_databasetest.moc"
