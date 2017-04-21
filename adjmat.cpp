#include "adjmat.h"

AdjMat::AdjMat(CoreGraph *g, QObject *parent) : QAbstractTableModel(parent)
{
    graph_ = g;
}

int AdjMat::rowCount(const QModelIndex &/*parent*/) const
{
    return graph_->vertexs().size();
}

int AdjMat::columnCount(const QModelIndex &/*parent*/) const
{
    return graph_->vertexs().size();
}

QVariant AdjMat::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        CoreVertex *a = graph_->vertexs().at(index.row());
        CoreVertex *b = graph_->vertexs().at(index.column());

        if (graph_->hasEdge(a, b))
            return QString("1");
        else
            return QString("0");
    }

    return QVariant();
}
