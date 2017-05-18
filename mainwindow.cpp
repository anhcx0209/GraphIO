#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenu();
    createToolbars();

    scene_ = new GraphScene(this); // init scenen for reading from file

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    setWindowTitle(tr("GraphIO"));
    setWindowIcon(QIcon(":/icons/app_icon.png"));
    setUnifiedTitleAndToolBarOnMac(true);
    menuBar()->setNativeMenuBar(false);
}


MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    new_visual_action_ = new QAction(tr("С экрана..."));
    new_visual_action_->setShortcut(tr("Ctrl+N"));
    connect(new_visual_action_, SIGNAL(triggered()), this, SLOT(startNewVisual()));

    new_adjmat_action_ = new QAction(tr("С матрицы смежности..."));
    connect(new_adjmat_action_, SIGNAL(triggered()), this, SLOT(startNewAdjMat()));

    new_incmat_action_ = new QAction(tr("С матрицы инцидентности..."));
    connect(new_incmat_action_, SIGNAL(triggered()), this, SLOT(startNewIncMat()));

    new_wmat_action_ = new QAction(tr("С матрицы весов..."));
    connect(new_wmat_action_, SIGNAL(triggered()), this, SLOT(startNewWMat()));

    new_edglist_action_ = new QAction(tr("С списки ребер..."));
    connect(new_edglist_action_, SIGNAL(triggered()), this, SLOT(startNewEdgList()));

    new_structadj_action_ = new QAction(tr("С структуры смежности..."));
    connect(new_structadj_action_, SIGNAL(triggered()), this, SLOT(startNewStructAdj()));


    open_action_ = new QAction(tr("Октрыть..."), this);
    open_action_->setShortcut(tr("Ctrl+O"));
    connect(open_action_, SIGNAL(triggered()), this, SLOT(openGraph()));

    save_action_ = new QAction(tr("Сохранить..."), this);
    save_action_->setShortcut(tr("Ctrl+S"));
    connect(save_action_, SIGNAL(triggered()), this, SLOT(saveGraph()));

    exit_action_ = new QAction(tr("Выход"), this);
    connect(exit_action_, SIGNAL(triggered()), this, SLOT(close()));

    about_action_ = new QAction(tr("О предложении"), this);
    connect(about_action_, SIGNAL(triggered()), this, SLOT(about()));

    help_action_ = new QAction(tr("Справка"), this);
    connect(help_action_, SIGNAL(triggered()), this, SLOT(openHelp()));

    delete_action_ = new QAction(QIcon(":/icons/delete.png"), tr("Delete"), this);
    delete_action_->setShortcut(tr("Delete"));

    // #demo action
    demo_action_1_ = new QAction(tr("Пример 1"), this);
    connect(demo_action_1_, SIGNAL(triggered()), this, SLOT(openDemo1()));

    demo_action_2_ = new QAction(tr("Пример 2"), this);
    connect(demo_action_2_, SIGNAL(triggered()), this, SLOT(openDemo2()));
}

void MainWindow::createMenu()
{
    file_menu_ = menuBar()->addMenu(tr("Файл"));
    new_menu_ = file_menu_->addMenu(tr("Новый граф"));
    new_menu_->addAction(new_visual_action_);
    new_menu_->addAction(new_adjmat_action_);
    new_menu_->addAction(new_incmat_action_);
    new_menu_->addAction(new_wmat_action_);
    new_menu_->addAction(new_edglist_action_);
    new_menu_->addAction(new_structadj_action_);

    file_menu_->addAction(open_action_);
    file_menu_->addAction(save_action_);
    file_menu_->addAction(exit_action_);

    demo_menu_ = menuBar()->addMenu(tr("Примеры"));
    demo_menu_->addAction(demo_action_1_);
    demo_menu_->addAction(demo_action_2_);

    help_menu_ = menuBar()->addMenu(tr("Помощь"));
    help_menu_->addAction(about_action_);
    help_menu_->addAction(help_action_);

}

void MainWindow::createToolbars()
{
    view_combobox_ = new QComboBox;
    view_combobox_->addItem(tr("Визуальный граф"));
    view_combobox_->addItem(tr("Матрица смежности"));
    view_combobox_->addItem(tr("Матрица инцидентности"));
    view_combobox_->addItem(tr("Матрица весов графа"));
    view_combobox_->addItem(tr("Список ребер графа"));
    view_combobox_->addItem(tr("Структура смежности графа"));

    connect(view_combobox_, SIGNAL(currentIndexChanged(int)), this, SLOT(changePage(int)));

    view_toolbar_ = addToolBar(tr("View"));
    view_toolbar_->addWidget(view_combobox_);

    QToolButton *pointButton = new QToolButton;
    pointButton->setCheckable(true);
    pointButton->setChecked(false);
    pointButton->setIcon(QIcon(":/icons/point.png"));

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/icons/pointer.png"));

    QToolButton *lineButton = new QToolButton;
    lineButton->setCheckable(true);
    lineButton->setChecked(false);
    lineButton->setIcon(QIcon(":/icons/linepointer.png"));    

    visual_graph_group_ = new QButtonGroup(this);
    visual_graph_group_->addButton(pointButton, int(GraphScene::InsertItem));
    visual_graph_group_->addButton(pointerButton, int(GraphScene::MoveItem));
    visual_graph_group_->addButton(lineButton, int(GraphScene::InsertLine));

    connect(visual_graph_group_, SIGNAL(buttonClicked(int)),
            this, SLOT(visualGraphGroupClicked(int)));

    graph_toolbar_ = addToolBar(tr("Graph"));
    graph_toolbar_->addWidget(pointButton);
    graph_toolbar_->addWidget(pointerButton);
    graph_toolbar_->addWidget(lineButton);
    graph_toolbar_->addAction(delete_action_);

    view_toolbar_->setEnabled(false);
    graph_toolbar_->setEnabled(false);
}

