#include <QApplication>
#include "tickerWindow.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   TickerWindow tickerWindow(750, 500); // create my ticker window
   return app.exec();
}
