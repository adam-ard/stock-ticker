#ifndef TICKER_WINDOW_H
#define TICKER_WINDOW_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QTableWidget;
class QGridLayout;
class QPushButton;

using namespace std;

struct StockInfo {
  QString logoFilename;
  QString symbol;
  QString name;
  QString price;
  QString diff;
  QString desc;
  QString open;
  QString high;
  QString low;
  QString close;
  QString volume;
};


class TickerWindow : public QWidget
{
private:
  QLabel* m_logoLabel;
  QLabel* m_detailsLabel;
  QLineEdit* m_symLineEdit;
  QTableWidget* m_stockTableWidget;
  QGridLayout* m_gridLayout;
  QPushButton* m_addButton;
  QPushButton* m_deleteButton;
  map<QString, StockInfo> m_stockDetails;
  
public:
  TickerWindow(int width, int height);
  ~TickerWindow();
  void doLayout();
  void setDetails(QString symbol);
  void updateDetails();
  void deleteStock();
  void initStockListRow(int row, QString sym, QString name, QString price, QString diff);
  void addStock();
  void addStockFromSymbol(QString sym);
  StockInfo getStockInfo(QString sym);
};

#endif //TICKER_WINDOW_H
