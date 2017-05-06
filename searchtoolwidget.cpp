#include "searchtoolwidget.h"

SearchToolWidget::SearchToolWidget(QWidget *parent) : QGroupBox(parent)
{
    setTitle("Search BFS and DFS");

    alg_selector_ = new QComboBox();
    alg_selector_->insertItem(0, "BFS");
    alg_selector_->insertItem(1, "DFS");
    start_button_ = new QPushButton("Старт");
    prev_button_ = new QPushButton("Пред.");
    next_button_ = new QPushButton("След.");;
    start_input_ = new QLineEdit();
    total_step_ = new QLabel("N");
    cur_step_ = new QSpinBox();

    QLabel *selectLabel = new QLabel("Выбрать алгоритм: ");

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(selectLabel, 0, 0);
    layout->addWidget(alg_selector_, 0, 2, 1, 3);
    layout->addWidget(start_button_, 1, 0);
    layout->addWidget(prev_button_, 2, 0);
    layout->addWidget(cur_step_, 2, 1);
    layout->addWidget(total_step_, 2, 2);
    layout->addWidget(next_button_, 2, 3);

    setLayout(layout);
    setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    setMinimumWidth(300);
}
