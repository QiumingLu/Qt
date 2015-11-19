#include "uibookmanagetree.h"
#include "core/sysinclude.h"
#include "core/systype.h"
#include "model/bookcategory.h"
#include "model/books.h"

UIBookManageTree::UIBookManageTree(QWidget *parent):
    QTreeWidget(parent)
{
    this->initBookManageTree();
    this->setHeaderHidden(true);
}

UIBookManageTree::~UIBookManageTree()
{

}

/*
 * @brief
 * 创建树item的函数
 * @name
 * makeTreeWidgetItem
 * @arg
 * itemList ：@class QStringList 树的叶子列表
 * root     ：@class QTreeWidgetItem * 根节点
 * data     ：@class QList<int> 叶子节点保存的数据
 * @return
 * void
 * @author
 * @test
 */
void UIBookManageTree::makeTreeWidgetItem(QStringList itemList,
                                          QTreeWidgetItem *root, QList<int> data)
{
    for (int i = 0; i < itemList.count(); ++i)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, itemList.at(i));
        if (data.count() > i)
            item->setData(0, Qt::UserRole, data.at(i));
        root->addChild(item);
    }
}

void UIBookManageTree::initBookManageTree()
{
    this->setColumnCount(1);
    QList<int> itemData;      //保存对应节点的id，作为treeitem的userdata

    /*添加根节点*/
    QStringList root1qslist;
    root1qslist.append("查看书籍的信息");
    root1qslist.append("编辑书籍的信息");
    root1qslist.append("书籍字典管理");

    QList<QTreeWidgetItem*> rootList;
    foreach (QString rootName, root1qslist) {
        QTreeWidgetItem *root = new QTreeWidgetItem(this);
        root->setText(0, rootName);
        rootList.append(root);
    }

    /*添加子节点*/
    QStringList list1;
    QList<BookCateGory*> bookCateGoryList = SYSTYPE->getAllBookCateGory();

    foreach (BookCateGory *pBookCateGory, bookCateGoryList) {
        list1.append(pBookCateGory->getCateGoryName());
        itemData.append(pBookCateGory->getCateGoryId());
    }

    this->makeTreeWidgetItem(list1, rootList.at(0), itemData);
    itemData.clear();

    /*添加子节点*/
    QStringList list2;
    list2.append("添加新书");
    list2.append("编辑旧书");
    this->makeTreeWidgetItem(list2, rootList.at(1), itemData);
    itemData.clear();

    /*添加子节点*/
    QStringList list3;
    list3.append("查看图书类别字典表");
    this->makeTreeWidgetItem(list3, rootList.at(2), itemData);
    itemData.clear();

    this->expandAll();
}
