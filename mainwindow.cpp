#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenu();
    createToolbars();
    setupPageWidget();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(pages_widget_);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
    setWindowTitle(tr("GraphIO"));
    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    new_action_ = new QAction(tr("New"), this);
    new_action_->setShortcut(tr("Ctrl+N"));
    connect(new_action_, SIGNAL(triggered()), this, SLOT(newGraph()));

    open_action_ = new QAction(tr("Open"), this);
    open_action_->setShortcut(tr("Ctrl+O"));
    connect(open_action_, SIGNAL(triggered()), this, SLOT(openGraph()));

    save_action_ = new QAction(tr("Save"), this);
    save_action_->setShortcut(tr("Ctrl+S"));
    connect(save_action_, SIGNAL(triggered()), this, SLOT(saveGraph()));

    exit_action_ = new QAction(tr("Exit"), this);
    connect(exit_action_, SIGNAL(triggered()), this, SLOT(close()));

    about_action_ = new QAction(tr("About"), this);
    connect(about_action_, SIGNAL(triggered()), this, SLOT(about()));

    help_action_ = new QAction(tr("Help"), this);
    //connect(exit_action_, SIGNAL(triggered()), this, SLOT(close()));

    delete_action_ = new QAction(QIcon(":/icons/delete.png"), tr("Delete"), this);
    delete_action_->setShortcut(tr("Delete"));
}

void MainWindow::createMenu()
{
    file_menu_ = menuBar()->addMenu(tr("File"));
    file_menu_->addAction(new_action_);
    file_menu_->addAction(open_action_);
    file_menu_->addAction(save_action_);
    file_menu_->addAction(exit_action_);

    help_menu_ = menuBar()->addMenu(tr("Help"));
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
}

void MainWindow::setupPageWidget()
{
    // Visual graph
    graph_ = new CoreGraph();
    scene_ = new GraphScene(this);
    scene_->setSceneRect(QRectF(0, 0, 5000, 5000));
    view_ = new QGraphicsView(scene_);
    scene_->setGraph(graph_);
    // Connect to delete action
    connect(delete_action_, SIGNAL(triggered()), scene_, SLOT(deleteItem()));

    // Adjacency matrix
    adjmat_view_ = new QTableView;
    adjmat_view_->setModel(new AdjMat(graph_));
    // List of edges
    edglist_view_ = new QTableView;
    edglist_view_->setModel(new EdgList(graph_));
    // IN
    incmat_view_ = new QTableView;
    incmat_view_->setModel(new IncMat(graph_));
    // struct adj
    structadj_view_ = new QTableView;
    structadj_view_->setModel(new StructAdj(graph_));
    // w mat
    wmat_view_ = new QTableView;
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

void MainWindow::newGraph()
{
    EnterDialog dialog;
    dialog.exec();
}

void MainWindow::openGraph()
{
    qDebug() << "open graph...";
}

void MainWindow::saveGraph()
{
    qDebug() << "save graph...";
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("GraphIO 2.0"),
                       tr("The <b>Graph creator</b> example shows "
                          "use of the graphics framework."));
}
