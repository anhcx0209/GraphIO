#ifndef COREEDGE_H
#define COREEDGE_H

#include <QString>
#include "corevertex.h"

class CoreEdge
{
private:
    QString id_;
    qreal weight_;
    bool flag_;

    CoreVertex *begin_;
    CoreVertex *end_;
public:
    CoreEdge(CoreVertex *a, CoreVertex *b, qreal w = 0);            // default constructor
    CoreEdge(const CoreEdge *);                                     // copy constructor

    QString id() const {return id_;}
    void setId(QString i) {id_ = i;}

    qreal weight() const {return weight_;}
    void setWeight(qreal w) {weight_ = w;}
    bool valid() const;

    CoreVertex *getBegin() const {return begin_;}
    void setBegin(CoreVertex *b) { begin_ = b; }

    CoreVertex *getEnd() const {return end_;}
    void setEnd(CoreVertex *e) { end_ = e; }

    bool flag() const { return flag_; }
    void setFlag(bool value) { flag_ = value; }
};

#endif // COREEDGE_H
