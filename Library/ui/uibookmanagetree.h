#ifndef UIBOOKMANAGETREE_H
#define UIBOOKMANAGETREE_H

#include <QTreeWidget>

class UIBookManageTree : public QTreeWidget
{
    Q_OBJECT

public:
    UIBookManageTree(QWidget *parent = 0);
    ~UIBookManageTree();

private:
    void makeTreeWidgetItem(QStringList itemList, QTreeWidgetItem *root, QList<int> data);
    void initBookManageTree();

private slots:
};

#endif // UIBOOKMANAGETREE_H
