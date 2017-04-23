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

bool StructAdj::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        QStringList listId = value.toString().remove(QChar(' ')).split(',');
        CoreVertex *u = graph_->vertexs().at(index.row());
        CoreVertex *v = 0;
        foreach (QString id, listId) {
            v = graph_->findVertex(id);
            if (v != 0 && v != u) {
                graph_->createEdge(u, v);
            }
        }
    }

    dataChanged(index, index);
    return true;
}

QVariant StructAdj::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal && section == 0)
            return QVariant("Вершина");
        if (orientation == Qt::Horizontal && section == 1)
            return QVariant("Структура смежности");
    }

    return QVariant();
}

Qt::ItemFlags StructAdj::flags(const QModelIndex &index) const
{
    if (index.column() == 1) {
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    } else
        return Qt::NoItemFlags;
}
