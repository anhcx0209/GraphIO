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
    QString message = "Только принимают значения 0, +1, -1 или 1.\n"
                      "Создать ребро между вершиной и самой собой не позволяет.";
    if (role == Qt::EditRole) {
        CoreVertex *xi = graph_->vertexs().at(index.row());
        CoreEdge *uj = graph_->edges().at(index.column());

        if (value.toString() == "+1" || value.toString() == "1") {
            if (uj->getBegin() == 0) {
                uj->setBegin(xi);
                message = "Успешно задать данные";
            } else {
                message = "Это ребро уже имел начальную верширу";
            }
        }

        if (value.toString() == "-1") {
            if (uj->getEnd() == 0) {
                uj->setEnd(xi);
                message = "Успешно задать данные";
            } else {
                message = "Это ребро уже имел конечную верширу";
            }
        }

        if (value.toString() == "0") {
            if (uj->getBegin() == xi) {
                uj->setBegin(0);
                message = "Успешно задать данные";
            }
            if (uj->getEnd() == xi) {
                uj->setEnd(0);
                message = "Успешно задать данные";
            }
        }
    }

    emit editCompleted(message);
    return true;
}

Qt::ItemFlags IncMat::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
