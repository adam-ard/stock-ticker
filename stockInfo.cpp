#include <QString>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>

#include "stockInfo.h"


/*
  This snippet comes from https://dev.to/aggsol/calling-shell-commands-from-c-8ej
*/
QString StockInfo::httpGet(const string path, int& out_exitStatus)
{
  string getCmd = "curl https://api.polygon.io/" + path + "?apiKey=" + API_KEY;
  
  out_exitStatus = 0;
  auto pPipe = ::popen(getCmd.c_str(), "r");
  if(pPipe == nullptr)
    {
	  throw runtime_error("Cannot open pipe");
    }

  array<char, 256> buffer;

  string result;

  while(not feof(pPipe))
    {
	  auto bytes = fread(buffer.data(), 1, buffer.size(), pPipe);
	  result.append(buffer.data(), bytes);
    }

  auto rc = ::pclose(pPipe);

  if(WIFEXITED(rc))
    {
	  out_exitStatus = WEXITSTATUS(rc);
    }

  return QString::fromStdString(result);
}

StockInfo::StockInfo(QString sym, QNetworkAccessManager* networkManager) : m_symbol(sym)
{
  m_networkManager = networkManager;
}

StockInfo::StockInfo()
{
}



void StockInfo::load()
{
  m_logoFilename = m_symbol + ".png";

  int status = 0;
  QString symbolDetails = httpGet(("v1/meta/symbols/" + m_symbol + "/company").toUtf8().constData(), status);

  // TODO: download the logos
  QJsonDocument d = QJsonDocument::fromJson(symbolDetails.toUtf8().constData());
  QJsonObject sett2 = d.object();

  m_name = sett2["name"].toString();
  m_desc = sett2["description"].toString();

  // TODO: get yesterday's date, and the day before
  QString openClose = httpGet(("v1/open-close/" + m_symbol + "/2021-03-22").toUtf8().constData(), status);
  
  QJsonDocument d1 = QJsonDocument::fromJson(openClose.toUtf8().constData());
  QJsonObject sett3 = d1.object();
  
  m_open = QString::number(sett3["open"].toDouble());
  m_price = QString::number(sett3["close"].toDouble());
  m_high = QString::number(sett3["high"].toDouble());
  m_low = QString::number(sett3["low"].toDouble());
  m_close = QString::number(sett3["close"].toDouble());
  m_volume = QString::number(sett3["volume"].toDouble());

  QString openClosePrev = httpGet(("v2/aggs/ticker/" + m_symbol + "/prev").toUtf8().constData(), status);
  cout << openClosePrev.toUtf8().constData() << endl;

  QJsonDocument d3 = QJsonDocument::fromJson(openClosePrev.toUtf8().constData());
  QJsonObject sett4 = d3.object();

  // I am taking the closing values, since the last trade and snapshot seem to be not authorized
  QJsonObject results = sett4["results"].toObject();
  m_diff = QString::number(results["c"].toDouble() - sett3["close"].toDouble());
}

QString StockInfo::logoFilename()
{
  return m_logoFilename;
}

QString StockInfo::stockDesc()
{
  return "Title: " + m_symbol + "\nSubtitle: " + m_name + "\nDesc: " + m_desc + "\nOpen: " + m_open + "\nHigh: " + m_high + "\nLow: "+ m_low + "\nClose: " + m_close + "\nVolume: " + m_volume;
}

QString StockInfo::symbol()
{
  return m_symbol;
}

QString StockInfo::name()
{
  return m_name;
}

QString StockInfo::price()
{
  return m_price;
}

QString StockInfo::diff()
{
  return m_diff;
}
