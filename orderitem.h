#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QPainterPath>
#include <QColor>

class OrderItem
{
public:
    OrderItem();
    void setPath(const QPainterPath &path);
    void setToolTip(const QString &toolTip);
    void setPosition(const QPoint &point);
    void setColor(const QColor &color);

    QPainterPath path() const;
    QPoint position() const;
    QColor color() const;
    QString toolTip() const;

private:
    QPainterPath myPath;
    QPoint myPosition;
    QColor myColor;
    QString myToolTip;
};

#endif // ORDERITEM_H
