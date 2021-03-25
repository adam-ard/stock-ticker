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
  const char* key = std::getenv("POLYGON_API_KEY");
  if(key) {
	m_apiKey = key;
  }
  m_logoFilename = m_symbol + ".png";
}

StockInfo::StockInfo()
{
}

void StockInfo::parseDetails(string json)
{
  QJsonDocument document = QJsonDocument::fromJson(json.c_str());
  QJsonObject root = document.object();

  m_name = root["name"].toString();
  m_desc = root["description"].toString();
  m_logoUrl = root["logo"].toString();
}

void StockInfo::parsePrevDay(string json)
{
  QJsonDocument document = QJsonDocument::fromJson(json.c_str());
  QJsonObject root = document.object();
  QJsonValue value = root.value(QString("results"));

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

void StockInfo::load()
{
  // Details API call
  string symbolDetails = httpGetPolygon(("v1/meta/symbols/" +
										  m_symbol +
										  "/company").toUtf8().constData());

  parseDetails(symbolDetails);
  downloadFilePolygon(m_logoUrl.toUtf8().constData());

  // Previous day API call
  string openClosePrev = httpGetPolygon(("v2/aggs/ticker/" +
										  m_symbol +
										  "/prev").toUtf8().constData());
  parsePrevDay(openClosePrev);
  
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
