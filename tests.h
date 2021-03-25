#ifndef TESTS_H
#define TESTS_H

#include <QtTest/QtTest>

class TestStockInfo: public QObject
{
  Q_OBJECT
private slots:
  void testParse();
  void testParseDetailsEmpty();
  void testParsePrevDayEmpty();
  void testLogoFilename();
  
};

#endif //TESTS_H
