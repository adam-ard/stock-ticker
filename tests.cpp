#include "tests.h"
#include "stockInfo.h"

#include <iostream>

using namespace std;

const string AAPL_PREV_DAY = R"({
 "ticker": "AAPL",
 "queryCount": 1,
 "resultsCount": 1,
 "adjusted": false,
 "results": [
  {
   "T": "AAPL",
   "v": 88525685,
   "vw": 121.2133,
   "o": 122.82,
   "c": 120.09,
   "h": 122.9,
   "l": 120.065,
   "t": 1616616000000,
   "n": 653239
  }
 ],
 "status": "OK",
 "request_id": "af0f0260fe9956b7e438bd616617bb77",
 "count": 1
})";

const string AAPL_DETAILS = R"({
 "logo": "https://s3.polygon.io/logos/aapl/logo.png",
 "listdate": "1990-01-02",
 "cik": "320193",
 "bloomberg": "EQ0010169500001000",
 "figi": null,
 "lei": "HWUPKR0MPOU8FGXBT394",
 "sic": 3571,
 "country": "usa",
 "industry": "Computer Hardware",
 "sector": "Technology",
 "marketcap": 908316631180,
 "employees": 123000,
 "phone": "+1 408 996-1010",
 "ceo": "Timothy D. Cook",
 "url": "http://www.apple.com",
 "description": "Apple Inc is designs, manufactures and markets mobile communication and media devices and personal computers, and sells a variety of related software, services, accessories, networking solutions and third-party digital content and applications.",
 "exchange": "Nasdaq Global Select",
 "name": "Apple Inc.",
 "symbol": "AAPL",
 "exchangeSymbol": "NGS",
 "hq_address": "1 Infinite Loop Cupertino CA, 95014",
 "hq_state": "CA",
 "hq_country": "USA",
 "type": "CS",
 "updated": "11/16/2018",
 "tags": [
  "Technology",
  "Consumer Electronics",
  "Computer Hardware"
 ],
 "similar": [
  "MSFT",
  "NOK",
  "IBM",
  "HPQ",
  "GOOGL",
  "BB",
  "XLK"
 ],
 "active": true
})";



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

void TestStockInfo::testParse()
{
  StockInfo info("AAPL");
  info.parseDetails(AAPL_DETAILS);
  info.parsePrevDay(AAPL_PREV_DAY);

  QVERIFY(info.symbol() == "AAPL");
  QVERIFY(info.name() == "Apple Inc.");

  QVERIFY(info.price() == "117.688");
  QVERIFY(info.diff() == "-2.4018");
  QVERIFY(info.stockDesc() == R"(Title: AAPL
Subtitle: Apple Inc.
Desc: Apple Inc is designs, manufactures and markets mobile communication and media devices and personal computers, and sells a variety of related software, services, accessories, networking solutions and third-party digital content and applications.
Open: 122.82
High: 122.9
Low: 120.065
Close: 120.09
Volume: 8.85257e+07)");
  
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
