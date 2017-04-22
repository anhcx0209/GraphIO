#include <QString>

#include "graphpoint.h"

GraphPoint::GraphPoint(QGraphicsItem *parent)
    :QGraphicsEllipseItem(parent)
{
    setRect(QRectF(0, 0, 50, 50));    
    arrows_extend_.clear();    

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void GraphPoint::addArrowExtend(GraphArrowExtend *arrow)
{
    arrows_extend_.append(arrow);
}

void GraphPoint::removeArrowExtend(GraphArrowExtend *arrow)
{
    int i = arrows_extend_.indexOf(arrow);
    if (i != -1) arrows_extend_.removeAt(i);
}

void GraphPoint::removeArrowsExtend()
{
    foreach (GraphArrowExtend *arrow, arrows_extend_) {
        arrow->startItem()->removeArrowExtend(arrow);
        arrow->endItem()->removeArrowExtend(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

QVariant GraphPoint::itemChange(GraphicsItemChange change, const QVariant &value)
{    
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (GraphArrowExtend *arrow, arrows_extend_) {
            arrow->updatePosition();
        }
    }

    return value;
}

void GraphPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{    
    painter->drawEllipse(rect());
    painter->drawText(rect(), Qt::AlignCenter, vertex()->id());

    if (isSelected()) {
        painter->setPen(Qt::DashLine);
        painter->drawRect(rect());
    }
}
