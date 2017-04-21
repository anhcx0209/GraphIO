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
};

#endif // EDGLIST_H
