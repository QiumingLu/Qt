#include "daouniquebook.h"
#include <QVector>
#include "dao/DaoHeader.h"
#include "model/uniquebook.h"

DaoUniqueBook::DaoUniqueBook()
{
}

/*
 * @brief
 * 本函数实现向数据库中存放UniqueBook的信息
 * @name Add
 * @arg
 * pObj QObject* :@class UniqueBook*, 需要添加到数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoUniqueBook::Add(UniqueBook *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList outFields("ID");
    return call_proc(pObj, "UNIQUE_BOOK_INSERT_PROC", outFields);
}

/*
 * @brief
 * 本函数实现向数据库中删除UniqueBook的信息
 * @name Delete
 * @arg
 * pObj QObject* :@class UniqueBook*, 需要删除的数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoUniqueBook::Delete(UniqueBook *pObj)
{
    Q_ASSERT(pObj != NULL);
    return BaseDao::Delete(pObj, "UNIQUE_BOOK", "ID");
}


/*
 * @brief
 * 本函数实现向数据库中更新UniqueBook的信息
 * @name Update
 * @arg
 * pObj QObject* :@class UniqueBook*, 需要更新的数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoUniqueBook::Update(UniqueBook *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions("ID");
    return BaseDao::Update(pObj, "UNIQUE_BOOK", conditions);
}

/*
 * @brief
 * 本函数实现向数据库中查询UniqueBook的信息
 * @name Select
 * @arg
 * pObj QObject* :@class UniqueBook*, 需要查询数据库中的信息
 * @return
 * QVector<UniqueBook*>
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
QVector<UniqueBook*> DaoUniqueBook::Select(UniqueBook *pObj, int cond)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions;
    if (cond > 0)
    {
        if (cond & COND_ID)
        {
            conditions.append("ID");
        }
        if (cond & COND_NAME)
        {
            conditions.append("BOOK_CODE");
        }
        if(cond & COND_SUPERIOR_ID)
        {
            conditions.append("BOOK_ID");
        }
    }

    QRetVec retVec = BaseDao::Select(pObj, "UNIQUE_BOOK", conditions);
    QVector<UniqueBook*> ret(retVec.size());

    for (int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new UniqueBook();
        QObject *p_Obj = ret[i];
        QVector<CPair> oneRet = retVec.at(i);

        for (int idx = 0; idx < oneRet.size(); ++idx)
        {
            p_Obj->setProperty(oneRet.at(idx).string.toStdString().c_str(),
                               oneRet.at(idx).var);
        }
    }
    return ret;
}
