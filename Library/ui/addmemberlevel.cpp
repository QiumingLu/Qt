#include "addmemberlevel.h"
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "model/memberlevel.h"
#include "dao/daomemberlevel.h"
#include "core/systype.h"
#include "core/sysinclude.h"

AddMemberLevel::AddMemberLevel(QWidget *parent) :
    QWidget(parent)
{
    this->memberLevel = NULL;
    this->initUI();
    this->createConnections();
    this->initTable();
}

AddMemberLevel::~AddMemberLevel()
{
    SAFE_DELETE(cancelBtn);
    SAFE_DELETE(saveBtn);
    SAFE_DELETE(mainTable);
    SAFE_DELETE(btnLayout);
    SAFE_DELETE(mainLayout);
}

void AddMemberLevel::initUI()
{
    this->mainTable = new QTableWidget();
    this->cancelBtn = new QPushButton("取消");
    this->saveBtn = new QPushButton("保存");
    this->btnLayout = new QHBoxLayout();
    this->mainLayout = new QVBoxLayout();

    this->btnLayout->addWidget(this->cancelBtn);
    this->btnLayout->addStretch();
    this->btnLayout->addWidget(this->saveBtn);
    this->mainLayout->addWidget(this->mainTable);
    this->mainLayout->addLayout(this->btnLayout);
    this->setLayout(mainLayout);
}

void AddMemberLevel::createConnections()
{
    QObject::connect(this->cancelBtn, SIGNAL(clicked()), this, SLOT(slotCancel()));
    QObject::connect(this->saveBtn, SIGNAL(clicked()), this, SLOT(slotSave()));
}

void AddMemberLevel::initTable()
{
    QStringList tableRowName;
    tableRowName.append("级别");
    tableRowName.append("最长的借书时间");
    tableRowName.append("一次最多可借的书的数目");
    tableRowName.append("会员费");

    QStringList tableColumnName;
    tableColumnName.append("名字");
    tableColumnName.append("对应值");

    this->mainTable->setColumnCount(tableColumnName.size());
    this->mainTable->setRowCount(tableRowName.size());
    this->mainTable->setHorizontalHeaderLabels(tableColumnName);


    for (int i = 0; i < tableRowName.size(); ++i)
    {
        this->mainTable->setItem(i, 0, new QTableWidgetItem(tableRowName.at(i)));
        this->mainTable->setItem(i, 1, new QTableWidgetItem());
    }
}

bool AddMemberLevel::initLevelInfo(MemberLevel *memberLevel)
{
    if (memberLevel == NULL)
        return false;

    this->memberLevel = memberLevel;
    this->mainTable->item(0, 1)->setText(memberLevel->getLevelName());
    this->mainTable->item(1, 1)->setText(QString::number(memberLevel->getDays()));
    this->mainTable->item(2, 1)->setText(QString::number(memberLevel->getNumbers()));
    this->mainTable->item(3, 1)->setText(QString::number(memberLevel->getFee()));
    return true;
}

QVector<QString> AddMemberLevel::getMemberLevelVec() const
{
    QVector<QString> memberLevelVec;
    for (int i = 0; i < this->mainTable->rowCount(); ++i)
    {
        QString temp = this->mainTable->item(i, 1)->text();
        memberLevelVec.append(temp);
    }
    return memberLevelVec;
}

void AddMemberLevel::slotCancel()
{
    int ret = QMessageBox::information(this, tr("提醒"), "确定放弃保存修改的内容？", "确定", "取消");
    if (ret == 0)
        close();
    else
        return;
}

void AddMemberLevel::slotSave()
{
    QVector<QString> memberLevelVec = this->getMemberLevelVec();

    if (this->memberLevel == NULL)
    {
        this->memberLevel = new MemberLevel();
        this->memberLevel->setLevelName(memberLevelVec.at(0));
        this->memberLevel->setDays(memberLevelVec.at(1).toInt());
        this->memberLevel->setNumbers(memberLevelVec.at(2).toInt());
        this->memberLevel->setFee(memberLevelVec.at(3).toDouble());

        DaoMemberLevel daoMemberLevel;
        bool ret = daoMemberLevel.Add(memberLevel);
        if (ret)
        {
            QString tableName = "MEMBER_LEVEL";
            QString outFields = "LEVEL_ID";
            BaseDao baseDao;
            int id = baseDao.getId(tableName, outFields);
            this->memberLevel->setLevelId(id);
            SYSTYPE->addMemberLevel(id, memberLevel);
            QMessageBox::information(this, "提醒", "保存成功！", "确定");
        }
        else
        {
            QMessageBox::information(this, "提醒", "保存失败！", "确定");
        }
    }
    else
    {
        this->memberLevel->setLevelName(memberLevelVec.at(0));
        this->memberLevel->setDays(memberLevelVec.at(1).toInt());
        this->memberLevel->setNumbers(memberLevelVec.at(2).toInt());
        this->memberLevel->setFee(memberLevelVec.at(3).toDouble());

        DaoMemberLevel daoMemberLevel;
        bool ret = daoMemberLevel.Update(this->memberLevel);

        if (ret)
        {
            QMessageBox::information(this, "提醒", "保存成功！", "确定");
            SYSTYPE->reverMemberLevel(this->memberLevel->getLevelId());
        }
        else
        {
            QMessageBox::information(this, "提醒", "保存失败！", "确定");
        }
    }
}

