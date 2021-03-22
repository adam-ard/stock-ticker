#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QPushButton>
#include <QStringList>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>

#include <cstdio>

QLabel* logoLabel;
QLabel* detailsLabel;
QLineEdit* symLineEdit;
QTableWidget* stockList;


void setDetails(QString symbol, QString details)
{
   QPixmap pic(symbol + ".png");
   logoLabel->setPixmap(pic);
   detailsLabel->setText(details);
}

void updateDetails()
{
  int curr = stockList->currentRow();
  QTableWidgetItem* currItem = stockList->item(curr, 1);

  setDetails(currItem->text(), "asdfasdfasdf\nasdfasdfasdf\nasdfafsdasdf\nasdfasdfaef");
}

void addStock()
{
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
   setDetails("TSLA", msg);
   
   QTableWidgetItem* applIcon = new QTableWidgetItem();
   applIcon->setIcon(QIcon("AAPL.png"));
   stockList->setItem(0,0, applIcon);

   stockList->setItem(0,1, new QTableWidgetItem("AAPL"));
   stockList->setItem(0,2, new QTableWidgetItem("Apple"));
   stockList->setItem(0,3, new QTableWidgetItem("-100"));
   stockList->setItem(0,4, new QTableWidgetItem("-5"));

   QTableWidgetItem* googleIcon = new QTableWidgetItem();
   googleIcon->setIcon(QIcon("GOOG.png"));

   stockList->setItem(1,0, googleIcon);
   stockList->setItem(1,1, new QTableWidgetItem("GOOG"));
   stockList->setItem(1,2, new QTableWidgetItem("Google"));
   stockList->setItem(1,3, new QTableWidgetItem("-100"));
   stockList->setItem(1,4, new QTableWidgetItem("-5"));

   QTableWidgetItem* teslaIcon = new QTableWidgetItem();
   teslaIcon->setIcon(QIcon("TSLA.png"));
   
   stockList->setItem(2,0, teslaIcon);
   stockList->setItem(2,1, new QTableWidgetItem("TSLA"));
   stockList->setItem(2,2, new QTableWidgetItem("Tesla"));
   stockList->setItem(2,3, new QTableWidgetItem("-100"));
   stockList->setItem(2,4, new QTableWidgetItem("-5"));

   QGridLayout *layout = new QGridLayout;
   layout->addWidget(addButton, 0, 0);
   layout->addWidget(symLineEdit, 0, 1);
   layout->addWidget(deleteButton, 1, 0);
   layout->addWidget(stockList, 2, 0, 2, 2);
   layout->addWidget(logoLabel, 4, 0);
   layout->addWidget(detailsLabel, 4, 1);

   QObject::connect(addButton, &QPushButton::clicked, addStock);
   QObject::connect(stockList, &QTableWidget::itemSelectionChanged, updateDetails);

   window->resize(750, 500);
   window->setLayout(layout);
   window->show();
   return app.exec();
}
