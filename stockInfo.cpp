#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>
#include "stockInfo.h"

const string API_URL = "https://api.polygon.io/";

string StockInfo::httpGetPolygon(const string path)
{
  string polygonPath = API_URL + path + "?apiKey=" + m_apiKey;
  return httpGet(polygonPath);
}

string StockInfo::downloadFilePolygon(const string url)
{
  string cmd = "curl " + url + "?apiKey=" + m_apiKey + " --output " +
	m_symbol.toUtf8().constData() + ".png";
  return shellCmd(cmd);
}

string StockInfo::httpGet(const string path)
{
  return shellCmd("curl " + path);
}

string StockInfo::shellCmd(const string cmd)
{
  FILE* pPipe = ::popen(cmd.c_str(), "r");

  int bufferSize = 1000;
  char buffer[bufferSize];
  string result;
  while(not feof(pPipe))
  {
	  size_t bytes = fread(buffer, 1, bufferSize, pPipe);
	  result.append(buffer, bytes);
  }

  ::pclose(pPipe);
  return result;
}

StockInfo::StockInfo(QString sym) : m_symbol(sym)
{
  m_apiKey = std::getenv("POLYGON_API_KEY");
  m_logoFilename = m_symbol + ".png";
}

StockInfo::StockInfo()
{
}

void StockInfo::load()
{
  // Details
  string symbolDetails = httpGetPolygon(("v1/meta/symbols/" +
										  m_symbol +
										  "/company").toUtf8().constData());

  QJsonDocument document = QJsonDocument::fromJson(symbolDetails.c_str());
  QJsonObject root = document.object();

  m_name = root["name"].toString();
  m_desc = root["description"].toString();
  QString logoUrl = root["logo"].toString();

  downloadFilePolygon(logoUrl.toUtf8().constData());

  // Previous day
  string openClosePrev = httpGetPolygon(("v2/aggs/ticker/" +
										  m_symbol +
										  "/prev").toUtf8().constData());

  QJsonDocument document2 = QJsonDocument::fromJson(openClosePrev.c_str());
  QJsonObject root2 = document2.object();
  QJsonValue value = root2.value(QString("results"));

  QJsonObject item = value[0].toObject();

  // I can't seem to get the price from the api, I think only paid accounts can get that data
  // I just stuck in a placeholder.
  double yesterdayPrice = item["c"].toDouble();
  double todayPrice = yesterdayPrice * 0.98f;

  m_price = QString::number(todayPrice);
  m_diff = QString::number(todayPrice - yesterdayPrice);

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
