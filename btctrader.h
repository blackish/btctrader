#ifndef BTCTRADER_H
#define BTCTRADER_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include "graphicwidget.h"
#include "orderswidget.h"
#include "myorderstablewidget.h"
#include <QSettings>


namespace Ui {
    class BTCTrader;
}

class BTCTrader : public QMainWindow
{
    Q_OBJECT

public:
    explicit BTCTrader(QWidget *parent = 0);
    ~BTCTrader();

private:
    Ui::BTCTrader *ui;
    QNetworkAccessManager *request;
    GraphicWidget* graph;
    OrdersWidget* ordersGraph;
    QTimer* timerDepth;
    QTimer* timerTicker;
    QTimer* timerBalance;
    QTimer* timerOrders;
    float balance;
    float balanceUSD;
    float fee;
    MyOrdersTableWidget* myOrderTableWidget;
    QString goxLogin;
    QString goxPassword;
    bool failedLogin;
    int errorCount;
    int poolInterval;
    qint64 nonce;
    QString restKey;
    QString restSign;
    QSettings* btctrader;
    void sendBuyRequest ( float amount, float price );
    void sendSellRequest ( float amount, float price );
    void signRequest ( QString* header, QNetworkRequest* newRequest );
    void openKeys ( QString );
    void saveKeys ( QString );

public slots:
    int gotReply ( QNetworkReply* );
    void sendDepthRequest ();
    void sendTickerRequest ();
    void sendBalanceRequest ();
    void sendOrdersRequest ();
    void sendCancelOrderRequest ( QString oid, int type );
    void buyTextEdited ( QString );
    void sellTextEdited ( QString );
    void buyOrder ( bool );
    void sellOrder ( bool );
    void preferences ();
    void tradeHistory ();
    void clearError ();
};

#endif // BTCTRADER_H
