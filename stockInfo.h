#ifndef STOCK_INFO_H
#define STOCK_INFO_H

class QString;
class QNetworkAccessManager;

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
  QNetworkAccessManager* m_networkManager;

public:
  StockInfo();
  StockInfo(QString sym, QNetworkAccessManager* networkManager);
  void load();
  QString stockDesc();
  QString logoFilename();

  QString symbol();
  QString name();
  QString price();
  QString diff();

  QString httpGetPolygon(const string path, int& out_exitStatus);
  QString httpGet(const string path, int& out_exitStatus);
  QString downloadLogo(const string url, int& out_exitStatus);
  QString shellCmd(const string cmd, int& out_exitStatus);
};

#endif //STOCK_INFO_H
