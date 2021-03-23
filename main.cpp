#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>

#include <iostream>

QLabel* logoLabel;
QLabel* detailsLabel;
QLineEdit* symLineEdit;
QTableWidget* stockList;


// TODO: make sure memory is cleaned up

void setDetails(QString symbol, QString details)
{
   QPixmap pic(symbol + ".png");
   logoLabel->setPixmap(pic);
   detailsLabel->setText(details);
}

void updateDetails()
{
  int curr = stockList->currentRow();

  if(curr == -1)
  {
	  setDetails("", "No stocks to load");
	  return;
  }
  
  QTableWidgetItem* currItem = stockList->item(curr, 1);
  setDetails(currItem->text(), "asdfasdfasdf\nasdfasdfasdf\nasdfafsdasdf\nasdfasdfaef");
}

void deleteStock()
{
  stockList->removeRow(stockList->currentRow());
  stockList->setCurrentCell(0,0);
}

void initStockListRow(int row, QString sym, QString name, QString price, QString diff)
{
  QTableWidgetItem* icon = new QTableWidgetItem();
  icon->setIcon(QIcon(sym + ".png"));

  stockList->setItem(row, 0, icon);
  stockList->setItem(row, 1, new QTableWidgetItem(sym));
  stockList->setItem(row, 2, new QTableWidgetItem(name));
  stockList->setItem(row, 3, new QTableWidgetItem(price));
  stockList->setItem(row, 4, new QTableWidgetItem(diff));
}

void addStock()
{
  int numRows = stockList->rowCount();
  stockList->setRowCount(numRows + 1);
  initStockListRow(numRows, symLineEdit->text(), "Searching...", "Searching...", "Searching...");
}

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   QWidget *window = new QWidget;
   
   QPushButton *addButton = new QPushButton("Add");
   QPushButton *deleteButton = new QPushButton("Delete");

   symLineEdit= new QLineEdit;

   QString msg = "These are the stock details. \nThere are lots of lines in here\nThese are the stock details. \nThere are lots of lines in here\nThese are the stock details. \nThere are lots of lines in here\nThese are the stock details. \nThere are lots of lines in here\nThese are the stock details. \nThere are lots of lines in here\n ";

   detailsLabel = new QLabel;

   stockList = new QTableWidget();
   stockList->setRowCount(3);
   stockList->setColumnCount(5);
   stockList->setSelectionBehavior(QAbstractItemView::SelectRows);
   stockList->horizontalHeader()->hide();
   stockList->horizontalHeader()->setStretchLastSection(true);
   stockList->verticalHeader()->hide();
   stockList->setShowGrid(false);

   logoLabel = new QLabel;

   initStockListRow(0, "AAPL", "Apple", "100", "-50");
   initStockListRow(1, "GOOG", "Google", "200", "-40");
   initStockListRow(2, "TSLA", "Tesla", "250", "-70");
   
   QGridLayout *layout = new QGridLayout;
   layout->addWidget(addButton, 0, 0);
   layout->addWidget(symLineEdit, 0, 1);
   layout->addWidget(deleteButton, 1, 0);
   layout->addWidget(stockList, 2, 0, 2, 2);
   layout->addWidget(logoLabel, 4, 0);
   layout->addWidget(detailsLabel, 4, 1);

   QObject::connect(addButton, &QPushButton::clicked, addStock);
   QObject::connect(deleteButton, &QPushButton::clicked, deleteStock);
   QObject::connect(stockList, &QTableWidget::itemSelectionChanged, updateDetails);

   stockList->setCurrentCell(0,0);
   
   window->resize(750, 500);
   window->setLayout(layout);
   window->show();
   return app.exec();
}
