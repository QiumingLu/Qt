#include "daousertype.h"
#include <QVector>
#include "DaoHeader.h"
#include "model/usertype.h"

DaoUserType::DaoUserType()
{
}

/*
 * @brief
 * 本函数实现向数据库中添加UserType的信息
 * @name Add
 * @arg
 * pObj QObject* :@class UserType*, 需要添加数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoUserType::Add(UserType *pObj)
{
    Q_ASSERT(pObj != NULL);
    return Insert(pObj, "USER_TYPE");
}

/*
 * @brief
 * 本函数实现向数据库中删除UserType的信息
 * @name Delete
 * @arg
 * pObj QObject* :@class UserType*, 需要删除数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoUserType::Delete(UserType *pObj)
{
    Q_ASSERT(pObj != NULL);
    return BaseDao::Delete(pObj, "USER_TYPE", "USER_TYPE_ID");
}

/*
 * @brief
 * 本函数实现向数据库中更新UserType的信息
 * @name Update
 * @arg
 * pObj QObject* :@class UserType*, 需要更新数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoUserType::Update(UserType *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions("USER_TYPE_ID");
    return BaseDao::Update(pObj, "USER_TYPE", conditions);
}

/*
 * @brief
 * 本函数实现向数据库中查询UserType的信息
 * @name Select
 * @arg
 * pObj QObject* :@class UserType*, 需要查询数据库中的信息
 * @return
 * QVector<UserType*>
 * @auhotr
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
QVector<UserType*> DaoUserType::Select(UserType *pObj, int cond)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions;

    if (cond > 0)
    {
        if (cond & COND_ID)
        {
            conditions.append("USER_TYPE_ID");
        }
        if (cond & COND_NAME)
        {
            conditions.append("USER_TYPE_NAME");
        }
    }

    QRetVec retVec = BaseDao::Select(pObj, "USER_TYPE", conditions);
    QVector<UserType*> ret(retVec.size());

    for (int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new UserType();
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
