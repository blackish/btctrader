#include "tradehistorywidget.h"
#include <QScriptEngine>
#include <QPainter>
#include <QScriptValueIterator>
#include <cmath>

TradeHistoryWidget::TradeHistoryWidget(QWidget *parent) :
    QWidget(parent)
{
    manager = new QNetworkAccessManager ( this );
    trades.clear();
    amounts.clear();
    types.clear();
    min = 999999999;
    max = 0;
    maxAmount = 0;
//    this->setAttribute( Qt::WA_OpaquePaintEvent );
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    path = QPainterPath ();
    path.addEllipse( 0, 0, 6, 6 );

    connect ( manager, SIGNAL ( finished ( QNetworkReply* ) ), this, SLOT ( gotReply ( QNetworkReply* ) ) );
    QNetworkReply* rpl;
    rpl = manager->get ( QNetworkRequest ( QUrl ("https://mtgox.com/code/data/getTrades.php") ) );
    rpl->ignoreSslErrors();

}

TradeHistoryWidget::~TradeHistoryWidget()
{
    delete manager;
}

void TradeHistoryWidget::paintEvent( QPaintEvent* event )
{
    QPen pen;
    QPainter painter ( this );
    float xScale;
    float yScale;
    float yScaleAmount;
    geomX = this->width();
    geomY = this->height();
    items.clear();
    painter.fillRect ( 0, 0, geomX, geomY, QBrush ( Qt::white ) );
    if ( trades.count() == 0 )
        return;
    QList<float> keys = trades.keys();
    qSort ( keys );
    yScale = geomY / ( max - min );
    xScale = geomX / keys.size();
    yScaleAmount = geomY / maxAmount;
    for ( int i=0; i< keys.count(); i++ )
    {
        OrderItem item;
        item.setColor( Qt::green);
        item.setPath( path );
        item.setPosition(QPoint ( (floor ( (  i  ) * xScale) ), geomY - floor ( ( trades.value ( keys.at( i ) ) - min ) *yScale ) ) );
        item.setToolTip(  amounts.value ( keys.at( i ) ) + ";" + QString::number ( trades.value ( keys.at ( i ) ) ) );
        item.setStamp( keys.at ( i ) );
        items.append ( item );
    }
//    pen.setColor( Qt::green );
//    painter.setPen( pen );
  /*  for ( int i=1;i<keys.count() - 1;i++ )
    {
        painter.drawLine(floor ( ( i - 1 ) * xScale ), floor ( geomY - ( trades.value( keys.at ( i - 1 ) ) - min ) * yScale ),floor ( i * xScale ), floor ( geomY - ( trades.value( keys.at ( i ) ) - min ) * yScale ) );
        painter.drawEllipse( floor ( i * xScale ), floor ( geomY - ( trades.value( keys.at ( i ) ) - min ) * yScale ), 2, 2 );
    }*/
    foreach (OrderItem item, items) {
        if ( types.value( item.getStamp() ) == 0 )
            painter.setPen ( Qt::blue );
        else
            painter.setPen ( Qt::red );
//        painter.drawLine( item.position().x() + 3, item.position().y() + 3 - ( amounts.value( item.getStamp() ).toFloat() * yScaleAmount )/2, item.position().x() + 3, item.position().y() + 3 + ( amounts.value( item.getStamp() ).toFloat() * yScaleAmount )/2 );
        painter.drawLine( item.position().x() + 3, geomY, item.position().x() + 3, geomY - ( amounts.value( item.getStamp() ).toFloat() * yScaleAmount ) );
        painter.setPen(item.color());
        painter.setBrush(item.color());
//        painter.drawLine( item.position().x() + 3, item.position().y(), item.position().x()+ 3, floor( geomY) );
        painter.translate(item.position());
        painter.drawPath(item.path());
        painter.translate(-item.position());
    }

}

int TradeHistoryWidget::gotReply ( QNetworkReply* reply )
{
    QByteArray result;
    result = reply->readAll ();
    QScriptValue sc;
    QScriptEngine engine;
    sc = engine.evaluate("({\"trades\":" + QString(result) + "})");
    if ( sc.property ( "trades" ).isObject() )
    {
        QScriptValueIterator iterator ( sc.property( "trades" ) );
        while ( iterator.hasNext() )
        {
            iterator.next();
            trades.insert( iterator.value().property("date" ).toNumber(),iterator.value().property( "price" ).toNumber() );
            amounts.insert ( iterator.value().property("date").toNumber(),iterator.value().property("amount" ).toString() );
            if ( iterator.value().property( "trade_type" ).toString().compare( "bid" ) )
                types.insert ( iterator.value().property("date" ).toNumber(), 0 );
            else
                types.insert ( iterator.value().property("date" ).toNumber(), 1 );

            if ( iterator.value().property( "price" ).toNumber() > max )
                max = iterator.value().property( "price" ).toNumber();
            if ( iterator.value().property( "price" ).toNumber() < min && iterator.value().property( "price" ).toNumber() > 0 )
                min = iterator.value().property( "price" ).toNumber();
            if ( iterator.value().property( "amount" ).toNumber() > maxAmount )
            {
                maxAmount = iterator.value().property( "amount" ).toNumber();
            }
        }
//        maxAmount /= amounts.count();
    }
    update ();
    return 0;
}

void TradeHistoryWidget::mousePressEvent ( QMouseEvent* e )
{
    int index = itemAt ( e->pos() );
    if ( index != -1 )
        QToolTip::showText(e->globalPos(), items[index].toolTip());
    else
        QToolTip::showText(e->globalPos(), "");

}

int TradeHistoryWidget::itemAt(const QPoint &pos)
{
    for (int i = items.size() - 1; i >= 0; --i) {
        const OrderItem &item = items[i];
        if (item.path().contains(pos - item.position()))
            return i;
    }
    return -1;
}
void TradeHistoryWidget::resizeEvent ( QResizeEvent * event )
{
    update();
}
