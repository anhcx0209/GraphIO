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

    QGroupBox *logGroup = new QGroupBox("Сообщение");
    log_label_ = new QLabel;
    QHBoxLayout *logLayout = new QHBoxLayout;
    logLayout->addWidget(log_label_);
    logGroup->setLayout(logLayout);


    QVBoxLayout *mainLayout = new QVBoxLayout;    
    mainLayout->addLayout(edgesLayout);
    mainLayout->addLayout(vertexsLayout);
    mainLayout->addLayout(changeTableLayout);
    mainLayout->addLayout(tableLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(logGroup);
    setLayout(mainLayout);

    setWindowTitle(name_);
    setGeometry(200, 200, 500, 500);
}

void EnterDialog::sendData()
{
    if (data_ != 0 && data_->validate()) {
        emit finishEnterData(data_);
        close();
    } else {
        log_label_->setText("Ошибка.");
    }
}

void EnterDialog::notice(QString mess)
{
    log_label_->setText(mess);
}

