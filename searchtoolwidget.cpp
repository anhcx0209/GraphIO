#include "searchtoolwidget.h"

SearchToolWidget::SearchToolWidget(CoreGraph *graph, QWidget *parent) : QGroupBox(parent)
{
    graph_ = graph;    
    setTitle("Search BFS and DFS");

    // Step
    max_step_ = 0;
    cur_step_ = 0;
    start_vertex_ = 0;
    mode_ = BFS;

    // Selector: BFS or DFS
    alg_selector_ = new QComboBox();
    alg_selector_->insertItem(0, "BFS");
    alg_selector_->insertItem(1, "DFS");

    connect(alg_selector_, SIGNAL(currentIndexChanged(int)), this, SLOT(changeMode(int)));

    // Start button
    start_button_ = new QPushButton("Старт");
    connect(start_button_, SIGNAL(clicked()), this, SLOT(search()));

    // Previous step button
    prev_button_ = new QPushButton("Пред.");
    connect(prev_button_, SIGNAL(clicked()), this, SLOT(previouStep()));

    // Next step button
    next_button_ = new QPushButton("След.");
    connect(next_button_, SIGNAL(clicked()), this, SLOT(nextStep()));

    // Start selector
    start_input_ = new QLineEdit();

    max_step_label_ = new QLabel("");

    cur_step_spin_ = new QSpinBox();
    connect(cur_step_spin_, SIGNAL(valueChanged(int)), this, SLOT(goToStep(int)));

    QLabel *selectLabel = new QLabel("Выбрать алгоритм: ");
    QLabel *startLabel = new QLabel("Начальная вершина: ");

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(selectLabel, 0, 0);
    layout->addWidget(alg_selector_, 0, 1, 1, 3);
    layout->addWidget(startLabel, 1, 0);
    layout->addWidget(start_input_, 1, 1, 1, 3);
    layout->addWidget(start_button_, 2, 0);
    layout->addWidget(prev_button_, 3, 0);
    layout->addWidget(cur_step_spin_, 3, 1);
    layout->addWidget(max_step_label_, 3, 2);
    layout->addWidget(next_button_, 3, 3);

    setLayout(layout);
    setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
}

int SearchToolWidget::bfs(int i, CoreVertex *start)
{
    list_steps_.clear();
    graph_->resetFlag();    
    int step = 0;

    QQueue<CoreVertex *> queue;
    queue.enqueue(start);   
    start->setFlag(true);
    step++;

    CoreVertex *u = 0;
    while (!queue.isEmpty() && step < i) {
        u = queue.dequeue();

        foreach (CoreVertex *v, graph_->vertexs()) {
            CoreEdge *e = graph_->edgeBetween(u, v);
            if (e != 0 && v->flag() == false) {
                v->setFlag(true);
                e->setFlag(true);
                queue.enqueue(v);
                step++;
                if (step == i) return step;
            }
        }
    }
    return step;
}

int SearchToolWidget::dfs(int i, CoreVertex *start)
{
    list_steps_.clear();
    graph_->resetFlag();
    int step = 0;

    QStack<CoreVertex *> stack;
    stack.push(start);
    start->setFlag(true);
    step++;

    CoreVertex *u = 0;
    while (!stack.isEmpty() && step < i) {
        u = stack.pop();

        foreach (CoreVertex *v, graph_->vertexs()) {
            CoreEdge *e = graph_->edgeBetween(u, v);
            if (e != 0 && v->flag() == false) {
                stack.push(u);
                e->setFlag(true);
                v->setFlag(true);
                stack.push(v);
                step++;
                if (step == i) return step;
            }
        }

    }
    return step;
}

void SearchToolWidget::changeMode(int i)
{
    mode_ = (ALGORITHM)i;
}

void SearchToolWidget::search()
{
    QString id = start_input_->text();
    start_vertex_ = graph_->findVertex(id);

    if (mode_ == BFS && start_vertex_) {
        max_step_ = bfs(9000, start_vertex_);
        max_step_label_->setText(QString::number(max_step_));

        cur_step_ = 1;
        bfs(cur_step_, start_vertex_);
        cur_step_spin_->setValue(cur_step_);
        cur_step_spin_->setRange(1, max_step_);

        emit graphChanged();
    }

    if (mode_ == DFS && start_vertex_) {
        max_step_ = dfs(1000, start_vertex_);
        max_step_label_->setText(QString::number(max_step_));

        cur_step_ = 1;
        bfs(cur_step_, start_vertex_);
        cur_step_spin_->setValue(cur_step_);
        cur_step_spin_->setRange(1, max_step_);
        emit graphChanged();
    }
}

void SearchToolWidget::nextStep()
{
    goToStep(cur_step_+1);
}

void SearchToolWidget::previouStep()
{
    goToStep(cur_step_-1);
}

void SearchToolWidget::goToStep(int i)
{
    if (i <= max_step_ && i > 0) {
        cur_step_ = i;

        if (mode_ == BFS)
            bfs(cur_step_, start_vertex_);
        else
            dfs(cur_step_, start_vertex_);

        cur_step_spin_->setValue(cur_step_);
        emit graphChanged();
    }
}
