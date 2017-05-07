#include "corevertex.h"

CoreVertex::CoreVertex(QString i)
{
    id_ = i;
    flag_ = false;
    visit_ = 0;
}

CoreVertex::CoreVertex(const CoreVertex *obj)
{
    id_ = obj->id();
    flag_ = obj->flag();
    visit_ = obj->visit();
}
