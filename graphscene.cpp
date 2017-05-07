#include <QtGui>

#include "graphscene.h"

GraphScene::GraphScene(QObject *parent)
    :QGraphicsScene(parent)
{
    mode_ = MoveItem;
    line_ = 0;
    def_name_ = 1;
    graph_ = 0;
}

void GraphScene::setMode(Mode mode)
{    
    mode_ = mode;
}

void GraphScene::readFrom(QString filename)
{        
    QFile fi(filename);
    if (!fi.open(QFile::ReadOnly | QIODevice::Text))
        return ;

    int n, m, pid;
    int b, e;
    double w;
    qreal px, py;
    clear();
    graph_ = new CoreGraph();
    QList<GraphPoint *> points;

    GraphPoint *point;
    CoreVertex *v;
    GraphPoint *begin, *end;
    GraphArrowExtend *arrow;

    QTextStream in(&fi);
    // Read number of vertexs
    in >> n;
    // Read and create all vertexs
    for (int i = 0; i < n; i++) {
        in >> pid >> px >> py;
        point = new GraphPoint();
        point->setPos(QPointF(px, py));
        v = new CoreVertex(QString::number(pid));
        graph_->addVertex(v);
        point->setVertex(v);
        addItem(point);
        points.append(point);
    }
    // Read number of edges
    in >> m;
    // Read and create all edges
    for (int i = 0; i < m; i++) {
        in >> b >> e >> w;
        // find vertex to add arrow
        for (int j = 0; j < points.size(); j++) {
            if (points.at(j)->vertex()->id().toInt() == b)
                begin = points.at(j);
            if (points.at(j)->vertex()->id().toInt() == e)
                end = points.at(j);
        }
        // add arrow
        arrow = new GraphArrowExtend(begin, end);
        begin->addArrowExtend(arrow);
        end->addArrowExtend(arrow);
        arrow->setZValue(-1000.0);

        CoreEdge *e = graph_->createEdge(begin->vertex(), end->vertex());
        e->setWeight(w);
        arrow->setEdge(e);

        addItem(arrow);
        arrow->updatePosition();
    }
}

void GraphScene::drawGraph(CoreGraph *g)
{
    graph_ = g;
    clear();
    QPointF pos(2150, 2350);
    QPointF delta(50, 50);
    GraphPoint *point;
    GraphArrowExtend *arrow;
    QList<GraphPoint *> listPoints;

    foreach (CoreVertex *v, graph_->vertexs()) {
        point = new GraphPoint();
        point->setVertex(v);
        point->setPos(pos);
        addItem(point);
        listPoints.append(point);
        pos = pos + delta;
    }

    GraphPoint *begin;
    GraphPoint *end;

    foreach (CoreEdge *e, graph_->edges()) {
        CoreVertex *a = e->getBegin();
        CoreVertex *b = e->getEnd();

        // find vertex to add arrow
        for (int j = 0; j < listPoints.size(); j++) {
            if (listPoints.at(j)->vertex() == a)
                begin = listPoints.at(j);
            if (listPoints.at(j)->vertex() == b)
                end = listPoints.at(j);
        }
        arrow = new GraphArrowExtend(begin, end);
        begin->addArrowExtend(arrow);
        end->addArrowExtend(arrow);
        arrow->setEdge(e);
        addItem(arrow);
    }
}

void GraphScene::deleteItem()
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == GraphPoint::Type) {
            graph_->removeVertex(qgraphicsitem_cast<GraphPoint *>(item)->vertex());
            qgraphicsitem_cast<GraphPoint *>(item)->removeArrowsExtend();
        } else {
            graph_->removeEdge(qgraphicsitem_cast<GraphArrowExtend *>(item)->edge());
        }
        removeItem(item);
    }
}

void GraphScene::saveTo(QString filename)
{
    QFile fi(filename);

    if (fi.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&fi);
        QList<QGraphicsItem *>listItem = items();

        // wirte n vertexs
        out << graph_->vertexs().size() << "\n";
        for (int i = 0; i < listItem.size(); i++) {
            if (listItem.at(i)->type() == GraphPoint::Type) {
                // write pos
                GraphPoint *point = qgraphicsitem_cast<GraphPoint *>(listItem.at(i));
                out << point->vertex()->id() << " ";
                out << listItem.at(i)->scenePos().x() << " " << listItem.at(i)->scenePos().y();
                out << "\n";
            }
        }

        // wirte m edges
        QString id_start, id_end;
        double w;
        out << graph_->edges().size() << "\n";
        for (int i = 0; i < graph_->edges().size(); i++) {
            id_start = graph_->edges().at(i)->getBegin()->id();
            id_end = graph_->edges().at(i)->getEnd()->id();
            w = graph_->edges().at(i)->weight();
            out << id_start << " " << id_end << " " << w << "\n";
        }

    }
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{    
    if (mouseEvent->button() != Qt::LeftButton || graph_ == 0)
        return ;

    GraphPoint *point;
    CoreVertex *v;
    QList<QGraphicsItem *> list;
    switch (mode_) {
    case InsertLine:
        line_ = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        line_->setPen(QPen(Qt::black, 2));
        addItem(line_);
        break;
    case InsertItem:
        point = new GraphPoint();
        addItem(point);
        point->setPos(mouseEvent->scenePos());        
        v = new CoreVertex(QString::number(def_name_));
        def_name_++;
        graph_->addVertex(v);
        point->setVertex(v);        
        break;
    default:
        break;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mode_ == InsertLine && line_ != 0)
    {
        QLineF newLine(line_->line().p1(), mouseEvent->scenePos());
        line_->setLine(newLine);
    }
    else
        if (mode_ == MoveItem) QGraphicsScene::mouseMoveEvent(mouseEvent);

}


void GraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line_ != 0 && mode_ == InsertLine)
    {
        QList<QGraphicsItem *> startItems = items(line_->line().p1());
        if (startItems.count() && startItems.first() == line_)
            startItems.removeFirst();

        QList<QGraphicsItem *> endItems = items(line_->line().p2());
        if (endItems.count() && endItems.first() == line_)
            endItems.removeFirst();

        removeItem(line_);
        delete line_;

        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first() != endItems.first())
        {
            GraphPoint *startPoint = qgraphicsitem_cast<GraphPoint *>(startItems.first());
            GraphPoint *endPoint = qgraphicsitem_cast<GraphPoint *>(endItems.first());            

            GraphArrowExtend *arrow = new GraphArrowExtend(startPoint, endPoint);
            startPoint->addArrowExtend(arrow);
            endPoint->addArrowExtend(arrow);
            arrow->setZValue(-1000.0);
            CoreEdge *e = graph_->createEdge(startPoint->vertex(), endPoint->vertex());
            arrow->setEdge(e);
            addItem(arrow);
            arrow->updatePosition();
        }

    }
    line_ = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    if (mode_ == MoveItem) {
        if (selectedItems().size() == 1)
            emit itemSelected(selectedItems().first());
    }
}
