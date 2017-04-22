#ifndef GRAPHARROW_H
#define GRAPHARROW_H

#include <QGraphicsLineItem>
#include "graphpoint.h"

class GraphArrow : public QGraphicsLineItem
{
public:
    GraphArrow(GraphPoint *, GraphPoint *);

protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    GraphPoint *start_point_;
    GraphPoint *end_point_;
};

#endif // GRAPHARROW_H
