#ifndef CANCELORDERMENU_H
#define CANCELORDERMENU_H

#include <QMenu>

class CancelOrderMenu : public QMenu
{
    Q_OBJECT
public:
    explicit CancelOrderMenu(QWidget *parent = 0);

signals:

public slots:
protected:
    void showEvent ( QShowEvent * event );
    void hideEvent ( QHideEvent * event );

};

#endif // CANCELORDERMENU_H
