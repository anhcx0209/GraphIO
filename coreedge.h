#ifndef COREEDGE_H
#define COREEDGE_H

#include <QString>
#include "corevertex.h"

class CoreEdge
{
private:
    QString id_;
    qreal weight_;

    CoreVertex *begin_;
    CoreVertex *end_;
public:
    CoreEdge(CoreVertex *a, CoreVertex *b, qreal w = 0);

    QString id() {return id_;}
    void setId(QString i) {id_ = i;}

    qreal weight() const {return weight_;}
    void setWeight(qreal w) {weight_ = w;}
    bool valid();

    void setBegin(CoreVertex *b) { begin_ = b; }
    void setEnd(CoreVertex *e) { end_ = e; }
    CoreVertex *getBegin() const {return begin_;}
    CoreVertex *getEnd() const {return end_;}
};

#endif // COREEDGE_H
