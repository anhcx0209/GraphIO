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
        CoreEdge *e = graph_->edges().at(index.row());

        if (index.column() == 0) {
            if (e->getBegin() != 0) {
                return QVariant(e->getBegin()->id());
            }
        } else {
            if (e->getEnd() != 0) {
                return QVariant(e->getEnd()->id());
            }
        }
    }
    return QVariant();
}

bool EdgList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QString allow_vertex_mess = "Разрешить имя вершины: 1-" + QString::number(graph_->edges().size());
    QString message = allow_vertex_mess + "\nСоздать ребро между вершиной и самой собой не позволяет";
    if (role == Qt::EditRole) {
        bool ok;
        value.toInt(&ok);
        CoreEdge *e = graph_->edges().at(index.row());
        CoreVertex *v = 0;
        if (ok) {
            v = graph_->findVertex(value.toString());

            if (index.column() == 0 && v != 0) {
                if (e->getEnd() != v) {
                    e->setBegin(v);
                    message = "Успешно задать данные.";
                }
            }

            if (index.column() == 1 && v != 0) {
                if (e->getBegin() != v) {
                    e->setEnd(v);
                    message = "Успешно задать данные.";
                }
            }
        }
    }

    emit editCompleted(message);
    return true;
}

Qt::ItemFlags EdgList::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QVariant EdgList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal && section == 0)
            return QVariant("Начало");
        if (orientation == Qt::Horizontal && section == 1)
            return QVariant("Конец");
    }
    return QVariant();
}
