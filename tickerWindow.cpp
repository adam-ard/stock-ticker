#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <iostream>

#include "tickerWindow.h"

#include <curlpp/cURLpp.hpp>

// TODO: should I use const or const_expr

const int ICON_COLUMN = 0;
const int SYMBOL_COLUMN = 1;
const int NAME_COLUMN = 2;
const int PRICE_COLUMN = 3;
const int DIFF_COLUMN = 4;

void TickerWindow::getStockInfo(QString sym)
{
  std::cout << "Retreiving data for " << sym.toUtf8().constData() << std::endl;
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
  m_stockTableWidget->setRowCount(3);
  m_stockTableWidget->setColumnCount(5);
  m_stockTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_stockTableWidget->horizontalHeader()->hide();
  m_stockTableWidget->horizontalHeader()->setStretchLastSection(true);
  m_stockTableWidget->verticalHeader()->hide();
  m_stockTableWidget->setShowGrid(false);

  // put in the fake data
  initStockListRow(0, "AAPL", "Apple", "100", "-50");
  initStockListRow(1, "GOOG", "Google", "200", "-40");
  initStockListRow(2, "TSLA", "Tesla", "250", "-70");

  // add everything to the gird layout
  m_gridLayout->addWidget(m_addButton, 0, 0);
  m_gridLayout->addWidget(m_symLineEdit, 0, 1);
  m_gridLayout->addWidget(m_deleteButton, 1, 0);
  m_gridLayout->addWidget(m_stockTableWidget, 2, 0, 2, 2);
  m_gridLayout->addWidget(m_logoLabel, 4, 0);
  m_gridLayout->addWidget(m_detailsLabel, 4, 1);

  // connect the signals and slots
  QObject::connect(m_addButton, &QPushButton::clicked, this, &TickerWindow::addStock);
  QObject::connect(m_deleteButton, &QPushButton::clicked, this, &TickerWindow::deleteStock);
  QObject::connect(m_stockTableWidget, &QTableWidget::itemSelectionChanged, this, &TickerWindow::updateDetails);

  // set the selection to the first row
  m_stockTableWidget->setCurrentCell(0,0);

  // set the widget layout
  setLayout(m_gridLayout);
}

void TickerWindow::setDetails(QString symbol)
{
  if(symbol == "")
	{
	  m_logoLabel->clear();
	  m_detailsLabel->setText("Nothing is selected");
	  return;
	}

  // TODO: call the API to get this information
  QPixmap pic(symbol + ".png");
  m_logoLabel->setPixmap(pic);
  m_detailsLabel->setText("Here is some fake data\nWe'll add some more stuff later\nStay tuned\nIt'll be fun");
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

  getStockInfo(sym);
  initStockListRow(numRows, sym, "Searching...", "Searching...", "Searching...");
}

void TickerWindow::addStock()
{
  addStockFromSymbol(m_symLineEdit->text());
}


