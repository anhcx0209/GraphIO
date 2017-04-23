#ifndef EDGLIST_H
#define EDGLIST_H

#include <QAbstractTableModel>
#include "coregraph.h"

class EdgList : public QAbstractTableModel
{
private:
    CoreGraph *graph_;
public:
    EdgList(CoreGraph *);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // EDGLIST_H
