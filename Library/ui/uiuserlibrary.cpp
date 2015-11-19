#include "uiuserlibrary.h"
#include "ui/uiusercenter.h"
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QMenuBar>

UIUserLibrary::UIUserLibrary(QWidget *parent) :
    QMainWindow(parent)
{
    this->initUI();
    this->createConnections();
}

UIUserLibrary::~UIUserLibrary()
{

}

void UIUserLibrary::initUI()
{
    this->setWindowIcon(QIcon(":/005.jpg"));
    this->setWindowTitle("图书管理系统[*]");
    this->setWindowState(Qt::WindowMaximized);

    this->mainWidget = new UIUserCenter();
    this->setCentralWidget(mainWidget);

    this->createActions();
    this->createMenus();
    this->createToolBars();
    this->saveAction->setEnabled(false);
}

void UIUserLibrary::createMenus()
{
    this->fileMenu = menuBar()->addMenu(tr("文件"));
    this->fileMenu->addAction(this->saveAction);
    this->fileMenu->addAction(this->exitAction);

    this->editMenu = menuBar()->addMenu(tr("编辑"));

    this->aboutMenu = menuBar()->addMenu(tr("帮助"));
    this->aboutMenu->addAction(this->helpAction);
}

void UIUserLibrary::createActions()
{
    this->saveAction = new QAction(QIcon(":/003.png"), tr("Save"), this);
    this->saveAction->setShortcut(tr("Ctrl+S"));
    this->saveAction->setStatusTip(tr("保存"));

    this->exitAction = new QAction(QIcon(":/004.png"), tr("Exit"), this);
    this->exitAction->setShortcut(tr("Ctrl+Q"));
    this->exitAction->setStatusTip(tr("退出"));

    this->helpAction = new QAction(QIcon(""), tr("About"), this);
}

void UIUserLibrary::createToolBars()
{
    this->fileToolBar = addToolBar(tr("文件"));
    this->fileToolBar->addAction(this->exitAction);
    this->fileToolBar->addAction(this->saveAction);
    this->fileToolBar->addSeparator();
}

void UIUserLibrary::createConnections()
{
    QObject::connect(this->saveAction, SIGNAL(triggered()), this, SLOT(slotSaveAction()));
    QObject::connect(this->exitAction, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(this->helpAction, SIGNAL(triggered()), this, SLOT(slotAboutLibrary()));
}

void UIUserLibrary::slotSaveAction()
{

}

void UIUserLibrary::slotAboutLibrary()
{

}
