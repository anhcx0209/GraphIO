#include "coregraph.h"

CoreGraph::CoreGraph()
{
    list_vertexs_.clear();
    list_edges_.clear();
}

CoreEdge *CoreGraph::createEdge(CoreVertex *a, CoreVertex *b)
{
    CoreEdge *e = 0;
    int i1 = list_vertexs_.indexOf(a);
    int i2 = list_vertexs_.indexOf(b);

    if (i1 != -1 && i2 != -1) {
        e = new CoreEdge(a, b);
        list_edges_.append(e);
    }    

    return e;
}

void CoreGraph::addEdge()
{
    CoreEdge *e = new CoreEdge(0, 0);
    list_edges_.append(e);
}

void CoreGraph::addVertex(CoreVertex *new_vertex)
{
    list_vertexs_.append(new_vertex);    
}

void CoreGraph::removeVertex(CoreVertex *v)
{
    foreach (CoreEdge *e, list_edges_) {
        if (e->getBegin() == v || e->getEnd() == v) {
            list_edges_.removeOne(e);
        }
    }

    list_vertexs_.removeOne(v);
}

void CoreGraph::removeEdge(CoreEdge *e)
{
    list_edges_.removeOne(e);
}

bool CoreGraph::validate()
{
    bool valid = true;
    foreach (CoreEdge *e, list_edges_) {
        valid &= e->valid();
    }
    return valid;
}

bool CoreGraph::hasEdge(CoreVertex *a, CoreVertex *b) const
{
    foreach (CoreEdge *edge, list_edges_)
    {
        if (edge->getBegin() == a && edge->getEnd() == b)
            return true;
    }
    return false;
}

CoreEdge *CoreGraph::edgeBetween(CoreVertex *a, CoreVertex *b) const
{
    foreach (CoreEdge *edge, list_edges_)
    {
        if (edge->getBegin() == a && edge->getEnd() == b)
            return edge;
    }
    return 0;
}

CoreVertex *CoreGraph::findVertex(QString id)
{    
    foreach (CoreVertex *v, list_vertexs_) {
        if (v->id() == id) {
            return v;
        }
    }
    return 0;
}

void CoreGraph::clear()
{
    list_vertexs_.clear();
    list_edges_.clear();
}

void CoreGraph::resetFlag()
{
    foreach (CoreVertex *v, list_vertexs_) {
        v->setFlag(false);
    }
}

QList<CoreVertex *> CoreGraph::bfs(QString start_id)
{
    resetFlag();
    QQueue<CoreVertex *> queue;
    QList<CoreVertex *> ret;
    CoreVertex *start = findVertex(start_id);
    queue.enqueue(start);
    start->setFlag(false);

    CoreVertex *u = 0;
    while (!queue.isEmpty()) {
        u = queue.dequeue();
        ret.append(u);          // visit u
        foreach (CoreVertex *v, list_vertexs_) {
            if (edgeBetween(u, v) != 0 && v->flag() == false) {
                v->setFlag(true);
                queue.enqueue(v);
            }
        }
    }

    return ret;
}
