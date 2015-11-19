#include "editmanagerbtn.h"
#include "model/managers.h"
#include <QMessageBox>
#include <QTableWidget>
#include "core/systype.h"
#include "core/sysinclude.h"
#include "dao/daouser.h"


EditManagerBtn::EditManagerBtn(QWidget *parent) :
    AddManager(parent)
{
}

EditManagerBtn::~EditManagerBtn()
{

}

bool EditManagerBtn::setTableText(Managers *manager)
{
    if(manager != NULL)
    {
        this->manager = manager;
    } else {
        QMessageBox::warning(this, "警告", "出现错误", "确定");
        return false;
    }

    this->mainTable->item(0, 1)->setText(this->manager->getUserCode());
    this->mainTable->item(1, 1)->setText(this->manager->getUserName());

    if (this->manager->getSex() == sysinclude::male)
    {
        this->mainTable->item(4, 1)->setText("男");
    }
    else if (this->manager->getSex() == sysinclude::female)
    {
        this->mainTable->item(4, 1)->setText("女");
    }

    this->mainTable->item(5, 1)->setText(this->manager->getBirthDay());
    this->mainTable->item(6, 1)->setText(this->manager->getPhone());
    this->mainTable->item(7, 1)->setText(this->manager->getMobile());
    this->mainTable->item(8, 1)->setText(this->manager->getMail());
    this->mainTable->item(9, 1)->setText(this->manager->getUserCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
    this->mainTable->item(10, 1)->setText(this->manager->getUserRemark());
    return true;
}

void EditManagerBtn::slotSave()
{

    QVector<QString> tableTexVec = this->getTableText();
    this->manager->setUserCode(tableTexVec.at(0));
    this->manager->setUserName(tableTexVec.at(1));
    if (tableTexVec.at(2) == "男")
        this->manager->setSex(sysinclude::male);
    else
        this->manager->setSex(sysinclude::female);
    this->manager->setBirthDay(tableTexVec.at(3));
    this->manager->setPhone(tableTexVec.at(4));
    this->manager->setMobile(tableTexVec.at(5));
    this->manager->setMail(tableTexVec.at(6));
    this->manager->setUserCreateTime(QDateTime::fromString(tableTexVec.at(7), "yyyy-MM-dd hh:mm:ss"));
    this->manager->setUserRemark(tableTexVec.at(8));
    User *user = this->manager;
    DaoUser daoUser;
    bool ret = daoUser.Update(user);
    if (ret)
    {
        QMessageBox::warning(this, "提醒", "更新成功！", "确定");
    }
    else
    {
        QMessageBox::warning(this, "警告", "更新失败！", "确定");
        SYSTYPE->reverUser(user->getUserID());
    }

}
