#include "incmat.h"

IncMat::IncMat(CoreGraph *g)
{
    graph_ = g;
}


int IncMat::rowCount(const QModelIndex &) const
{
    return graph_->vertexs().size();
}

int IncMat::columnCount(const QModelIndex &) const
{
    return graph_->edges().size();
}

QVariant IncMat::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        CoreVertex *xi = graph_->vertexs().at(index.row());
        CoreEdge *uj = graph_->edges().at(index.column());
        if (uj->getBegin() == xi) {
            return 1;
        }

        if (uj->getEnd() == xi) {
            return -1;
        }

        return 0;
    }

    return QVariant();
}
