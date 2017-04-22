#include "enterdialog.h"

EnterDialog::EnterDialog()
{
    type_combobox_ = new QComboBox;
    type_combobox_->addItem(tr("Матрица смежности"));
    type_combobox_->addItem(tr("Матрица инцидентности"));
    type_combobox_->addItem(tr("Матрица весов графа"));
    type_combobox_->addItem(tr("Список ребер графа"));
    type_combobox_->addItem(tr("Структура смежности графа"));
    number_edges_spinbox_ = new QSpinBox;
    number_vertexs_spinbox_ = new QSpinBox;

    graph_ = new CoreGraph();
    table_view_ = new QTableView();

    QHBoxLayout *tableLayout = new QHBoxLayout;
    tableLayout->addWidget(table_view_);

    QLabel *typeLabel = new QLabel(tr("Тип представления"));
    QLabel *edgesLabel = new QLabel(tr("Количество ребер"));
    QLabel *vertexsLabel = new QLabel(tr("Количество вершин"));

    QHBoxLayout *typeLayout = new QHBoxLayout;
    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(type_combobox_);

    QHBoxLayout *edgesLayout = new QHBoxLayout;
    edgesLayout->addWidget(edgesLabel);
    edgesLayout->addWidget(number_edges_spinbox_);

    QHBoxLayout *vertexsLayout = new QHBoxLayout;
    vertexsLayout->addWidget(vertexsLabel);
    vertexsLayout->addWidget(number_vertexs_spinbox_);

    QPushButton *closeButton = new QPushButton(tr("Отмена"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QPushButton *acceptButton = new QPushButton(tr("Вводить"));
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(enterData()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(acceptButton);
    buttonLayout->addWidget(closeButton);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(typeLayout);
    mainLayout->addLayout(edgesLayout);
    mainLayout->addLayout(vertexsLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(tableLayout);
    setLayout(mainLayout);

    setWindowTitle("Вводить данных");
}

void EnterDialog::enterData()
{
    graph_->clear();
    int n = number_vertexs_spinbox_->value();
    for (int i = 0; i < n; i++) {
        CoreVertex *v = new CoreVertex(QString::number(i));
        graph_->addVertex(v);
    }
    table_view_->setModel(new AdjMat(graph_));
}
