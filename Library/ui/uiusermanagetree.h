#ifndef UIUSERMANAGETREE_H
#define UIUSERMANAGETREE_H

#include <QTreeWidget>

class UIUserManageTree : public QTreeWidget
{
    Q_OBJECT

public:
    UIUserManageTree(QWidget *parent = 0);
    ~UIUserManageTree();

private:
    void makeTreeWidgetItem(QStringList itemList, QTreeWidgetItem *root, QList<int> data);
    void initUserManageTree();

private slots:
};

#endif // UIUSERMANAGETREE_H
