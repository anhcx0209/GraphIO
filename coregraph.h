#ifndef COREGRAPH_H
#define COREGRAPH_H

#include "coreedge.h"
#include "corevertex.h"
#include <QList>
#include <QFile>
#include <QTextStream>

class CoreGraph : public QObject
{
    Q_OBJECT

private:
    QList<CoreVertex *> list_vertexs_;
    QList<CoreEdge *> list_edges_;
signals:
    void changed();

public:
    CoreGraph();

    CoreEdge *createEdge(CoreVertex *a, CoreVertex *b);
    void addVertex(CoreVertex *new_vertex);
    void removeVertex(CoreVertex *v);
    void removeEdge(CoreEdge *e);

    bool hasEdge(CoreVertex *a, CoreVertex *b) const;
    CoreEdge *edgeBetween(CoreVertex *a, CoreVertex *b) const;

    int size() const {return list_vertexs_.size();}
    void clear();

    QList<CoreVertex *> vertexs() const {return list_vertexs_;}
    QList<CoreEdge *> edges() const {return list_edges_;}

    void saveAdjMat(QString filename);
    void saveEdgList(QString filename);
    void saveIncMat(QString filename);
    void saveStructAdj(QString filename);
};

#endif // COREGRAPH_H
