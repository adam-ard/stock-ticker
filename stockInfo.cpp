#include <QString>
#include "stockInfo.h"

StockInfo::StockInfo(QString sym) : m_symbol(sym)
{
}

StockInfo::StockInfo()
{
}

void StockInfo::load()
{
  m_logoFilename = m_symbol + ".png";

  // TODO: load this from the internet
  m_name = "Name";
  m_price = "Price";
  m_diff = "Diff";
  m_desc = "Desc";
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
