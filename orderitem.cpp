#include "orderitem.h"

OrderItem::OrderItem()
{
}

QPainterPath OrderItem::path() const
{
    return myPath;
}

QPoint OrderItem::position() const
{
    return myPosition;
}

QColor OrderItem::color() const
{
    return myColor;
}

QString OrderItem::toolTip() const
{
    return myToolTip;
}

float OrderItem::getStamp() const
{
    return stamp;
}

void OrderItem::setStamp ( const float& st )
{
    stamp = st;
}

void OrderItem::setPath(const QPainterPath &path)
{
    myPath = path;
}

void OrderItem::setToolTip(const QString &toolTip)
{
    myToolTip = toolTip;
}

void OrderItem::setPosition(const QPoint &point )
{
    myPosition = point;
}

void OrderItem::setColor(const QColor &color)
{
    myColor = color;
}
