#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <iostream>

#include "tickerWindow.h"
#include "stockInfo.h"

const int ICON_COLUMN = 0;
const int SYMBOL_COLUMN = 1;
const int NAME_COLUMN = 2;
const int PRICE_COLUMN = 3;
const int DIFF_COLUMN = 4;

StockInfo TickerWindow::getStockInfo(QString sym)
{
  if(m_stockDetails.find(sym) != m_stockDetails.end())
	return m_stockDetails[sym];

  StockInfo info(sym);
  info.load();

  m_stockDetails[sym] = info;
  return info;
}

TickerWindow::TickerWindow(int width, int height)
{
  m_symLineEdit= new QLineEdit;
  m_detailsLabel = new QLabel;
  m_stockTableWidget = new QTableWidget;
  m_logoLabel = new QLabel;
  m_gridLayout = new QGridLayout;
  m_addButton = new QPushButton("Add");
  m_deleteButton = new QPushButton("Delete");

  doLayout();

  resize(width, height);
  show();
}

TickerWindow::~TickerWindow()
{
  if(m_logoLabel)
	delete m_logoLabel;

  if(m_detailsLabel)
	delete m_detailsLabel;

  if(m_symLineEdit)
	delete m_symLineEdit;

  if(m_stockTableWidget)
	delete m_stockTableWidget;

  if(m_addButton)
	delete m_addButton;

  if(m_deleteButton)
	delete m_deleteButton;
}

void TickerWindow::doLayout()
{
  // setup the table widget
  m_stockTableWidget->setRowCount(0);
  m_stockTableWidget->setColumnCount(5);
  m_stockTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_stockTableWidget->horizontalHeader()->hide();
  m_stockTableWidget->horizontalHeader()->setStretchLastSection(true);
  m_stockTableWidget->verticalHeader()->hide();
  m_stockTableWidget->setShowGrid(false);
  m_stockTableWidget->sortItems(1);

  // I can only seed two values before the rate limiting kicks in for the api
  //    that is why Tesla is commented out.
  addStockFromSymbol("AAPL");
  addStockFromSymbol("GOOG");
  addStockFromSymbol("TSLA");


  // add everything to the gird layout
  m_gridLayout->addWidget(m_addButton, 0, 0);
  m_gridLayout->addWidget(m_symLineEdit, 0, 1, 1, 1);
  m_gridLayout->addWidget(m_deleteButton, 1, 0);
  m_gridLayout->addWidget(m_stockTableWidget, 2, 0, 2, 3);
  m_gridLayout->addWidget(m_logoLabel, 4, 0, 1, 2);
  m_gridLayout->addWidget(m_detailsLabel, 4, 2);

  m_detailsLabel->setWordWrap(true);

  // connect the signals and slots
  QObject::connect(m_addButton, &QPushButton::clicked, this, &TickerWindow::addStock);
  QObject::connect(m_deleteButton, &QPushButton::clicked, this, &TickerWindow::deleteStock);
  QObject::connect(m_stockTableWidget, &QTableWidget::itemSelectionChanged, this, &TickerWindow::updateDetails);

  // set the widget layout
  setLayout(m_gridLayout);

  // set the selection to the first row
  m_stockTableWidget->setCurrentCell(0,0);
}

void TickerWindow::setDetails(QString symbol)
{
  if(symbol == "")
  {
	m_logoLabel->clear();
	m_detailsLabel->setText("Nothing is selected");
	return;
  }

  StockInfo info = m_stockDetails[symbol];
  QPixmap pic(info.logoFilename());
  m_logoLabel->setPixmap(pic);
  m_detailsLabel->setText(info.stockDesc());
}

void TickerWindow::updateDetails()
{
  int curr = m_stockTableWidget->currentRow();

  // if nothing is selected, then make a blank selection
  if(curr == -1)
  {
	setDetails("");
	return;
  }

  QTableWidgetItem* currItem = m_stockTableWidget->item(curr, SYMBOL_COLUMN);
  setDetails(currItem->text());
}

void TickerWindow::deleteStock()
{
  m_stockTableWidget->removeRow(m_stockTableWidget->currentRow());
  m_stockTableWidget->setCurrentCell(0,0);
}

void TickerWindow::initStockListRow(int row, QString sym, QString name, QString price, QString diff)
{
  QTableWidgetItem* icon = new QTableWidgetItem();
  icon->setIcon(QIcon(sym + ".png"));

  m_stockTableWidget->setItem(row, ICON_COLUMN, icon);
  m_stockTableWidget->setItem(row, SYMBOL_COLUMN, new QTableWidgetItem(sym));
  m_stockTableWidget->setItem(row, NAME_COLUMN, new QTableWidgetItem(name));
  m_stockTableWidget->setItem(row, PRICE_COLUMN, new QTableWidgetItem(price));
  m_stockTableWidget->setItem(row, DIFF_COLUMN, new QTableWidgetItem(diff));
}

void TickerWindow::addStockFromSymbol(QString sym)
{
  int numRows = m_stockTableWidget->rowCount();
  m_stockTableWidget->setRowCount(numRows + 1);

  StockInfo info = getStockInfo(sym);
  initStockListRow(numRows, info.symbol(), info.name(), info.price(), info.diff());
}

void TickerWindow::addStock()
{
  addStockFromSymbol(m_symLineEdit->text());
  m_stockTableWidget->sortItems(1);
}
