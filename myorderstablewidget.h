#ifndef MYORDERSTABLEWIDGET_H
#define MYORDERSTABLEWIDGET_H

#include <QTableWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <cancelordermenu.h>

class MyOrdersTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit MyOrdersTableWidget(QWidget *parent = 0);
    CancelOrderMenu* contextMenu;
    QAction* cancelOrder;
    ~MyOrdersTableWidget ();

signals:

public slots:
protected:
    void contextMenuEvent ( QContextMenuEvent * e );
private slots:
    void cancelOrderEvent ();
signals:
    void cancelOrderSignal ( QString, int );
};

#endif // MYORDERSTABLEWIDGET_H
