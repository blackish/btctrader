#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>

class GraphicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicWidget(QWidget *parent = 0);
    void updateBid ( float bid );
    void updateAsk ( float ask );
    void updateTrade ( float trade );

signals:

public slots:
private:
    float currentMin;
    float currentMax;
    float currentTrade;
    int currentYAsk;
    int currentYBid;
    int currentYTrade;
protected:
    void paintEvent( QPaintEvent* event );
    void resizeEvent ( QResizeEvent * event );
};

#endif // GRAPHICWIDGET_H
