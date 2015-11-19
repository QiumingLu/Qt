#include "uiuserinformationmanage.h"
#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateTime>
#include <QMessageBox>
#include <set>
#include "core/systype.h"
#include "model/managers.h"
#include "core/sysinclude.h"
#include "model/sysenviroment.h"
#include "dao/daouser.h"
#include "dao/daomanagers.h"
#include "ui/uiadmin.h"
#include "ui/addmanagerbtn.h"
#include "ui/editmanagerbtn.h"

UIUserInformationManage::UIUserInformationManage(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConections();
}

UIUserInformationManage::~UIUserInformationManage()
{
    SAFE_DELETE(addManager);
    SAFE_DELETE(editManager);
    SAFE_DELETE(deleteBtn);
    SAFE_DELETE(addBtn);
    SAFE_DELETE(closeBtn);
    SAFE_DELETE(btnLayout);
    SAFE_DELETE(managerTable);
    SAFE_DELETE(mainLayout);
}

void UIUserInformationManage::initUI()
{
    this->managerTable = new QTableWidget();
    this->managerTable->setWindowTitle("人员管理列表");
    this->managerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->managerTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->deleteBtn = new QPushButton("删除");
    this->addBtn = new QPushButton("添加");
    this->closeBtn = new QPushButton("取消");

    this->btnLayout = new QHBoxLayout();
    this->btnLayout->addStretch();
    this->btnLayout->addWidget(this->deleteBtn);
    this->btnLayout->addWidget(this->addBtn);
    this->btnLayout->addWidget(this->closeBtn);
    this->deleteBtn->setDisabled(true);
    this->addBtn->setDisabled(true);

    this->mainLayout = new QVBoxLayout();
    this->mainLayout->addWidget(this->managerTable);
    this->mainLayout->addLayout(this->btnLayout);
    this->setLayout(this->mainLayout);

    if (SysEnviroment::getInstance()->getUser()->getUserType() == sysinclude::superAdmin)
    {
        this->deleteBtn->setEnabled(true);
        this->addBtn->setEnabled(true);
    }
}

void UIUserInformationManage::createConections()
{
    QObject::connect(this->deleteBtn, SIGNAL(clicked()), this, SLOT(slotDelete()));
    QObject::connect(this->closeBtn, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->addBtn, SIGNAL(clicked()), this, SLOT(slotAdd()));
}

