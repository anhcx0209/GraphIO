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

void CoreGraph::saveAdjMat(QString filename)
{
    QFile f(filename);
    if (f.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&f);
        for (int i = 0; i < vertexs().size(); i++) {
            for (int j = 0; j < vertexs().size(); j++) {
                if (hasEdge(vertexs().at(i), vertexs().at(j))) {
                    out << "1 ";
                } else  {
                    out << "0 ";
                }
            }
            out << endl;
        }
    }
}

void CoreGraph::saveEdgList(QString filename)
{
    QFile f(filename);
    if (f.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&f);
        for (int i = 0; i < edges().size(); i++) {
            out << edges().at(i)->getBegin()->id() << " " <<
                   edges().at(i)->getEnd()->id();
            out << endl;
        }
    }
}

void CoreGraph::saveIncMat(QString filename)
{
    QFile f(filename);
    if (f.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&f);
        for (int i = 0; i < vertexs().size(); i++) {
            for (int j = 0; j < edges().size(); j++) {
                CoreVertex *v = vertexs().at(i);
                CoreEdge *e = edges().at(j);

                if (e->getBegin() == v) {
                    out << "+1 ";
                } else {
                    if (e->getEnd() == v) {
                       out << "-1 ";
                    } else {
                        out << "0 ";
                    }
                }
            }
            out << endl;
        }
    }
}

void CoreGraph::saveStructAdj(QString filename)
{
    QFile f(filename);
    if (f.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&f);
        for (int i = 0; i < vertexs().size(); i++) {
            for (int j = 0; j < edges().size(); j++) {
                if (edges().at(j)->getBegin() == vertexs().at(i)) {
                    out << vertexs().at(i)->id() << ", ";
                }
            }
            out << endl;
        }
    }
}

void CoreGraph::clear()
{
    list_vertexs_.clear();
    list_edges_.clear();
}
