#include <QString>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>
#include "stockInfo.h"


QString StockInfo::httpGetPolygon(const string path, int& out_exitStatus)
{
  string polygonPath = "https://api.polygon.io/" + path + "?apiKey=" + API_KEY;
  return httpGet(polygonPath, out_exitStatus);
}

QString StockInfo::httpGet(const string path, int& out_exitStatus)
{
  return shellCmd("curl " + path, out_exitStatus);
}

QString StockInfo::downloadLogo(const string url, int& out_exitStatus)
{
  string cmd = "curl " + url + "?apiKey=" + API_KEY + " --output " + m_symbol.toUtf8().constData() + ".png";
  return shellCmd(cmd, out_exitStatus);
}

/*
  This snippet comes from https://dev.to/aggsol/calling-shell-commands-from-c-8ej
*/
QString StockInfo::shellCmd(const string cmd, int& out_exitStatus)
{
  out_exitStatus = 0;
  auto pPipe = ::popen(cmd.c_str(), "r");
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
  QString symbolDetails = httpGetPolygon(("v1/meta/symbols/" + m_symbol + "/company").toUtf8().constData(), status);

  // TODO: handle errors
  QJsonDocument d = QJsonDocument::fromJson(symbolDetails.toUtf8().constData());
  QJsonObject sett2 = d.object();

  m_name = sett2["name"].toString();
  m_desc = sett2["description"].toString();

  QString logoUrl = sett2["logo"].toString();

  downloadLogo(logoUrl.toUtf8().constData(), status);

  // TODO: get yesterday's date, and the day before
  // TODO: problem with too many requests
  QString openClose = httpGetPolygon(("v1/open-close/" + m_symbol + "/2021-03-22").toUtf8().constData(), status);
  
  QJsonDocument d1 = QJsonDocument::fromJson(openClose.toUtf8().constData());
  QJsonObject sett3 = d1.object();
  
  m_open = QString::number(sett3["open"].toDouble());
  m_price = QString::number(sett3["close"].toDouble());
  m_high = QString::number(sett3["high"].toDouble());
  m_low = QString::number(sett3["low"].toDouble());
  m_close = QString::number(sett3["close"].toDouble());
  m_volume = QString::number(sett3["volume"].toDouble());

  QString openClosePrev = httpGetPolygon(("v2/aggs/ticker/" + m_symbol + "/prev").toUtf8().constData(), status);

  QJsonDocument d3 = QJsonDocument::fromJson(openClosePrev.toUtf8().constData());
  QJsonObject sett4 = d3.object();
  QJsonValue value = sett4.value(QString("results"));

  QJsonObject item = value[0].toObject();

  // I am taking the closing values, since the last trade and snapshot seem to be not authorized
  m_diff = QString::number(item["c"].toDouble() - sett3["close"].toDouble());
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
