#ifndef COREGRAPH_H
#define COREGRAPH_H

#include "coreedge.h"
#include "corevertex.h"
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QStack>
#include <QQueue>
#include <QDebug>

class CoreGraph : public QObject
{
    Q_OBJECT

private:
    QList<CoreVertex *> list_vertexs_;
    QList<CoreEdge *> list_edges_;

public:
    CoreGraph();                                            // default constructor
    CoreGraph(const CoreGraph *obj);                        // copy constructor

    CoreEdge *createEdge(CoreVertex *a, CoreVertex *b);
    void addEdge();                                         // Add "null" edge
    void addVertex(CoreVertex *new_vertex);                 // Add vertex
    void removeVertex(CoreVertex *v);                       // Remove vertex
    void removeEdge(CoreEdge *e);                           // Remove edge
    bool validate() const;                                  // Check if valid graph

    bool hasEdge(CoreVertex *a, CoreVertex *b) const;           // Check if has edge from a to b
    CoreEdge *edgeBetween(CoreVertex *a, CoreVertex *b) const;  // Find edge between a and b
    CoreVertex* findVertex(QString id);                         // Find vertex has name id

    int size() const {return list_vertexs_.size();}         // Return size of graph
    void clear();                                           // Clear graph, remove all edges and vertexs

    QList<CoreVertex *> vertexs() const {return list_vertexs_;} // Return vertexs's list
    QList<CoreEdge *> edges() const {return list_edges_;}       // Return edges's list

    void resetFlag();                                       // reset all flag of graph
};

#endif // COREGRAPH_H
