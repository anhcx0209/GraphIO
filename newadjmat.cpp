#include "newadjmat.h"

NewAdjMat::NewAdjMat() : EnterDialog("Матрица смежности")
{
    number_edges_spinbox_->setEnabled(false);    
}

void NewAdjMat::enterData()
{
    CoreGraph *g = new CoreGraph;
    int n = number_vertexs_spinbox_->value();
    for (int i = 1; i < n+1; i++) {
        g->addVertex(new CoreVertex(QString::number(i)));
    }

    AdjMat *model = new AdjMat(g);
    table_view_->setModel(model);
    connect(model, SIGNAL(editCompleted(QString)), this, SLOT(notice(QString)));
    data_ = g;
}
