#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include "coregraph.h"
#include "graphpoint.h"
#include "grapharrowextend.h"

class GraphScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, MoveItem, InsertLine };
    GraphScene(QMenu *menu, QObject *parent = 0);
    void setMode(Mode mode);

    CoreGraph *graph() {return graph_;}
    void setGraph(CoreGraph * g) {graph_ = g;}
    void saveTo(QString filename);
    void readFrom(QString filename);
signals:
    void itemInserted(GraphPoint *item);
    void arrowInserted(GraphArrowExtend *arrow);
    void itemSelected(QGraphicsItem *);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    CoreGraph *graph_;
    int def_name_;
    Mode mode_;
    QMenu *item_menu_;
    QGraphicsLineItem *line_;
};

#endif // GRAPHSCENE_H
