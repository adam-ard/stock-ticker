#include "tests.h"
#include "stockInfo.h"

#include <iostream>

using namespace std;

void TestStockInfo::testLogoFilename()
{
  StockInfo info("TEST");
  QVERIFY(info.symbol() == "TEST");
  QVERIFY(info.logoFilename() == "TEST.png");
}

void TestStockInfo::testParseDetailsEmpty()
{
  StockInfo info("TEST");
  info.parseDetails("{}");

  QVERIFY(info.stockDesc() ==
		  "Title: TEST\nSubtitle: \nDesc: \nOpen: \nHigh: \nLow: \nClose: \nVolume: ");
}

void TestStockInfo::testParsePrevDayEmpty()
{
  StockInfo info("TEST");
  info.parseDetails("{}");

  QVERIFY(info.symbol() == "TEST");
  QVERIFY(info.name() == "");
  QVERIFY(info.price() == "");
  QVERIFY(info.diff() == "");
}

QTEST_MAIN(TestStockInfo)
