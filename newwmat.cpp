#include "newwmat.h"

NewWMat::NewWMat(QString name) : EnterDialog(name)
{
    number_edges_spinbox_->setEnabled(false);
}

void NewWMat::enterData()
{    
    CoreGraph *g = new CoreGraph;
    int n = number_vertexs_spinbox_->value();
    for (int i = 1; i < n+1; i++) {
        g->addVertex(new CoreVertex(QString::number(i)));
    }
    table_view_->setModel(new WMat(g));
    data_ = g;
}

void NewWMat::sendData()
{
    if (data_->validate()) {
        emit finishEnterData(data_);
    } else {
        qDebug() << "invalid data";
    }
}
