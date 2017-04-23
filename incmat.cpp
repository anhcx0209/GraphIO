#include "incmat.h"
#include <QDebug>

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
//        if (!uj->valid()) {
//            return 0;
//        }

        if (uj->getBegin() == xi) {
            return QVariant("+1");
        }

        if (uj->getEnd() == xi) {
            return QVariant("-1");
        }

        return 0;
    }

    return QVariant();
}

bool IncMat::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        CoreVertex *xi = graph_->vertexs().at(index.row());
        CoreEdge *uj = graph_->edges().at(index.column());

        if (value.toString() == "+1" || value.toString() == "1") {
            if (uj->getBegin() == 0) {
                uj->setBegin(xi);
            } else {
                qDebug() << "this edge already had begin point";
            }
        }

        if (value.toString() == "-1") {
            if (uj->getEnd() == 0) {
                uj->setEnd(xi);
            } else {
                qDebug() << "this edge already had end point";
            }
        }

        if (value.toString() == "0") {
            if (uj->getBegin() == xi) {
                uj->setBegin(0);
            }
            if (uj->getEnd() == xi) {
                uj->setEnd(0);
            }
        }
    }

    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags IncMat::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
