#include "coreedge.h"

CoreEdge::CoreEdge(CoreVertex *a, CoreVertex *b, qreal w)
{
    begin_ = a;
    end_ = b;
    weight_ = w;
}

bool CoreEdge::valid()
{
    return begin_ != 0 && end_ != 0;
}
