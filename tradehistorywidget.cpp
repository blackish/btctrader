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
    min = 999999999;
    max = 0;
    connect ( manager, SIGNAL ( finished ( QNetworkReply* ) ), this, SLOT ( gotReply ( QNetworkReply* ) ) );
    manager->get ( QNetworkRequest ( QUrl ("https://mtgox.com/code/data/getTrades.php") ) );

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
    geomX = this->width();
    geomY = this->height();
    painter.fillRect ( 0, 0, geomX, geomY, QBrush ( Qt::white ) );
    if ( trades.count() == 0 )
        return;
    QList<float> keys = trades.keys();
    qSort ( keys );
    yScale = geomY / ( max - min );
    xScale = geomX / keys.size();
    pen.setColor( Qt::green );
    painter.setPen( pen );
    for ( int i=1;i<keys.count() - 1;i++ )
    {
        painter.drawLine(floor ( ( i - 1 ) * xScale ), floor ( geomY - ( trades.value( keys.at ( i - 1 ) ) - min ) * yScale ),floor ( i * xScale ), floor ( geomY - ( trades.value( keys.at ( i ) ) - min ) * yScale ) );
        painter.drawEllipse( floor ( i * xScale ), floor ( geomY - ( trades.value( keys.at ( i ) ) - min ) * yScale ), 2, 2 );
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
            if ( iterator.value().property( "price" ).toNumber() > max )
                max = iterator.value().property( "price" ).toNumber();
            if ( iterator.value().property( "price" ).toNumber() < min && iterator.value().property( "price" ).toNumber() > 0 )
                min = iterator.value().property( "price" ).toNumber();
        }
    }
    update ();
    return 0;
}
