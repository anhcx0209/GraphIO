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

    StructAdj *model = new StructAdj(g);
    table_view_->setModel(model);
    connect(model, SIGNAL(editCompleted(QString)), this, SLOT(notice(QString)));

    data_ = g;
}


