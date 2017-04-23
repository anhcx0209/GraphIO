#include "newedglist.h"

NewEdgList::NewEdgList() : EnterDialog("Список ребер графа")
{

}

void NewEdgList::enterData()
{
    CoreGraph *g = new CoreGraph;
    int n = number_vertexs_spinbox_->value();
    for (int i = 1; i < n+1; i++) {
        g->addVertex(new CoreVertex(QString::number(i)));
    }
    int m = number_edges_spinbox_->value();
    for (int i = 1; i < m+1; i++) {
        g->addEdge();
    }
    table_view_->setModel(new EdgList(g));
    data_ = g;
}

void NewEdgList::sendData()
{
    if (data_->validate())
        emit finishEnterData(data_);
}
