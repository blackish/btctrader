#ifndef TRADEHISTORYWIDGET_H
#define TRADEHISTORYWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPainterPath>
#include <QList>
#include <QEvent>
#include <QHelpEvent>
#include <QToolTip>
#include <QMouseEvent>
#include "orderitem.h"

class TradeHistoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TradeHistoryWidget(QWidget *parent = 0);
    ~TradeHistoryWidget ();

signals:

public slots:
    int gotReply ( QNetworkReply* );
protected:
    void paintEvent( QPaintEvent* event );
    void mousePressEvent ( QMouseEvent* e );
    void resizeEvent ( QResizeEvent * event );

private:
    QNetworkAccessManager *manager;
    float geomX;
    float geomY;
    float min;
    float max;
    float maxAmount;
    QList<OrderItem> items;
    QPainterPath path;
    int itemAt(const QPoint &pos);

    QMap<float,float> trades;
    QMap<float,QString> amounts;
    QMap<float,int> types;

};

#endif // TRADEHISTORYWIDGET_H