void UIUserInformationManage::initManagerTable(int userType)
{   
    this->managerVec.clear();
    for (int i = 0; i < SYSTYPE->getAllManagers().size(); ++i)
    {
        if (SYSTYPE->getAllManagers().at(i)->getUserType() == userType)
        {
            this->managerVec.append(SYSTYPE->getAllManagers().at(i));
        }
    }

    if (userType == sysinclude::superAdmin)
    {
        this->deleteBtn->setEnabled(true);
    }

    QStringList tableColumnName;
    tableColumnName.append("Library ID");
    tableColumnName.append("用户姓名");
    tableColumnName.append("姓别");
    tableColumnName.append("出生日期");
    tableColumnName.append("电话");
    tableColumnName.append("手机");
    tableColumnName.append("邮箱");
    tableColumnName.append("加入时间");
    tableColumnName.append("备注");
    tableColumnName.append("详细信息");
    tableColumnName.append("编辑");

    this->managerTable->setColumnCount(tableColumnName.size());
    this->managerTable->setRowCount(managerVec.size());
    this->managerTable->setHorizontalHeaderLabels(tableColumnName);

    for (int i = 0; i < managerTable->rowCount(); ++i)
    {
        this->managerTable->setItem(i, 0, new QTableWidgetItem(managerVec.at(i)->getUserCode()));
        this->managerTable->setItem(i, 1, new QTableWidgetItem(managerVec.at(i)->getUserName()));

        if (managerVec.at(i)->getSex() == sysinclude::male)
            this->managerTable->setItem(i, 2, new QTableWidgetItem("男"));
        else if (managerVec.at(i)->getSex() == sysinclude::female)
            this->managerTable->setItem(i, 2, new QTableWidgetItem("女"));
        else
            this->managerTable->setItem(i, 2, new QTableWidgetItem("保密"));
        this->managerTable->setItem(i, 3, new QTableWidgetItem(managerVec.at(i)->getBirthDay()));
        this->managerTable->setItem(i, 4, new QTableWidgetItem(managerVec.at(i)->getPhone()));
        this->managerTable->setItem(i, 5, new QTableWidgetItem(managerVec.at(i)->getMobile()));
        this->managerTable->setItem(i, 6, new QTableWidgetItem(managerVec.at(i)->getMail()));
        this->managerTable->setItem(i, 7, new QTableWidgetItem(managerVec.at(i)->getUserCreateTime().toString("yyyy-MM-dd hh:mm:ss")));
        this->managerTable->setItem(i, 8, new QTableWidgetItem(managerVec.at(i)->getUserRemark()));

        QPushButton *buttonDetail = new QPushButton();
        buttonDetail->setText("详细信息");
        buttonDetail->setEnabled(true);

        QPushButton *buttonEdit = new QPushButton();
        buttonEdit->setText("编辑");
        buttonEdit->setEnabled(false);

        this->managerTable->setCellWidget(i, 9, buttonDetail);
        this->managerTable->setCellWidget(i, 10, buttonEdit);

        if (managerVec.at(i)->getUserID() == SysEnviroment::getInstance()->getUser()->getUserID()
                || SysEnviroment::getInstance()->getUser()->getUserType() == sysinclude::superAdmin)
        {
            buttonEdit->setEnabled(true);
        }
        QObject::connect(buttonEdit, SIGNAL(clicked()), this, SLOT(slotEdit()));
        QObject::connect(buttonDetail, SIGNAL(clicked()), this, SLOT(slotDetail()));
    }
}

void UIUserInformationManage::slotDelete()
{
    QList<QTableWidgetItem*> deleteList = this->managerTable->selectedItems();
    if (deleteList.size() == 0)
    {
        QMessageBox::information(this, tr("提醒"), tr("请选择要删除的行"));
        return;
    }

    int ret = QMessageBox::warning(this, tr("警告"), tr("确定要删除所选中的行？"), "确定", "取消");
    if (ret == 1)
        return;

    std::set<int> del_row;
    for (int i = 0; i < deleteList.size(); ++i)
    {
        QTableWidgetItem *selectItem = deleteList.at(i);
        if(selectItem)
        {
            int row = this->managerTable->row(selectItem);
            del_row.insert(row);
        }
    }

    std::vector<int> del_list;
    for (std::set<int>::iterator it = del_row.begin(); it != del_row.end(); ++it)
    {
        del_list.push_back(*it);
    }

    DaoUser daoUser;
    for (int i = del_list.size() - 1; i >= 0; i--)
    {
        Managers *manager = managerVec.at(del_list.at(i));
        User *user = SYSTYPE->getUser(manager->getUserID());
        bool ret = daoUser.Delete(user);
        if (ret)
        {
            SYSTYPE->deleteManager(manager->getUserID());
            SYSTYPE->deleteUser(user->getUserID());
            this->managerTable->removeRow(del_list.at(i));
            QMessageBox::information(this, "提醒", "第" + QString::number(del_list.at(i) + 1) + "删除成功！", "确定");
        }
        else
        {
            QMessageBox::information(this, "提醒","第" + QString::number(del_list.at(i) + 1) + "删除失败！", "确定");
        }
    }
}

void UIUserInformationManage::slotAdd()
{
    this->addManager = new AddManagerBtn();
    this->addManager->show();
}

void UIUserInformationManage::slotEdit()
{
    this->managerTable->setFocus();
    int row = -1;
    row = this->managerTable->currentRow();
    if (row < 0)
    {
        return;
    }
    this->editManager = new EditManagerBtn();
    bool ret = this->editManager->setTableText(managerVec.at(row));
    if (ret)
    {
        this->editManager->show();
    } else {
        QMessageBox::information(this, "警告", "管理员编辑出错！", "确定");
    }
}

void UIUserInformationManage::slotDetail()
{
}

