#include "wmat.h"

WMat::WMat(CoreGraph *g)
{
    graph_ = g;
}


int WMat::rowCount(const QModelIndex &) const
{
    return graph_->vertexs().size();
}

int WMat::columnCount(const QModelIndex &) const
{
    return graph_->vertexs().size();
}

QVariant WMat::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        CoreVertex *v1 = graph_->vertexs().at(index.row());
        CoreVertex *v2 = graph_->vertexs().at(index.column());
        if (graph_->hasEdge(v1, v2)) {
            CoreEdge *e = graph_->edgeBetween(v1, v2);
            return e->weight();
        } else {
            return "oo";
        }
    }
    return QVariant();
}
