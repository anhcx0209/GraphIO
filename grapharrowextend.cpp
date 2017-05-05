#include <QtGui>
#include <math.h>

#include "grapharrowextend.h"

const qreal Pi = 3.14;
const qreal D_ANGLE = 5;

GraphArrowExtend::GraphArrowExtend(GraphPoint *start, GraphPoint *end, QGraphicsItem *parent)
    :QGraphicsPathItem(parent)
{        
    start_item_ = start;
    end_item_ = end;
    pos_to_insert_ = 0;
    line1 = 0;
    line2 = 0;

    QPointF p1, p2;
    getBeginEnd(p1, p2);

    list_point_.append(p1);
    list_point_.append(p2);

    QPainterPath initpath(p1);
    initpath.lineTo(p2);
    setPath(initpath);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

void GraphArrowExtend::mousePressEvent(QGraphicsSceneMouseEvent *event)
{    
    pos_to_insert_ = findPosBefore(event->scenePos());
    if (pos_to_insert_ != -1) {
        line1 = new QGraphicsLineItem(QLineF(list_point_[pos_to_insert_], event->scenePos()));
        line2 = new QGraphicsLineItem(QLineF(event->scenePos(), list_point_[pos_to_insert_+1]));

        line1->setPen(QPen(Qt::red));
        line2->setPen(QPen(Qt::red));

        scene()->addItem(line1);
        scene()->addItem(line2);
    } else {
        line1 = 0;
        line2 = 0;
    }

    QGraphicsPathItem::mousePressEvent(event);
}

void GraphArrowExtend::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    if (line1 != 0 & line2 != 0) {
        if (line1->line().angleTo(line2->line()) > 20 && line1->line().angleTo(line2->line()) < 340) {
            if (line1 != 0 && line2 != 0) {
                list_point_.insert(pos_to_insert_+1, line1->line().p2());
                update();
            }
        }

        scene()->removeItem(line1);
        scene()->removeItem(line2);
        delete line1;
        delete line2;
        line1 = 0;
        line2 = 0;
    }

    QGraphicsPathItem::mouseReleaseEvent(event);
}

void GraphArrowExtend::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (line1 != 0 && line2 != 0) {
        QLineF newLine1(line1->line().p1(), event->scenePos());
        QLineF newLine2(event->scenePos(), line2->line().p2());
        line1->setLine(newLine1);
        line2->setLine(newLine2);
    } else {
        QGraphicsPathItem::mouseMoveEvent(event);
    }
}

void GraphArrowExtend::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    double w = QInputDialog::getDouble(0, "Введите вес ребра", "Вес ребра");
    this->edge()->setWeight(w);
    this->updateMicroFocus();
    line1 = 0;
    line2 = 0;
}

void GraphArrowExtend::updatePosition()
{
    QPointF p1, p2;
    getBeginEnd(p1, p2);

    list_point_.first() = p1;
    list_point_.last() = p2;
}

void GraphArrowExtend::getBeginEnd(QPointF &begin, QPointF &end)
{
    QLineF centerLine(start_item_->scenePos(), end_item_->scenePos());
    centerLine.translate(QPointF(25, 25));

    qreal t1 = 25 / centerLine.length();
    qreal t2 = (centerLine.length() - 25) / centerLine.length();
    begin = centerLine.pointAt(t1);
    end = centerLine.pointAt(t2);
}

int GraphArrowExtend::findPosBefore(QPointF point)
{
    for (int i = 0; i < list_point_.size()-1; i++) {
        QLineF l1(list_point_[i], list_point_[i+1]);
        QLineF l2(list_point_[i], point);
        if (fabs(l1.angle() - l2.angle()) < D_ANGLE) {
            return i;
        }
    }
    return -1;
}

void GraphArrowExtend::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (start_item_->collidesWithItem(end_item_))
        return ;

    if (isSelected()) {
        painter->setPen(Qt::blue);
    }

    QPainterPath linePath(list_point_.first());

    for (int i = 1; i < list_point_.size(); i++) {
        linePath.lineTo(list_point_[i]);
    }

    QPointF p1 = list_point_.last();
    QPointF p2 = list_point_.at(list_point_.size() - 2);

    QLineF arrowLine(p1, p2);
    qreal arrowSize = 12;
    double angle = ::acos(arrowLine.dx() / arrowLine.length());

    if (arrowLine.dy() >= 0)
        angle = (2 * Pi) - angle;

    QPointF arrowP1 = arrowLine.p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                            cos(angle + Pi / 3) * arrowSize);

    QPointF arrowP2 = arrowLine.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                            cos(angle + Pi - Pi / 3) * arrowSize);

    arrow_head_.clear();
    arrow_head_ << arrowLine.p1() << arrowP1 << arrowP2;



    linePath.addPolygon(arrow_head_);
    linePath.closeSubpath();
    QPointF baseline = QPointF((list_point_.first().x() + list_point_.at(1).x()) / 2,
                                (list_point_.first().y() + list_point_.at(1).y()) / 2);
    QString wStr = QString("%1").arg(edge()->weight());
    if (edge()->weight() != 0)
        linePath.addText(baseline, painter->font(), wStr);

    setPath(linePath);
    painter->drawPath(path());

    painter->setBrush(QBrush(Qt::black));
    painter->drawPolygon(arrow_head_);

    for (int i = 1; i < list_point_.size()-1; i++) {
        painter->setBrush(Qt::SolidPattern);
        painter->drawEllipse(list_point_[i], 2, 2);
    }
}

QRectF GraphArrowExtend::boundingRect() const
{
    return path().boundingRect();
}
