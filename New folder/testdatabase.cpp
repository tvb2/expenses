#include "testdatabase.h"

void Testdatabase::printData()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

QTEST_MAIN(Testdatabase)
