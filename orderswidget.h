#ifndef ORDERSWIDGET_H
#define ORDERSWIDGET_H

#include <QWidget>
#include <QMap>
#include <QList>
#include <QPainterPath>
#include "orderitem.h"
#include <QEvent>
#include <QHelpEvent>
#include <QToolTip>
#include <QMouseEvent>

class OrdersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OrdersWidget(QWidget *parent = 0);
    void updateBids ( QMap<float,float> bid );
    void updateAsks ( QMap<float,float> ask );
    ~OrdersWidget ();

signals:

public slots:
protected:
    void paintEvent( QPaintEvent* event );
    void resizeEvent ( QResizeEvent * event );
    bool event(QEvent *event);
    void mousePressEvent ( QMouseEvent* e );
private:
    QMap<float,float> bids;
    QMap<float,float> asks;
//    QList<OrderItem> bidsItems;
    QList<OrderItem> items;
    QPainterPath path;
//    QPainterPath* asksPath;
    float geomX;
    float geomY;
    float minBid;
    float maxAsk;
    float maxVolume;
    float xScale;
    float yScale;
    void recalculate ();
    int itemAt(const QPoint &pos);
};

#endif // ORDERSWIDGET_H
