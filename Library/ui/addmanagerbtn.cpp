#include "addmanagerbtn.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QLineEdit>
#include <QSqlDriver>
#include "dao/daouser.h"
#include "dao/daomanagers.h"
#include "core/sysinclude.h"
#include "model/sysenviroment.h"
#include "model/managers.h"
#include "core/systype.h"


AddManagerBtn::AddManagerBtn(QWidget *parent) :
    AddManager(parent)
{
}

AddManagerBtn::~AddManagerBtn()
{

}

void AddManagerBtn::slotSave()
{
    DaoUser daoUser;
    DaoManagers daoManager;
    QVector<QString> tableTexVec = this->getTableText();
    if (this->morePswEdit->text() != this->passEdit->text())
    {
        QMessageBox::warning(this, "警告", "两次密码不一致", "确定");
        return;
    }

    this->manager = new Managers();

    /*如果输入的是md5，则无需转换*/
   if (this->passEdit->text().length() == 32) {
        this->manager->setUserPsw(this->passEdit->text());
    } else {
        QString md5password;
        QByteArray bb;
        bb = QCryptographicHash::hash(this->passEdit->text().toLatin1(), QCryptographicHash::Md5);
        md5password.append(bb.toHex());
        this->manager->setUserPsw(md5password);
    }

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
    this->manager->setUserCreateTime(QDateTime::currentDateTime());
    this->manager->setUserRemark(tableTexVec.at(8));
    this->manager->setUserType(sysinclude::admin);

    if (QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions))
    {
        if (QSqlDatabase::database().transaction())
        {
            User *user = this->manager;
            bool retUser = daoUser.Add(user);
            QString tableName = "USER";
            QString outFields = "USER_ID";
            BaseDao baseDao;
            int userId = baseDao.getId(tableName, outFields);

            this->manager->setManagerId(userId);
            bool retManager = daoManager.Add(this->manager);

            if (retUser == false || retManager == false)
            {
                QSqlDatabase::database().rollback();
                QMessageBox::warning(this, "警告", "添加失败！", "确定");
                SAFE_DELETE(this->manager);
                user = NULL;
                return;
            }

            if (QSqlDatabase::database().commit())
            {
                QMessageBox::information(this, "提醒", "保存成功！", "确定");
                SYSTYPE->addUser(userId, user);
                SYSTYPE->addManager(userId, manager);
            }
            else
            {
                QMessageBox::warning(this, "提醒", "更新失败！", "确定");
            }
        }
    }
}
