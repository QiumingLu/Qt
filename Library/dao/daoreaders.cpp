#include "daoreaders.h"
#include <QVector>
#include <QStringList>
#include "DaoHeader.h"
#include "model/readers.h"

DaoReaders::DaoReaders()
{
}

/*
 * @brief
 * 本函数实现向数据库中添加Reader的信息
 * @name Add
 * @arg
 * pObj QObject* ：@class Reader*, 需要添加到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoReaders::Add(Readers *pObj)
{
    Q_ASSERT(pObj != NULL);
    QList<QVariant> inFields;
    inFields.append(pObj->getReaderId());
    inFields.append(pObj->getCardName());
    inFields.append(pObj->getCardId());
    inFields.append(pObj->getCardLevel());
    inFields.append(pObj->getDay());
    QList<QVariant> outFields;
    outFields.append(pObj->getId());
    return BaseDao::callProc("READERS_INSERT_PROC",inFields, outFields);
}

/*
 * @brief
 * 本函数实现向数据库中删除Readers的信息
 * @name Delete
 * @arg
 * pObj QObject* ：@class Readers*, 需要删除到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoReaders::Delete(Readers *pObj)
{
    Q_ASSERT(pObj != NULL);
    return BaseDao::Delete(pObj, "READERS", "ID");
}

/*
 * @brief
 * 本函数实现向数据库中更新Readers的信息
 * @name Update
 * @arg
 * pObj QObject* ：@class Readers*, 需要更新到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoReaders::Update(Readers *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions("ID");
    QStringList updateFields;
    updateFields.append("READER_ID");
    updateFields.append("CARD_NAME");
    updateFields.append("CARD_ID");
    updateFields.append("CARD_LEVEL");
    updateFields.append("DAY");
    return BaseDao::Update(pObj, "READERS", updateFields, conditions);
}

/*
 * @brief
 * 本函数实现向数据库中查询Reader的信息
 * @name Select
 * @arg
 * pObj QObject* ：@class Reader*, 需要查询数据库的信息
 * @return
 * QVector<Readers*>
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
QVector<Readers*> DaoReaders::Select(Readers *pObj, int cond)
{
    Q_ASSERT(pObj != NULL);

    QString sql = "select * from READERS ";

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
            inFields.append("READER_ID");
            sql += "where READER_ID = ";
            sql += QString::number(pObj->getReaderId());
        }
    }

    QStringList outFields;
    outFields.append("ID");
    outFields.append("READER_ID");
    outFields.append("CARD_NAME");
    outFields.append("CARD_ID");
    outFields.append("CARD_LEVEL");
    outFields.append("DAY");

    QRetVec retVec = BaseDao::callSelectSql(pObj, sql, inFields, outFields);
    QVector<Readers*> ret(retVec.size());

    for(int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new Readers();
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
