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

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   QWidget *window = new QWidget;
   
   QPushButton *addButton = new QPushButton("Add");
   QPushButton *deleteButton = new QPushButton("Delete");

   QLineEdit *symLineEdit= new QLineEdit;

   QString msg = "These are the stock details. \nThere are lots of lines in here";
   QLabel detailsLabel(msg);

   QTableWidget *tv = new QTableWidget();
   tv->setRowCount(10);
   tv->setColumnCount(5);
   tv->setSelectionBehavior(QAbstractItemView::SelectRows);
   tv->horizontalHeader()->hide();
   tv->horizontalHeader()->setStretchLastSection(true);
   tv->verticalHeader()->hide();
   tv->setShowGrid(false);
   
   QTableWidgetItem* applIcon = new QTableWidgetItem();
   applIcon->setIcon(QIcon("test.png"));

   QLabel logoLabel;
   QPixmap pic("test.png");
   logoLabel.setPixmap(pic);

   
   tv->setItem(0,0, applIcon);
   tv->setItem(0,1, new QTableWidgetItem("AAPL"));
   tv->setItem(0,2, new QTableWidgetItem("Apple"));
   tv->setItem(0,3, new QTableWidgetItem("-100"));
   tv->setItem(0,4, new QTableWidgetItem("-5"));

   tv->setItem(1,0, new QTableWidgetItem(""));
   tv->setItem(1,1, new QTableWidgetItem("GOOG"));
   tv->setItem(1,2, new QTableWidgetItem("Google"));
   tv->setItem(1,3, new QTableWidgetItem("-100"));
   tv->setItem(1,4, new QTableWidgetItem("-5"));

   tv->setItem(2,0, new QTableWidgetItem(""));
   tv->setItem(2,1, new QTableWidgetItem("TSLA"));
   tv->setItem(2,2, new QTableWidgetItem("Tesla"));
   tv->setItem(2,3, new QTableWidgetItem("-100"));
   tv->setItem(2,4, new QTableWidgetItem("-5"));

   QGridLayout *layout = new QGridLayout;
   layout->addWidget(addButton, 0, 0);
   layout->addWidget(symLineEdit, 0, 1);
   layout->addWidget(deleteButton, 1, 0);
   layout->addWidget(tv, 2, 0, 2, 2);
   layout->addWidget(&logoLabel, 4, 0);
   layout->addWidget(&detailsLabel, 5, 0, 5, 2);


   window->resize(750, 500);
   window->setLayout(layout);
   window->show();
   return app.exec();
}
