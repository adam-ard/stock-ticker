#include "tests.h"
#include "stockInfo.h"

void TestStockInfo::toUpper()
{
  QString str = "Hello";
  QVERIFY(str.toUpper() == "HELLO");
}

void TestStockInfo::anotherTest()
{
  //  StockInfo info;
  //  QVERIFY(true);
}

QTEST_MAIN(TestStockInfo)