void MainWindow::setupPageWidget(CoreGraph *g)
{
    // Visual graph    
    graph_ = g;
    scene_->setSceneRect(QRectF(0, 0, 5000, 5000));    
    view_ = new QGraphicsView(scene_);
    scene_->setGraph(g);
    // Connect to delete action
    connect(delete_action_, SIGNAL(triggered()), scene_, SLOT(deleteItem()));

    // Adjacency matrix
    adjmat_view_ = new QTableView;
    adjmat_view_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    adjmat_view_->setModel(new AdjMat(graph_));
    // List of edges
    edglist_view_ = new QTableView;
    edglist_view_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    edglist_view_->setModel(new EdgList(graph_));
    // Inc mat
    incmat_view_ = new QTableView;
    incmat_view_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    incmat_view_->setModel(new IncMat(graph_));
    // Struct adj
    structadj_view_ = new QTableView;
    structadj_view_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    structadj_view_->setModel(new StructAdj(graph_));
    // W mat
    wmat_view_ = new QTableView;
    wmat_view_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    wmat_view_->setModel(new WMat(graph_));

    pages_widget_ = new QStackedWidget;
    pages_widget_->addWidget(view_);
    pages_widget_->addWidget(adjmat_view_);
    pages_widget_->addWidget(incmat_view_);
    pages_widget_->addWidget(wmat_view_);
    pages_widget_->addWidget(edglist_view_);
    pages_widget_->addWidget(structadj_view_);
}

void MainWindow::changePage(int i)
{
    adjmat_view_->setModel(new AdjMat(graph_));
    edglist_view_->setModel(new EdgList(graph_));
    incmat_view_->setModel(new IncMat(graph_));
    structadj_view_->setModel(new StructAdj(graph_));
    wmat_view_->setModel(new WMat(graph_));
    pages_widget_->setCurrentIndex(i);
}

void MainWindow::visualGraphGroupClicked(int)
{
    scene_->setMode(GraphScene::Mode(visual_graph_group_->checkedId()));
}

void MainWindow::start(CoreGraph *newGraph)
{
    // get up page widget
    setupPageWidget(newGraph);
    // set up search tool box
    search_widget_ = new SearchToolWidget(graph_);
    connect(search_widget_, SIGNAL(graphChanged()), view_->viewport(), SLOT(update()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(pages_widget_, 0, 0, 2, 1);
    layout->addWidget(search_widget_, 0, 1);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    graph_toolbar_->setEnabled(true);
    view_toolbar_->setEnabled(true);
}

void MainWindow::startNewVisual()
{
    CoreGraph *g = new CoreGraph();
    scene_->clear();
    scene_->reset();
    start(g);
}

void MainWindow::startNewAdjMat()
{
    NewAdjMat *dialog = new NewAdjMat();
    connect(dialog, SIGNAL(finishEnterData(CoreGraph*)), this, SLOT(gotGraphFromDialog(CoreGraph*)));
    dialog->exec();
}

void MainWindow::startNewIncMat()
{
    NewIncMat *dialog = new NewIncMat();
    connect(dialog, SIGNAL(finishEnterData(CoreGraph*)), this, SLOT(gotGraphFromDialog(CoreGraph*)));
    dialog->exec();
}

void MainWindow::startNewWMat()
{
    NewWMat *dialog = new NewWMat();
    connect(dialog, SIGNAL(finishEnterData(CoreGraph*)), this, SLOT(gotGraphFromDialog(CoreGraph*)));
    dialog->exec();
}

void MainWindow::startNewEdgList()
{
    NewEdgList *dialog = new NewEdgList();
    connect(dialog, SIGNAL(finishEnterData(CoreGraph*)), this, SLOT(gotGraphFromDialog(CoreGraph*)));
    dialog->exec();
}

void MainWindow::startNewStructAdj()
{
    NewStructAdj *dialog = new NewStructAdj();
    connect(dialog, SIGNAL(finishEnterData(CoreGraph*)), this, SLOT(gotGraphFromDialog(CoreGraph*)));
    dialog->exec();
}

void MainWindow::openGraph()
{    
    QString file;
    file = QFileDialog::getOpenFileName(this,
                                        tr("Open file"),
                                        tr("/Users/anhcx/8/IO/file"),
                                        tr("Graph data file (*.graph)"));
    if (scene_->readFrom(file)) {
        graph_ = scene_->graph();
        start(graph_);
    }
}

void MainWindow::saveGraph()
{
    QString saveFileName;
    saveFileName = QFileDialog::getSaveFileName(this, tr("Save to file"), tr("/Users/anhcx/8/IO/file"), tr("Graph data file (*.graph)"));
    scene_->saveTo(saveFileName);
}

void MainWindow::openHelp()
{
    HelpBrowser::showPage("index.html");
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("GraphIO 3.0"),
                       tr("Предложение <b>Graph IO</b> версия "
                          "3.0 для отображения граф. Автор: AnhCx"));
}

void MainWindow::openDemo1()
{
    if (scene_->readFrom(":/demo/demo1.graph")) {
        graph_ = scene_->graph();
        start(graph_);
    }
}

void MainWindow::openDemo2()
{
    if (scene_->readFrom(":/demo/demo2.graph")) {
        graph_ = scene_->graph();
        start(graph_);
    }
}

void MainWindow::gotGraphFromDialog(CoreGraph *g)
{    
    startNewVisual();
    graph_ = g;
    scene_->drawGraph(g);
    search_widget_->setGraph(g);
}
