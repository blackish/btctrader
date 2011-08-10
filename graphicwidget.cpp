#include "graphicwidget.h"
#include <cmath>
#include <QPainter>

GraphicWidget::GraphicWidget(QWidget *parent) :
    QWidget(parent)
{
    currentMin = 0;
    currentMax = 0;
    currentYAsk = -1;
    currentYBid = -1;
    currentYTrade = -1;
    this->setAttribute( Qt::WA_OpaquePaintEvent );
}

void GraphicWidget::updateAsk ( float ask )
{
    currentMax = ask;
    repaint ();
}

void GraphicWidget::updateBid ( float bid )
{
    currentMin = bid;
    repaint ();
}

void GraphicWidget::updateTrade ( float trade )
{
    currentTrade = trade;
    repaint ();
}

void GraphicWidget::paintEvent( QPaintEvent* event )
{
    int geomX;
    int geomY;
    float scale;
    float min;
    float max;
    QPen pen;
    QPainter painter ( this );
    geomY = this->height();
    geomX = this->width();
    if ( currentYAsk < 0 || currentYBid < 0 ||  currentYTrade < 0 )
     {
         painter.fillRect ( 0, 0, geomX, geomY, QBrush ( Qt::white ) );
         currentYAsk = 0;
         currentYBid = 0;
         currentYTrade = 0;
     }

    if ( currentYAsk >= geomX || currentYAsk < 0 || currentYBid >= geomX || currentYBid < 0 || currentYTrade >= geomX || currentYTrade < 0 )
    {
        currentYAsk = 0;
        currentYBid = 0;
        currentYTrade = 0;
        for ( int i=0;i<geomX;i++ )
        {
            pen.setColor ( Qt::white );
            painter.setPen ( pen );
            painter.drawEllipse(currentYTrade,i, 2, 2 );
            pen.setColor ( Qt::yellow );
            painter.setPen ( pen );
            painter.drawEllipse(currentYTrade+2,i, 2, 2 );
        }
    }
/*    if ( currentMax - currentMin < 0.1 )
    {
        min = floor ( currentMin * 10 ) / 10;
        max = ( floor ( currentMax * 10 ) + 1 ) / 10;
    } else {*/
        min = floor ( currentMin );
        max = floor ( currentMax ) + 1;
//    }
    scale = geomY/( max - min );
    pen.setColor ( Qt::white );
    painter.setPen ( pen );
    for ( int i=0;i<geomX;i++ )
    {
        pen.setColor ( Qt::white );
        painter.setPen ( pen );
        painter.drawEllipse(currentYTrade+2,i, 2, 2 );
        pen.setColor ( Qt::yellow );
        painter.setPen ( pen );
        painter.drawEllipse(currentYTrade+4,i, 2, 2 );
    }
    pen.setColor ( Qt::blue );
    painter.setPen ( pen );
    painter.drawEllipse(currentYBid, geomY - floor ((currentMin-min)*scale ), 2, 2 );
    currentYBid+=2;
    pen.setColor ( Qt::red );
    painter.setPen ( pen );
    painter.drawEllipse(currentYAsk, geomY - floor ( (currentMax - min)*scale ), 2, 2 );
    currentYAsk+=2;
    pen.setColor ( Qt::green );
    painter.setPen ( pen );
    painter.drawEllipse(currentYAsk, geomY - floor ( (currentTrade - min)*scale ), 2, 2 );
    currentYTrade+=2;

}

void GraphicWidget::resizeEvent ( QResizeEvent * event )
{
    currentYAsk = -1;

}

