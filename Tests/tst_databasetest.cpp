#include <QCoreApplication>
#include <QtTest>

// add necessary includes here

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
};

databaseTest::databaseTest() {}

databaseTest::~databaseTest() {}

void databaseTest::initTestCase() {}

void databaseTest::cleanupTestCase() {}

void databaseTest::test_case1() {
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

QTEST_MAIN(databaseTest)

#include "tst_databasetest.moc"
