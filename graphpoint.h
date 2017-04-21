#ifndef GRAPHPOINT_H
#define GRAPHPOINT_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "grapharrowextend.h"
#include "coregraph.h"

class GraphArrowExtend;

class GraphPoint : public QGraphicsEllipseItem
{
public:
    GraphPoint(QMenu *contextMenu, QGraphicsItem *parent = 0);

    enum {Type = UserType + 15};
    int type() const { return Type; }

    void removeArrowsExtend();
    void addArrowExtend(GraphArrowExtend *arrow);
    void removeArrowExtend(GraphArrowExtend *arrow);

    CoreVertex *vertex() {return vertex_;}
    void setVertex(CoreVertex *v) {vertex_ = v;}
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QMenu *context_menu_;
    QList<GraphArrowExtend *> arrows_extend_;
    CoreVertex *vertex_;
};

#endif // GRAPHPOINT_H
