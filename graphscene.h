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
    GraphScene(QObject *parent = 0);
    void setMode(Mode mode);

    CoreGraph *graph() {return graph_;}
    void setGraph(CoreGraph * g) {graph_ = g;}
    void saveTo(QString filename);
    bool readFrom(QString filename);
    void drawGraph(CoreGraph *g);

public slots:
    void deleteItem();

signals:    
    void itemSelected(QGraphicsItem *);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    CoreGraph *graph_;
    int def_name_;
    Mode mode_;    
    QGraphicsLineItem *line_;
};

#endif // GRAPHSCENE_H
