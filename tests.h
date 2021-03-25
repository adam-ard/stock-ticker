#ifndef TESTS_H
#define TESTS_H

#include <QtTest/QtTest>

class TestStockInfo: public QObject
{
  Q_OBJECT
private slots:
  void toUpper();
  void anotherTest();
};

#endif //TESTS_H
