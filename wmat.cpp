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
            return QVariant(e->weight());
        } else {
            return QVariant("oo");
        }
    }
    return QVariant();
}

bool WMat::setData(const QModelIndex & index, const QVariant & value, int role)
{
    QString message = "Чтобы удалить ребро, вводить значение 'oo'."
                      "\nСоздать ребро между вершиной и самой собой не позволяет.";
    if (role == Qt::EditRole) {
        CoreVertex *a = graph_->vertexs().at(index.row());
        CoreVertex *b = graph_->vertexs().at(index.column());
        if (a != b) {
            if (value.toString() == "oo") {
                if (graph_->hasEdge(a, b)) {
                    CoreEdge *e = graph_->edgeBetween(a, b);
                    graph_->removeEdge(e);
                    message = "Успешно задать данные";
                }
            }
            bool ok;
            double w = value.toDouble(&ok);
            if (ok) {
                CoreEdge *e = 0;
                if (!graph_->hasEdge(a, b)) {
                    e = graph_->createEdge(a, b);
                    message = "Успешно задать данные";
                } else {
                    e = graph_->edgeBetween(a, b);
                    message = "Успешно задать данные";
                }
                e->setWeight(w);
            }
        }
    }
    emit editCompleted(message);
    return true;
}

Qt::ItemFlags WMat::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
