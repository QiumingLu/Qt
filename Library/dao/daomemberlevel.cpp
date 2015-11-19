#include "daomemberlevel.h"
#include <QVector>
#include "DaoHeader.h"
#include "model/memberlevel.h"

DaoMemberLevel::DaoMemberLevel()
{
}


/*
 * @brief
 * 本函数实现向数据库中存放MemberLevel的信息
 * @name Add
 * @arg
 * pObj QObject* ：@class MemberLevel*, 需要存放到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoMemberLevel::Add(MemberLevel *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList outFields("LEVEL_ID");
    return BaseDao::call_proc(pObj, "MEMBER_LEVEL_INSERT_PROC", outFields);
}

/*
 * @brief
 * 本函数实现向数据库中删除MemberLevel的信息
 * @name Delete
 * @arg
 * pObj QObject* ：@class MemberLevel*, 需要删除到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoMemberLevel::Delete(MemberLevel *pObj)
{
    Q_ASSERT(pObj != NULL);
    return BaseDao::Delete(pObj, "MEMBER_LEVEL", "LEVEL_ID");
}

/*
 * @brief
 * 本函数实现向数据库中更新MemberLevel的信息
 * @name Update
 * @arg
 * pObj QObject* ：@class MemberLevel*, 需要更新到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoMemberLevel::Update(MemberLevel *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions("LEVEL_ID"); //primary key
    return BaseDao::Update(pObj, "MEMBER_LEVEL", conditions);
}

/*
 * @brief
 * 本函数实现向数据库中查询MemberLevel的信息
 * @name Select
 * @arg
 * pObj QObject* ：@class MemberLevel*, 需要查询到数据库的信息
 * @return
 * QVector<MemberLevel*>
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
QVector<MemberLevel*> DaoMemberLevel::Select(MemberLevel *pObj, int cond)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions;
    if (cond > 0)
    {
        if (cond & COND_ID)
        {
            conditions.append("LEVEL_ID");
        }
        if (cond & COND_NAME)
        {
            conditions.append("LEVEL_NAME");
        }
    }

    QRetVec retVec = BaseDao::Select(pObj, "MEMBER_LEVEL", conditions);
    QVector<MemberLevel*> ret(retVec.size());

    for (int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new MemberLevel();
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
