#include "edglist.h"

EdgList::EdgList(CoreGraph *g)
{
    graph_ = g;
}

int EdgList::rowCount(const QModelIndex &) const
{
    return graph_->edges().size();
}

int EdgList::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant EdgList::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return graph_->edges().at(index.row())->getBegin()->id();
        } else {
            return graph_->edges().at(index.row())->getEnd()->id();
        }
    }
    return QVariant();
}
