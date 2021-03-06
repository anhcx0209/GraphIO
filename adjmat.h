#ifndef ADJMAT_H
#define ADJMAT_H

#include <QFile>
#include <QTextStream>
#include <QAbstractTableModel>
#include <QDebug>
#include "coregraph.h"

class AdjMat : public QAbstractTableModel
{
    Q_OBJECT    
public:
    AdjMat(CoreGraph *g, QObject *parent=0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
    CoreGraph *graph() const {return graph_;}
    void setGraph(CoreGraph *g) { graph_ = g; }

    void save(QString filename);
private:
    CoreGraph *graph_;
signals:
    void editCompleted(const QString &);
};

#endif // ADJMAT_H
