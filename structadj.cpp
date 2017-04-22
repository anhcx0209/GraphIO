#include "structadj.h"

StructAdj::StructAdj(CoreGraph *g) : QAbstractTableModel()
{
    graph_ = g;
}

int StructAdj::rowCount(const QModelIndex &) const
{
    return graph_->vertexs().size();
}

int StructAdj::columnCount(const QModelIndex &) const
{
    return 2;
}

QVariant StructAdj::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return graph_->vertexs().at(index.row())->id();
        } else {
            QStringList ret;
            CoreVertex *v = graph_->vertexs().at(index.row());
            for (int i = 0; i < graph_->edges().size(); i++) {
                if (graph_->edges().at(i)->getBegin() == v) {
                    ret << graph_->edges().at(i)->getEnd()->id();
                }
            }
            return ret.join(", ");
        }
    }

    return QVariant();
}
