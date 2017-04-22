#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenu();

    QWidget *widget = new QWidget;
    //widget->setLayout(layout);
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
