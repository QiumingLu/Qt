#include "uimemberlevel.h"
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <set>
#include "core/systype.h"
#include "model/memberlevel.h"
#include "dao/daomemberlevel.h"
#include "ui/addmemberlevel.h"

UIMemberLevel::UIMemberLevel(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

UIMemberLevel::~UIMemberLevel()
{

}

void UIMemberLevel::initUI()
{
    this->memberLevelTable = new QTableWidget();
    this->deleteBtn = new QPushButton("删除");
    this->addBtn = new QPushButton("添加");
    this->closeBtn = new QPushButton("取消");
    this->btnLayout = new QHBoxLayout();
    this->mainLayout = new QVBoxLayout();

    this->btnLayout->addStretch();
    this->btnLayout->addWidget(deleteBtn);
    this->btnLayout->addWidget(addBtn);
    this->btnLayout->addWidget(closeBtn);

    this->mainLayout->addWidget(memberLevelTable);
    this->mainLayout->addLayout(btnLayout);
    this->setLayout(mainLayout);
}

void UIMemberLevel::createConnections()
{
    QObject::connect(this->closeBtn, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->addBtn, SIGNAL(clicked()), this, SLOT(slotAdd()));
    QObject::connect(this->deleteBtn, SIGNAL(clicked()), this, SLOT(slotDelete()));
}

void UIMemberLevel::initTable()
{
    this->memberList = SYSTYPE->getAllMemberLevel();
    QStringList tableColumnName;
    tableColumnName.append("级别名");
    tableColumnName.append("最长的借书时间");
    tableColumnName.append("一次最多可借的书的数目");
    tableColumnName.append("会员费");
    tableColumnName.append("编辑");

    this->memberLevelTable->setColumnCount(tableColumnName.size());
    this->memberLevelTable->setRowCount(memberList.size());
    this->memberLevelTable->setHorizontalHeaderLabels(tableColumnName);

    for (int i = 0; i < memberList.size(); ++i)
    {
        memberLevelTable->setItem(i, 0, new QTableWidgetItem(memberList.at(i)->getLevelName()));
        memberLevelTable->setItem(i, 1, new QTableWidgetItem(QString::number(memberList.at(i)->getDays())));
        memberLevelTable->setItem(i, 2, new QTableWidgetItem(QString::number(memberList.at(i)->getNumbers())));
        memberLevelTable->setItem(i, 3, new QTableWidgetItem(QString::number(memberList.at(i)->getFee())));

        QPushButton *editBtn = new QPushButton("编辑");
        editBtn->setEnabled(true);
        memberLevelTable->setCellWidget(i, 4, editBtn);
        QObject::connect(editBtn, SIGNAL(clicked()), this, SLOT(slotEdit()));
    }
}

void UIMemberLevel::slotAdd()
{
    this->addMemberLevel = new AddMemberLevel();
    this->addMemberLevel->show();
}

void UIMemberLevel::slotEdit()
{
    this->memberLevelTable->setFocus();
    int row = -1;
    row = this->memberLevelTable->currentRow();
    if (row >= 0)
    {
        int ret = QMessageBox::information(this, tr("information"), tr("启动编辑？"), "确定", "取消");
        if (ret == 1)
            return ;
        this->addMemberLevel = new AddMemberLevel();
        MemberLevel *memberLevel = memberList.at(row);
        if (this->addMemberLevel->initLevelInfo(memberLevel))
            this->addMemberLevel->show();
        else
            return ;
    }
}

void UIMemberLevel::slotDelete()
{
    QList<QTableWidgetItem*> deleteList = this->memberLevelTable->selectedItems();
    if (deleteList.size() == 0)
    {
        QMessageBox::information(this, tr("提醒"), tr("请选择要删除的行"));
        return;
    }

    int ret = QMessageBox::warning(this, tr("警告"), tr("确定要删除所选中的行？会级联删除相对应的用户"), "确定", "取消");
    if (ret == 1)
        return;

    std::set<int> del_row;              //记录要删除的行号，用set防止重复
    for (int i = 0; i < deleteList.size(); ++i)       //删除选中的项
    {
        QTableWidgetItem *selectItem = deleteList.at(i);   //指向选中的item的指针
        if (selectItem)
        {
            int row = this->memberLevelTable->row(selectItem);    //获取行号
            del_row.insert(row);
        }
    }

    std::vector<int> del_list;
    for (std::set<int>::iterator it = del_row.begin(); it != del_row.end(); ++it)
    {
        del_list.push_back(*it);
    }

    for (int i = del_list.size() - 1; i >= 0; --i)
    {
        MemberLevel *memberLevel = memberList.at(del_list.at(i));
        QVector<Readers*> readerVec = SYSTYPE->getReaderByLevel(memberLevel->getLevelId());
        if (readerVec.size() > 0)
        {
            QMessageBox::warning(this, tr("警告"), "第" +
                                 QString::number(del_list.at(i) + 1) + "的类型有相应的用户！，请先删除相应用户", "确定");
            break;
        }
        DaoMemberLevel daoMemberLevel;
        bool ret = daoMemberLevel.Delete(memberLevel);
        if (ret)
        {
            SYSTYPE->deleteMemberLevel(del_list.at(i));
            this->memberLevelTable->removeRow(del_list.at(i));
            QMessageBox::warning(this, tr("提醒"), "第" + QString::number(del_list.at(i) + 1) + "删除成功！", "确定");
        }
        else
        {
            QMessageBox::warning(this, tr("警告"), "第" + QString::number(del_list.at(i) + 1) + "删除失败！", "确定");
        }
    }
}
