#ifndef COREGRAPH_H
#define COREGRAPH_H

#include "coreedge.h"
#include "corevertex.h"
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QStack>
#include <QQueue>

class CoreGraph : public QObject
{
    Q_OBJECT

private:
    QList<CoreVertex *> list_vertexs_;
    QList<CoreEdge *> list_edges_;
public:
    CoreGraph();

    CoreEdge *createEdge(CoreVertex *a, CoreVertex *b);
    void addEdge();
    void addVertex(CoreVertex *new_vertex);
    void removeVertex(CoreVertex *v);
    void removeEdge(CoreEdge *e);
    bool validate();

    bool hasEdge(CoreVertex *a, CoreVertex *b) const;
    CoreEdge *edgeBetween(CoreVertex *a, CoreVertex *b) const;
    CoreVertex* findVertex(QString id);

    int size() const {return list_vertexs_.size();}
    void clear();

    QList<CoreVertex *> vertexs() const {return list_vertexs_;}
    QList<CoreEdge *> edges() const {return list_edges_;}

    void eraseFlag();
    void bfs(CoreVertex *);
    void dfs(CoreVertex *);
};

#endif // COREGRAPH_H
