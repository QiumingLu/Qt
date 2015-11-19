#include "uiusereditmanage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QMessageBox>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <set>
#include "model/sysenviroment.h"
#include "model/readers.h"
#include "ui/uiregister.h"
#include "core/systype.h"
#include "model/memberlevel.h"
#include "dao/daoreaders.h"
#include "dao/daouser.h"
#include "ui/myinfowidget.h"

UIUserEditManage::UIUserEditManage(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

UIUserEditManage::~UIUserEditManage()
{
}

void UIUserEditManage::initUI()
{
    this->readerTable = new QTableWidget();
    this->deleteBtn = new QPushButton("删除");
    this->addBtn = new QPushButton("添加");
    this->closeBtn = new QPushButton("取消");
    this->btnLayout = new QHBoxLayout();
    this->mainLayout = new QVBoxLayout();

    this->btnLayout->addStretch();
    this->btnLayout->addWidget(deleteBtn);
    this->btnLayout->addWidget(addBtn);
    this->btnLayout->addWidget(closeBtn);

    this->mainLayout->addWidget(readerTable);
    this->mainLayout->addLayout(btnLayout);
    this->setLayout(mainLayout);
}

void UIUserEditManage::initReaderTable()
{
    this->readerList = SYSTYPE->getAllReaders();

    QStringList tableColumnName;
    tableColumnName.append("Library ID");
    tableColumnName.append("用户名");
    tableColumnName.append("电话");
    tableColumnName.append("手机");
    tableColumnName.append("邮箱");
    tableColumnName.append("证件名称");
    tableColumnName.append("证件编号");
    tableColumnName.append("会员级别");
    tableColumnName.append("应交会费");
    tableColumnName.append("详细信息");
    tableColumnName.append("编辑");

    this->readerTable->setColumnCount(tableColumnName.size());
    this->readerTable->setRowCount(readerList.size());
    this->readerTable->setHorizontalHeaderLabels(tableColumnName);

    for (int i = 0; i < readerTable->rowCount(); ++i)
    {
        this->readerTable->setItem(i, 0, new QTableWidgetItem(readerList.at(i)->getUserCode()));
        this->readerTable->setItem(i, 1, new QTableWidgetItem(readerList.at(i)->getUserName()));
        this->readerTable->setItem(i, 2, new QTableWidgetItem(readerList.at(i)->getPhone()));
        this->readerTable->setItem(i, 3, new QTableWidgetItem(readerList.at(i)->getMobile()));
        this->readerTable->setItem(i, 4, new QTableWidgetItem(readerList.at(i)->getMail()));
        this->readerTable->setItem(i, 5, new QTableWidgetItem(readerList.at(i)->getCardName()));
        this->readerTable->setItem(i, 6, new QTableWidgetItem(readerList.at(i)->getCardId()));

        MemberLevel *memberLevel = SYSTYPE->getMemberLevel(readerList.at(i)->getCardLevel());
        this->readerTable->setItem(i, 7, new QTableWidgetItem(memberLevel->getLevelName()));
        this->readerTable->setItem(i, 8, new QTableWidgetItem(memberLevel->getFee()));

        QPushButton *buttonDetail = new QPushButton();
        buttonDetail->setText("详细信息");
        buttonDetail->setEnabled(true);

        QPushButton *buttonEdit = new QPushButton();
        buttonEdit->setText("编辑");
        buttonEdit->setEnabled(true);
        this->readerTable->setCellWidget(i, 9, buttonDetail);
        this->readerTable->setCellWidget(i, 10,buttonEdit);

        QObject::connect(buttonEdit, SIGNAL(clicked()), this, SLOT(slotEdit()));
        QObject::connect(buttonDetail, SIGNAL(clicked()), this, SLOT(slotDetail()));
    }
}

void UIUserEditManage::createConnections()
{
    QObject::connect(this->deleteBtn, SIGNAL(clicked()), this, SLOT(slotDelete()));
    QObject::connect(this->addBtn, SIGNAL(clicked()), this, SLOT(slotShowRegister()));
    QObject::connect(this->closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void UIUserEditManage::slotDetail()
{

}

void UIUserEditManage::slotEdit()
{
    this->readerTable->setFocus();
    int row = -1;
    row = this->readerTable->currentRow();
    if (row >= 0)
    {
        int ret = QMessageBox::information(this, tr("information"), tr("启动编辑？"), "确定", "取消");
        if (ret == 1)
            return ;
        MyInfoWidget *myInfoWidget = new MyInfoWidget();
        myInfoWidget->initInfomation(readerList.at(row));
        myInfoWidget->show();
    }
}

void UIUserEditManage::slotDelete()
{
    QList<QTableWidgetItem*> deleteList = this->readerTable->selectedItems();
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
            int row = this->readerTable->row(selectItem);
            del_row.insert(row);
        }
    }

    std::vector<int> del_list;
    for (std::set<int>::iterator it = del_row.begin(); it != del_row.end(); ++it)
    {
        del_list.push_back(*it);
    }

    for (int i = del_list.size() - 1; i >= 0; i--)
    {
        Readers *reader = this->readerList.at(del_list.at(i));
        User *user = SYSTYPE->getUser(reader->getReaderId());
        DaoUser daoUser;
        DaoReaders daoReaders;

        if (SYSTYPE->getReaderBorrow(user->getUserID()).size() > 0)
        {
            QMessageBox::warning(this, tr("警告"),
                                 "第" + QString::number(del_list.at(i) + 1) + "行的读者有借阅记录，请先删除", "确定");
            break;
        }

        if (QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions))
        {
            if (GLobal_DB->transaction())
            {
                bool retReader = daoReaders.Delete(reader);
                bool retUser = daoUser.Delete(user);
                if (retReader == false || retUser == false)
                {
                    GLobal_DB->rollback();
                    SYSTYPE->reverUser(user->getUserID());
                    SYSTYPE->reverReader(reader->getReaderId());
                    QMessageBox::warning(this, tr("警告"), tr("删除失败"), "确定");
                    return ;
                }
                if (GLobal_DB->commit())
                {
                    this->readerTable->removeRow(del_list.at(i));
                    QMessageBox::information(this, tr("提醒"), tr("删除成功"), "确定");
                    SYSTYPE->deleteReader(reader->getReaderId());
                    SYSTYPE->deleteUser(user->getUserID());
                    this->readerList.removeAt(del_list.at(i));
                } else {
                    SYSTYPE->reverUser(user->getUserID());
                    SYSTYPE->reverReader(reader->getReaderId());
                    QMessageBox::warning(this, tr("警告"), tr("删除失败"), "确定");
                    return ;
                }
            }
        }
    }
}

void UIUserEditManage::slotShowRegister()
{
    this->uiRegister = new UIRegister();
    uiRegister->show();
    QObject::connect(uiRegister, SIGNAL(registerSuccess()), this, SLOT(slotRegister()));
}

void UIUserEditManage::slotRegister()
{
    this->uiRegister->addNewReaderToSysType();
}
