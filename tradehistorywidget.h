#ifndef TRADEHISTORYWIDGET_H
#define TRADEHISTORYWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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

private:
    QNetworkAccessManager *manager;
    float geomX;
    float geomY;
    float min;
    float max;
    QMap<float,float> trades;

};

#endif // TRADEHISTORYWIDGET_H
