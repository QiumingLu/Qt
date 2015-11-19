#ifndef UIBOOKMANAGE_H
#define UIBOOKMANAGE_H

#include <QMainWindow>
#include "core/sysinclude.h"

class QTreeWidgetItem;
class QLabel;
class QSplitter;
class QGridLayout;
class UIBookManageTree;
class UIBookInformationManage;
class UIBookEditManage;
class UIBookCateGory;

class UIBookManage : public QMainWindow
{
    Q_OBJECT

public:
    UIBookManage(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~UIBookManage();

private:
    void initUI();
    void createConnections();

private:
    QLabel *banner;
    QSplitter *mainSplitter;
    QGridLayout *mainLayout;
    QWidget *mainWidget;

    UIBookManageTree *leftTree;
    UIBookInformationManage *bookInfomationManage;
    UIBookEditManage *bookEditManage;
    UIBookInformationManage *editBookManage;
    UIBookCateGory *uiBookCateGory;

public slots:
    void slotTreeItemClick(QTreeWidgetItem*, int);
};

#endif // UIBOOKMANAGE_H
