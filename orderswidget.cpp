#include "orderswidget.h"
#include <cmath>
#include <QPainter>

OrdersWidget::OrdersWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setAttribute( Qt::WA_OpaquePaintEvent );
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    minBid = 21000001;
    maxAsk = 0;
    maxVolume = 0;
    path = QPainterPath ();
    path.addEllipse( 0, 0, 6, 6 );


}

OrdersWidget::~OrdersWidget()
{
}

void OrdersWidget::updateBids ( QMap<float,float> bid )
{
    bids.clear();
    for ( int i=0;i<bid.keys().count();i++ )
    {
        bids.insert ( bid.keys().at(i), bid.value ( bid.keys().at(i) ) );
    }

    recalculate ();
}

void OrdersWidget::recalculate (){
    QList<float> bidsList;
    QList<float> bidsValues;
    QList<float> asksList;
    QList<float> asksValues;

    minBid = 21000001;
    maxAsk = 0;
    maxVolume = 0;

    bidsList = bids.keys ();
    bidsValues = bids.values();
    asksList = asks.keys();
    asksValues = asks.values ();

    if ( bidsList.count() == 0 || asksList.count() == 0 )
        return;
    qSort ( asksValues );
    qSort ( bidsList );
    qSort ( asksList );
    qSort ( bidsValues );
    if ( minBid > bidsList.at ( 0 ) )
        minBid = bidsList.at ( 0 );
    if ( maxVolume < bidsValues.at ( bidsValues.count() - 1 ) )
        maxVolume = bidsValues.at ( bidsValues.count() - 1 );
    if ( maxAsk < asksList.at ( asksList.count() - 1 ) )
        maxAsk = asksList.at ( asksList.count() - 1 );
    if ( maxVolume < asksValues.at ( asksValues.count() - 1 ) )
        maxVolume = asksValues.at ( asksValues.count() - 1 );


    items.clear();
    xScale = geomX / ( maxAsk - minBid );
    yScale = geomY / ( maxVolume );

    for ( int i=0;i<bidsList.count();i++ )
    {
        OrderItem item;
        item.setColor( Qt::blue);
        item.setPath( path );
        item.setPosition(QPoint ( (floor ( ( bidsList.at ( i ) - minBid) * xScale) ), geomY - floor (bids.value ( bidsList.at( i ) )*yScale ) ) );
        item.setToolTip( QString::number ( bidsList.at( i ) ) + ";" + QString::number ( bids.value ( bidsList.at ( i ) ) ) );
        items.append ( item );
    }

    for ( int i=0;i<asksList.count();i++ )
    {
        OrderItem item;
        item.setColor( Qt::red);
        item.setPath( path );
        item.setPosition( QPoint ( (floor ( ( asksList.at ( i ) - minBid) * xScale) ), geomY - floor (asks.value ( asksList.at( i ) )*yScale ) ) );
        item.setToolTip( QString::number ( asksList.at( i ) ) + ";" + QString::number (asks.value ( asksList.at ( i ) ) ) );
        items.append ( item );
    }
    update ();
}

void OrdersWidget::updateAsks ( QMap<float,float> ask )
{
    asks.clear();
    for ( int i=0;i<ask.keys().count();i++ )
    {
        asks.insert ( ask.keys().at(i), ask.value ( ask.keys().at(i) ) );
    }
    recalculate ();
}

void OrdersWidget::paintEvent( QPaintEvent* event )
{
    QPen pen;
    QPainter painter ( this );
    geomX = this->width();
    geomY = this->height();
    painter.fillRect ( 0, 0, geomX, geomY, QBrush ( Qt::white ) );

    foreach (OrderItem item, items) {
        painter.setPen(item.color());
        painter.setBrush(item.color());
        painter.drawLine( item.position().x() + 3, item.position().y(), item.position().x()+ 3, floor( geomY) );
        painter.translate(item.position());
        painter.drawPath(item.path());
        painter.translate(-item.position());
    }
}

void OrdersWidget::resizeEvent ( QResizeEvent * event )
{

}

bool OrdersWidget::event(QEvent *event)
{
    return QWidget::event(event);
}

void OrdersWidget::mousePressEvent ( QMouseEvent* e )
{
    int index = itemAt ( e->pos() );
    if ( index != -1 )
        QToolTip::showText(e->globalPos(), items[index].toolTip());
    else
        QToolTip::showText(e->globalPos(), "");

}

int OrdersWidget::itemAt(const QPoint &pos)
{
    for (int i = items.size() - 1; i >= 0; --i) {
        const OrderItem &item = items[i];
        if (item.path().contains(pos - item.position()))
            return i;
    }
    return -1;
}
