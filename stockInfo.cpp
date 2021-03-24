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
  
  QJsonDocument d = QJsonDocument::fromJson(symbolDetails.toUtf8().constData());
  QJsonObject sett2 = d.object();

  m_name = sett2["name"].toString();
  m_price = "Price";
  m_diff = "Diff";
  m_desc = sett2["description"].toString();
  m_open = "Open";
  m_high = "High";
  m_low = "Low";
  m_close = "Close";
  m_volume = "Volume";
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
