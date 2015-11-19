#include "sysenviroment.h"
#include "model/user.h"
#include "model/readers.h"
#include "dao/daoreaders.h"
#include "model/managers.h"
#include "dao/daomanagers.h"
#include "core/sysinclude.h"
#include "dao/DaoHeader.h"
#include <QMessageBox>

SysEnviroment* SysEnviroment::m_Instance = new SysEnviroment();

SysEnviroment::SysEnviroment()
{
    QSqlDatabase tmpDB = QSqlDatabase::addDatabase("QMYSQL");
    this->db = new QSqlDatabase(tmpDB);
    this->db->setHostName("localhost");
    this->db->setDatabaseName("Library");
    this->db->setUserName("root");
    this->db->setPassword("123456");
}

QSqlDatabase* SysEnviroment::getDB()
{
    return this->db;
}

User* SysEnviroment::getUser() const
{
    return this->user;
}

Readers* SysEnviroment::getReader() const
{
    return this->reader;
}

Managers* SysEnviroment::getManager() const
{
    return this->manager;
}

void SysEnviroment::setUser(User *user)
{
    Q_ASSERT(user != NULL);
    this->user = user;
    if (this->user->getUserType() == sysinclude::reader) {
        this->reader = new Readers();
        this->reader->setUserID(user->getUserID());
        this->reader->setReaderId(user->getUserID());
        DaoReaders daoReaders;
        QVector<Readers*> readerVec = daoReaders.Select(reader, COND_NAME);

        if (readerVec.size() != 0) {
            this->reader = readerVec.at(0);
            this->reader->setUserID(user->getUserID());
            this->reader->setUserCode(user->getUserCode());
            this->reader->setUserName(user->getUserName());
            this->reader->setUserPsw(user->getUserPsw());
            this->reader->setSex(user->getSex());
            this->reader->setBirthDay(user->getBirthDay());
            this->reader->setPhone(user->getPhone());
            this->reader->setMobile(user->getMobile());
            this->reader->setMail(user->getMail());
            this->reader->setUserType(user->getUserType());
            this->reader->setUserRemark(user->getUserRemark());
            this->reader->setUserLastLogTime(user->getUserLastLogTime());
            this->reader->setUserCreateTime(user->getUserCreateTime());
        } else {
            int ret = QMessageBox::warning(0, "警告",
                                           "数据库出现严重！程序将立即结束！", "确定");
            if (ret == 0)
                exit(0);
        }

    } else {
        this->manager = new Managers();
        this->manager->setUserID(user->getUserID());
        this->manager->setManagerId(user->getUserID());
        DaoManagers daoManagers;
        QVector<Managers*> managerVec = daoManagers.Select(manager, COND_NAME);

        if (managerVec.size() != 0) {
            this->manager = managerVec.at(0);

            this->manager->setUserCode(user->getUserCode());
            this->manager->setUserName(user->getUserName());
            this->manager->setUserPsw(user->getUserPsw());
            this->manager->setSex(user->getSex());
            this->manager->setBirthDay(user->getBirthDay());
            this->manager->setPhone(user->getPhone());
            this->manager->setMobile(user->getMobile());
            this->manager->setMail(user->getMail());
            this->manager->setUserType(user->getUserType());
            this->manager->setUserRemark(user->getUserRemark());
            this->manager->setUserLastLogTime(user->getUserLastLogTime());
            this->manager->setUserCreateTime(user->getUserCreateTime());
        } else {
            int ret = QMessageBox::warning(0, "警告",
                                           "数据库出现严重！程序将立即结束！", "确定");
            if (ret == 0)
                exit(0);
        }
    }
}
