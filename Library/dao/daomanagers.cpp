#include "daomanagers.h"
#include <QVector>
#include <QStringList>
#include "DaoHeader.h"
#include "model/managers.h"

DaoManagers::DaoManagers()
{
}

/*
 * @brief
 * 本函数实现向数据库中存放Managers的信息
 * @name Add
 * @arg
 * pObj QObject* ：@class Managers*, 需要存放到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoManagers::Add(Managers *pObj)
{
    Q_ASSERT(pObj != NULL);
    QList<QVariant> inFields;
    inFields.append(pObj->getManagerId());
    QList<QVariant> outFields;
    outFields.append(pObj->getId());
    return BaseDao::callProc("MANAGERS_INSERT_PROC", inFields, outFields);
}

/*
 * @brief
 * 本函数实现向数据库中删除Managers的信息
 * @name Delete
 * @arg
 * pObj QObject* ：@class Managers*, 需要删除数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoManagers::Delete(Managers *pObj)
{
    Q_ASSERT(pObj != NULL);
    return BaseDao::Delete(pObj, "MANAGERS", "ID");
}

/*
 * @brief
 * 本函数实现向数据库中更新Managers的信息
 * @name Update
 * @arg
 * pObj QObject* ：@class Managers*, 需要更新到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoManagers::Update(Managers *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions("ID");
    return BaseDao::Update(pObj, "MANAGERS", conditions);
}

/*
 * @brief
 * 本函数实现向数据库中查询Managers的信息
 * @name Select
 * @arg
 * pObj QObject* ：@class Managers*, 需要查询数据库的信息
 * @return
 * QVector<Managers*>
 * @author
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
QVector<Managers*> DaoManagers::Select(Managers *pObj, int cond)
{
    Q_ASSERT(pObj != NULL);

    QString sql = "select * from MANAGERS ";
    QStringList inFields;
    if (cond > 0)
    {
        if (cond & COND_ID)
        {
            inFields.append("ID");
            sql += "where ID = ";
            sql += QString::number(pObj->getId());
        }
        if (cond & COND_NAME)
        {
            inFields.append("MANAGER_ID");
            sql += " where MANAGER_ID = ";
            sql += QString::number(pObj->getManagerId());
        }
    }

    QStringList outFields;
    outFields.append("ID");
    outFields.append("MANAGER_ID");

    QRetVec retVec = BaseDao::callSelectSql(pObj, sql, inFields, outFields);
    QVector<Managers*> ret(retVec.size());

    for (int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new Managers();
        QObject *p_Obj = ret[i];
        QVector<CPair> oneRet = retVec[i];

        for (int idx = 0; idx < oneRet.size(); ++idx)
        {
            p_Obj->setProperty(oneRet[idx].string.toStdString().c_str(),
                               oneRet[idx].var);
        }
    }
    return ret;
}
