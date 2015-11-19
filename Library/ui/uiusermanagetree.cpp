#include "uiusermanagetree.h"
#include "core/systype.h"
#include "model/usertype.h"

UIUserManageTree::UIUserManageTree(QWidget *parent) :
    QTreeWidget(parent)
{
    this->initUserManageTree();
    this->setHeaderHidden(true);
}

UIUserManageTree::~UIUserManageTree()
{

}

/*
 * @brief
 * 创建树item的函数
 * @name
 * makeTreeWidgetItem
 * @arg
 * itemList ：@class QStringList 树的叶子列表
 * root     ：@class QTreeWidgetItem* 根节点
 * data     ：@class QList<int> 叶子节点保存的数据
 * @return
 * void
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 * @test
 */
void UIUserManageTree::makeTreeWidgetItem(QStringList itemList,
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

void UIUserManageTree::initUserManageTree()
{
    this->setColumnCount(1);
    QList<int> itemData;     //保存对应节点的id

    /*添加根节点*/
    QStringList root1qsList;
    root1qsList.append("查看人员信息");
    root1qsList.append("编辑人员信息");
    root1qsList.append("人员字典管理");

    QList<QTreeWidgetItem*> rootList;
    foreach (QString rootName, root1qsList)
    {
        QTreeWidgetItem *root = new QTreeWidgetItem(this);
        root->setText(0, rootName);
        rootList.append(root);
    }

    /*添加子节点*/
    QStringList list1;
    QList<UserType*> userTypeList = SYSTYPE->getAllUserType();

    foreach (UserType *pUserType, userTypeList) {
        list1.append(pUserType->getUserTypeName());
        itemData.append(pUserType->getUserTypeId());
    }

    this->makeTreeWidgetItem(list1, rootList.at(0), itemData);
    itemData.clear();

    /*添加子节点*/
    QStringList list2;
    list2.append("添加新用户");
    list2.append("编辑旧的人员");
    this->makeTreeWidgetItem(list2, rootList.at(1), itemData);
    itemData.clear();

    QStringList list3;
    list3.append("人员类别字典表");
    list3.append("会员等级字典表");
    this->makeTreeWidgetItem(list3, rootList.at(2), itemData);
    itemData.clear();

    this->expandAll();
}
