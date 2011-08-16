#include "cancelordermenu.h"
#include "btctrader.h"

CancelOrderMenu::CancelOrderMenu(QWidget *parent) :
    QMenu(parent)
{
}

void CancelOrderMenu::showEvent ( QShowEvent * event )
{
    BTCTrader* parent = (BTCTrader*)parentWidget();
    parent->tableContextMenuActive ();
}

void CancelOrderMenu::hideEvent ( QHideEvent * event )
{
//    BTCTrader* parent = (BTCTrader*)parentWidget();
//    parent->tableContextMenuClosed ();
}
