#ifndef GRAPHARROWEXTEND_H
#define GRAPHARROWEXTEND_H

#include <QGraphicsPathItem>
#include <QtGui>
#include "graphpoint.h"
#include "coreedge.h"

class GraphPoint;

class GraphArrowExtend : public QGraphicsPathItem
{
public slots:
    void updatePosition();
private:
    GraphPoint *start_item_;
    GraphPoint *end_item_;

    QList<QPointF> list_point_;
    int pos_to_insert_;
    QPolygonF arrow_head_;

    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;

    void getBeginEnd(QPointF &begin, QPointF &end);
    int findPosBefore(QPointF point);

    CoreEdge *edge_;

    // Override functions
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QGraphicsSimpleTextItem *w_text_;
public:
    GraphArrowExtend(GraphPoint *start, GraphPoint *end, QGraphicsItem *parrent = 0);
    GraphPoint *startItem() { return start_item_; }
    GraphPoint *endItem() { return end_item_; }

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    CoreEdge *edge() {return edge_;}
    void setEdge(CoreEdge *e) {edge_ = e;}

    enum { Type = UserType + 4 };
    int type() const { return Type; }

};

#endif // GRAPHARROWEXTEND_H
