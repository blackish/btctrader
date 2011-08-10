#ifndef MYORDERSTABLEWIDGET_H
#define MYORDERSTABLEWIDGET_H

#include <QTableWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>

class MyOrdersTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit MyOrdersTableWidget(QWidget *parent = 0);
    QMenu* contextMenu;
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
