#include "coreedge.h"

CoreEdge::CoreEdge(CoreVertex *a, CoreVertex *b, qreal w)
{
    begin_ = a;
    end_ = b;
    weight_ = w;
    flag_ = 0;
}

CoreEdge::CoreEdge(const CoreEdge *obj)
{
    id_ = obj->id();
    weight_ = obj->weight();
    flag_ = obj->flag();

    begin_ = new CoreVertex(obj->getBegin());
    end_ = new CoreVertex(obj->getEnd());
}

bool CoreEdge::valid() const
{
    return begin_ != 0 && end_ != 0;
}
