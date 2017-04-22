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
    GraphPoint(QGraphicsItem *parent = 0);

    enum {Type = UserType + 15};
    int type() const override { return Type; }

    void removeArrowsExtend();
    void addArrowExtend(GraphArrowExtend *arrow);
    void removeArrowExtend(GraphArrowExtend *arrow);

    CoreVertex *vertex() {return vertex_;}
    void setVertex(CoreVertex *v) {vertex_ = v;}
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:    
    QList<GraphArrowExtend *> arrows_extend_;
    CoreVertex *vertex_;
};

#endif // GRAPHPOINT_H
