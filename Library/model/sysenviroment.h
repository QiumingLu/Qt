#ifndef SYSENVIROMENT_H
#define SYSENVIROMENT_H

#include <QtSql/QSqlDatabase>

class User;
class Readers;
class Managers;

#define GLobal_DB (SysEnviroment::getInstance()->getDB())

class SysEnviroment
{
private:
    SysEnviroment();
    static SysEnviroment *m_Instance;
    SysEnviroment(const SysEnviroment&) {}
    SysEnviroment & operator = (const SysEnviroment &)
    {
        return *this;
    }
    class Garbo
    {
    public:
        ~Garbo()
        {
            if (SysEnviroment::getInstance())
            {
                delete SysEnviroment::getInstance();
            }
        }
    };
    static Garbo Garbo;

public:
    static SysEnviroment *getInstance()
    {
        if (m_Instance == NULL)
        {
            m_Instance = new SysEnviroment();
        }
        return m_Instance;
    }

    QSqlDatabase* getDB();
    void setUser(User *user);
    User* getUser() const;
    Readers* getReader() const;
    Managers* getManager() const;

private:
    QSqlDatabase* db;
    User* user;
    Readers* reader;
    Managers* manager;
};

#endif // SYSENVIROMENT_H
