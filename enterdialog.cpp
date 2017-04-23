#include "enterdialog.h"

EnterDialog::EnterDialog(QString name)
{
    name_ = name;
    data_ = 0;

    number_edges_spinbox_ = new QSpinBox;
    number_vertexs_spinbox_ = new QSpinBox;

    table_view_ = new QTableView();
    QHBoxLayout *tableLayout = new QHBoxLayout;
    tableLayout->addWidget(table_view_);

    QLabel *edgesLabel = new QLabel(tr("Количество ребер"));
    QLabel *vertexsLabel = new QLabel(tr("Количество вершин"));

    QHBoxLayout *edgesLayout = new QHBoxLayout;
    edgesLayout->addWidget(edgesLabel);
    edgesLayout->addWidget(number_edges_spinbox_);

    QHBoxLayout *vertexsLayout = new QHBoxLayout;
    vertexsLayout->addWidget(vertexsLabel);
    vertexsLayout->addWidget(number_vertexs_spinbox_);

    QPushButton *acceptButton = new QPushButton(tr("Вводить"));
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(enterData()));
    QHBoxLayout *changeTableLayout = new QHBoxLayout;
    changeTableLayout->addWidget(acceptButton);

    QPushButton *finishButton = new QPushButton(tr("Завершать"));
    connect(finishButton, SIGNAL(clicked()), this, SLOT(sendData()));
    QPushButton *closeButton = new QPushButton(tr("Отмена"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(finishButton);
    buttonLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;    
    mainLayout->addLayout(edgesLayout);
    mainLayout->addLayout(vertexsLayout);
    mainLayout->addLayout(changeTableLayout);
    mainLayout->addLayout(tableLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(name_);
}
