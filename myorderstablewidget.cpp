#include "myorderstablewidget.h"
#include "btctrader.h"

MyOrdersTableWidget::MyOrdersTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    cancelOrder = new QAction ( tr ( "Cancel Order" ), this );
    contextMenu = new QMenu ();
    contextMenu->addAction( cancelOrder );
    connect ( cancelOrder, SIGNAL ( triggered () ), this, SLOT ( cancelOrderEvent() ) );
}

MyOrdersTableWidget::~MyOrdersTableWidget()
{
    delete cancelOrder;
    delete contextMenu;
}

void MyOrdersTableWidget::contextMenuEvent ( QContextMenuEvent * e )
{
    contextMenu->move( e->globalPos() );
    contextMenu->setVisible( true );
}

void MyOrdersTableWidget::cancelOrderEvent ()
{

    int type;
    if ( this->selectedItems().size() == 0 )
        return;
    int order = this->selectedItems().at(0)->row();
    QString oid = this->item( order, 0 )->text();
    if ( this->item ( order, 1 )->text().contains( "S" ) )
        type = 1;
    else
        type = 2;
    emit cancelOrderSignal ( oid, type );
}
