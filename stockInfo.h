#ifndef STOCK_INFO_H
#define STOCK_INFO_H

class QString;

using namespace std;

class StockInfo
{
private:
  QString m_logoFilename;
  QString m_symbol;
  QString m_name;
  QString m_price;
  QString m_diff;
  QString m_desc;
  QString m_open;
  QString m_high;
  QString m_low;
  QString m_close;
  QString m_volume;
  QString m_logoUrl;

  string m_apiKey;

  // helpers
  string httpGetPolygon(const string path);
  string downloadFilePolygon(const string url);
  string httpGet(const string path);
  string shellCmd(const string cmd);

public:
  StockInfo();
  StockInfo(QString sym);
  void load();
  QString stockDesc();
  QString logoFilename();

  QString symbol();
  QString name();
  QString price();
  QString diff();

  // I made these public so I could test them
  //   but I am sure there is a better way to
  //   do this.
  void parseDetails(string json);
  void parsePrevDay(string json);
};

#endif //STOCK_INFO_H
