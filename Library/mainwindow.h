#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class UIBookManage;
class UIUserManage;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initUI();
    void createMenus();
    void createActions();
    void createToolBars();
    void createConnections();

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *aboutMenu;

    QAction *saveAction;
    QAction *exitAction;
    QAction *helpAction;

    QToolBar *fileToolBar;

    QTabWidget *pTabWidget;

    UIBookManage *pBookManage;
    UIUserManage *pUserManage;

private slots:
    void slotAboutLibrary();
};

#endif // MAINWINDOW_H
