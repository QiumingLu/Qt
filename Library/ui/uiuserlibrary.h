#ifndef UIUSERLIBRARY_H
#define UIUSERLIBRARY_H

#include <QMainWindow>

class UIUserCenter;
class UIUserLibrary : public QMainWindow
{
    Q_OBJECT

public:
    explicit UIUserLibrary(QWidget *parent = 0);
    ~UIUserLibrary();

private:
    void initUI();
    void createMenus();
    void createActions();
    void createToolBars();
    void createConnections();

private:
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *aboutMenu;

    QAction *saveAction;
    QAction *exitAction;
    QAction *helpAction;

    QToolBar *fileToolBar;

    UIUserCenter *mainWidget;

private slots:
    void slotSaveAction();
    void slotAboutLibrary();
};

#endif // UIUSERLIBRARY_H
