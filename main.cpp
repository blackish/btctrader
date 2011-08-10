#include <QtGui/QApplication>
#include "btctrader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BTCTrader w;
    w.show();

    return a.exec();
}
