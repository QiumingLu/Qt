#include "daoborrow.h"
#include <QVector>
#include "DaoHeader.h"
#include "model/borrow.h"

DaoBorrow::DaoBorrow()
{
}

/*
 * @brief
 * 本函数实现向数据库中存放Borrow的信息
 * @name Add
 * @arg
 * pObj QObject* :@class Borrow*, 需要存放到数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */

bool DaoBorrow::Add(Borrow *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList outFields("ID");     //primary key
    return call_proc(pObj, "BORROW_INSERT_PROC", outFields);
}

/*
 * @brief
 * 本函数实现向数据库中删除Borrow的信息
 * @name Delete
 * @arg
 * pObj QObject* :@class Borrow*, 需要删除的数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */

bool DaoBorrow::Delete(Borrow *pObj)
{
    Q_ASSERT(pObj != NULL);
    return BaseDao::Delete(pObj, "BORROW", "ID");
}

/*
 * @brief
 * 本函数实现向数据库中更新Borrow的信息
 * @name Update
 * @arg
 * pObj QObject* :@class Borrow*, 需要更新的数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoBorrow::Update(Borrow *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions("ID");   //primary key
    return BaseDao::Update(pObj, "BORROW", conditions);
}

/*
 * @brief
 * 本函数实现向数据库中查询Borrow的信息
 * @name Select
 * @arg
 * pObj QObject* ：@class Borrow*, 需要查询到数据库的信息
 * @return
 * QVector<Borrow*>
 * @author
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
QVector<Borrow*> DaoBorrow::Select(Borrow *pObj, int cond)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions;
    if (cond > 0)
    {
        if (cond & COND_ID)
        {
            conditions.append("ID");
        }
        if (cond & COND_SUPERIOR_ID)
        {
            conditions.append("READER_ID");
        }
        if (cond & COND_NAME)
        {
            conditions.append("BOOK_ID");
        }
    }

    QRetVec retVec = BaseDao::Select(pObj, "BORROW",conditions);
    QVector<Borrow*> ret (retVec.size());

    for (int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new Borrow();
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
