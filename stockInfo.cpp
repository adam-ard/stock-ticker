#include <QString>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>
#include "stockInfo.h"

const string API_KEY = std::getenv("POLYGON_API_KEY");

QString StockInfo::httpGetPolygon(const string path)
{
  string polygonPath = "https://api.polygon.io/" +
	path + "?apiKey=" + API_KEY;
  return httpGet(polygonPath);
}

QString StockInfo::downloadFilePolygon(const string url)
{
  string cmd = "curl " + url + "?apiKey=" + API_KEY + " --output " +
	m_symbol.toUtf8().constData() + ".png";
  return shellCmd(cmd);
}

QString StockInfo::httpGet(const string path)
{
  return shellCmd("curl " + path);
}

QString StockInfo::shellCmd(const string cmd)
{
  auto pPipe = ::popen(cmd.c_str(), "r");
  array<char, 256> buffer;
  string result;
  while(not feof(pPipe))
  {
	  auto bytes = fread(buffer.data(), 1, buffer.size(), pPipe);
	  result.append(buffer.data(), bytes);
  }

  ::pclose(pPipe);
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

  // Details
  QString symbolDetails = httpGetPolygon(("v1/meta/symbols/" +
										  m_symbol +
										  "/company").toUtf8().constData());

  QJsonDocument d = QJsonDocument::fromJson(symbolDetails.toUtf8().constData());
  QJsonObject sett2 = d.object();

  m_name = sett2["name"].toString();
  m_desc = sett2["description"].toString();
  QString logoUrl = sett2["logo"].toString();

  downloadFilePolygon(logoUrl.toUtf8().constData());
  
  // Previous day
  QString openClosePrev = httpGetPolygon(("v2/aggs/ticker/" +
										  m_symbol +
										  "/prev").toUtf8().constData());

  QJsonDocument d3 = QJsonDocument::fromJson(openClosePrev.toUtf8().constData());
  QJsonObject sett4 = d3.object();
  QJsonValue value = sett4.value(QString("results"));

  QJsonObject item = value[0].toObject();

  // I can't seem to get the price from the api, I think only paid accounts can get that data
  // I just stuck in 5.0 as a place holder
  m_price = QString::number(5.0f);
  m_diff = QString::number(5.0f - item["c"].toDouble());

  m_open = QString::number(item["o"].toDouble());
  m_high = QString::number(item["h"].toDouble());
  m_low = QString::number(item["l"].toDouble());
  m_close = QString::number(item["c"].toDouble());
  m_volume = QString::number(item["v"].toDouble());
}

QString StockInfo::logoFilename()
{
  return m_logoFilename;
}

QString StockInfo::stockDesc()
{
  return "Title: " + m_symbol + "\nSubtitle: " + m_name + "\nDesc: " +
	m_desc + "\nOpen: " + m_open + "\nHigh: " + m_high + "\nLow: "+
	m_low + "\nClose: " + m_close + "\nVolume: " + m_volume;
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
