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
QWidget* window;
QGridLayout* layout;
QPushButton* addButton;
QPushButton* deleteButton;

// TODO: check that TableWidgetItems get deleted
// TODO: put this all in a class, so clean can be in a destructor
// TODO: make sure to not delete things twice (currently I am seg faulting)

void setDetails(QString symbol)
{
  if(symbol == "")
  {
	logoLabel->clear();
	detailsLabel->setText("Nothing is selected");
	return;
  }

  // TODO: call the API to get this information
  QPixmap pic(symbol + ".png");
  logoLabel->setPixmap(pic);
  detailsLabel->setText("Here is some fake data\nWe'll add some more stuff later\nStay tuned\nIt'll be fun");
}

void updateDetails()
{
  int curr = stockList->currentRow();

  if(curr == -1)
  {
	  setDetails("");
	  return;
  }
  
  QTableWidgetItem* currItem = stockList->item(curr, 1);
  setDetails(currItem->text());
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

void cleanup()
{
  if(logoLabel)
	delete logoLabel;

  if(detailsLabel)
	delete detailsLabel;

  if(symLineEdit)
	delete symLineEdit;

  if(stockList)
	delete stockList;

  if(window)
	delete window;
  
  if(layout)
	delete layout;

  if(addButton)
	delete layout;

  if(deleteButton)
	delete deleteButton;
}

void init()
{
  window = new QWidget;
  symLineEdit= new QLineEdit;
  detailsLabel = new QLabel;
  stockList = new QTableWidget;
  logoLabel = new QLabel;
  layout = new QGridLayout;
  addButton = new QPushButton("Add");
  deleteButton = new QPushButton("Delete");
}

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   init();

   stockList->setRowCount(3);
   stockList->setColumnCount(5);
   stockList->setSelectionBehavior(QAbstractItemView::SelectRows);
   stockList->horizontalHeader()->hide();
   stockList->horizontalHeader()->setStretchLastSection(true);
   stockList->verticalHeader()->hide();
   stockList->setShowGrid(false);

   initStockListRow(0, "AAPL", "Apple", "100", "-50");
   initStockListRow(1, "GOOG", "Google", "200", "-40");
   initStockListRow(2, "TSLA", "Tesla", "250", "-70");
   
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
   int res = app.exec();

   cleanup();

   return res;
}
