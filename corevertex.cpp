#include "corevertex.h"

CoreVertex::CoreVertex(QString i)
{
    id_ = i;
    flag_ = false;
}

CoreVertex::CoreVertex(const CoreVertex *obj)
{
    id_ = obj->id();
    flag_ = obj->flag();
}
