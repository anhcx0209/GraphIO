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

bool AdjMat::setData(const QModelIndex & index, const QVariant & value, int role)
{
    QString message = "Только принимают значения 0 или 1.\nСоздать ребро между вершиной и самой собой не позволяет.";

    if (role == Qt::EditRole) {
        CoreVertex *a = graph_->vertexs().at(index.row());
        CoreVertex *b = graph_->vertexs().at(index.column());
        if (a != b) {
            if (value.toInt() == 0) {
                if (graph_->hasEdge(a, b)) {
                    CoreEdge *e = graph_->edgeBetween(a, b);
                    graph_->removeEdge(e);
                    message = "Успешно задать данные";
                }
            }

            if (value.toInt() == 1) {
                if (!graph_->hasEdge(a, b)) {
                    graph_->createEdge(a, b);
                    message = "Успешно задать данные";
                }
            }
        }
    }

    emit editCompleted(message);
    return true;
}

Qt::ItemFlags AdjMat::flags(const QModelIndex & /*index*/) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}
