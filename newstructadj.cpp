#include "newstructadj.h"

NewStructAdj::NewStructAdj() : EnterDialog("Структура смежности графа")
{
    number_edges_spinbox_->setEnabled(false);
}

void NewStructAdj::enterData()
{
    CoreGraph *g = new CoreGraph;
    int n = number_vertexs_spinbox_->value();
    for (int i = 1; i < n+1; i++) {
        g->addVertex(new CoreVertex(QString::number(i)));
    }
    table_view_->setModel(new StructAdj(g));
    data_ = g;
}

void NewStructAdj::sendData()
{
    if (data_->validate())
        emit finishEnterData(data_);
}


