#include "grapharrow.h"

GraphArrow::GraphArrow(GraphPoint *start, GraphPoint *end)
{
    start_point_ = start;
    end_point_ = end;
}

void GraphArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF newLine(start_point_->scenePos(), start_point_->scenePos());
    setLine(newLine);

    painter->drawLine(line());
}
