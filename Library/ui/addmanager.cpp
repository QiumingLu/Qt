#include "addmanager.h"
#include <QTableWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include "model/managers.h"
#include "core/sysinclude.h"
#include "dao/daomanagers.h"
#include "dao/daouser.h"
#include "model/user.h"
#include "model/sysenviroment.h"
#include "core/systype.h"

AddManager::AddManager(QWidget *parent) :
    AddBaseWidget(parent)
{
    this->passEdit = NULL;
    this->initTable();
}

AddManager::~AddManager()
{
    SAFE_DELETE(passEdit);
    SAFE_DELETE(morePswEdit);
}

void AddManager::initTable()
{
    QStringList tableColumnName;
    tableColumnName.append("名字");
    tableColumnName.append("对应值");

    QStringList tableRowName;
    tableRowName.append("Library ID");
    tableRowName.append("用户姓名");
    tableRowName.append("密码");
    tableRowName.append("确认密码");
    tableRowName.append("性别");
    tableRowName.append("出生日期");
    tableRowName.append("电话");
    tableRowName.append("手机");
    tableRowName.append("邮箱");
    tableRowName.append("加入时间");
    tableRowName.append("备注");

    this->mainTable->setColumnCount(tableColumnName.size());
    this->mainTable->setRowCount(tableRowName.size());
    this->mainTable->setHorizontalHeaderLabels(tableColumnName);

    for (int i = 0; i < tableRowName.size(); ++i)
    {
        this->mainTable->setItem(i, 0, new QTableWidgetItem(tableRowName.at(i)));
        if (i != 2 && i != 3)
            this->mainTable->setItem(i, 1, new QTableWidgetItem());
        else if (i == 2)
        {
            this->passEdit = new QLineEdit();
            this->mainTable->setCellWidget(i, 1, passEdit);
            passEdit->setEchoMode(QLineEdit::Password);
        }
        else if (i ==3)
        {
            this->morePswEdit = new QLineEdit();
            this->mainTable->setCellWidget(i, 1, morePswEdit);
            morePswEdit->setEchoMode(QLineEdit::Password);
        }
    }
}

QVector<QString> AddManager::getTableText() const
{
    QVector<QString> tableTextVec;
    for (int i = 0; i < this->mainTable->rowCount(); ++i)
    {
        if (i != 2 && i != 3)
            tableTextVec.append(this->mainTable->item(i, 1)->text());
    }
    return tableTextVec;
}
