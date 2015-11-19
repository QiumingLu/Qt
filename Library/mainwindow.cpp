#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/uibookmanage.h"
#include "ui/uiusermanage.h"
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUI();
    this->createConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    this->setWindowTitle(tr("图书管理系统[*]"));
    this->setWindowIcon(QIcon(":/005.jpg"));
    this->setWindowState(Qt::WindowMaximized);
    this->pTabWidget = new QTabWidget();
    this->pTabWidget->setTabPosition(QTabWidget::North);

    this->pBookManage = new UIBookManage();
    this->pUserManage = new UIUserManage();
    this->pTabWidget->addTab(pBookManage, tr("图书管理模块"));
    this->pTabWidget->addTab(pUserManage, tr("图书馆人员管理模块"));

    this->setCentralWidget(pTabWidget);

    this->createActions();
    this->createMenus();
    this->createToolBars();
    this->saveAction->setEnabled(false);
}

void MainWindow::createMenus()
{
    this->fileMenu = menuBar()->addMenu(tr("文件"));
    this->fileMenu->addAction(this->saveAction);
    this->fileMenu->addAction(this->exitAction);

    this->editMenu = menuBar()->addMenu(tr("编辑"));

    this->aboutMenu = menuBar()->addMenu(tr("帮助"));
    this->aboutMenu->addAction(this->helpAction);
}

void MainWindow::createActions()
{
    this->saveAction = new QAction(QIcon(":/003.png"), tr("Save"), this);
    this->saveAction->setShortcut(tr("Ctrl+S"));

    this->exitAction = new QAction(QIcon(":/004.png"), tr("Exit"), this);
    this->exitAction->setShortcut(tr("Ctrl+Q"));

    this->helpAction = new QAction(QIcon(""), tr("About"), this);
}

void MainWindow::createToolBars()
{
    this->fileToolBar = addToolBar(tr("文件"));
    this->fileToolBar->addAction(this->saveAction);
    this->fileToolBar->addAction(this->exitAction);
    this->fileToolBar->addSeparator();
}

void MainWindow::createConnections()
{
    QObject::connect(this->exitAction, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(this->helpAction, SIGNAL(triggered()), this, SLOT(slotAboutLibrary()));
}

void MainWindow::slotAboutLibrary()
{

}
