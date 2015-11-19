#include "daouser.h"
#include <QVector>
#include <QStringList>
#include "DaoHeader.h"
#include "model/user.h"

DaoUser::DaoUser()
{
}

/*
 * @brief
 * 本函数实现向数据库中存放User的信息
 * @name Add
 * @arg
 * pObj QObject* ：@class User*, 需要添加到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoUser::Add(User *pObj)
{
    Q_ASSERT(pObj != NULL);
    QList<QVariant> inFields;
    QList<QVariant> outFields;

    inFields.append(pObj->getUserCode());
    inFields.append(pObj->getUserName());
    inFields.append(pObj->getUserPsw());
    inFields.append(pObj->getSex());
    inFields.append(pObj->getBirthDay());
    inFields.append(pObj->getPhone());
    inFields.append(pObj->getMobile());
    inFields.append(pObj->getMail());
    inFields.append(pObj->getUserType());
    inFields.append(pObj->getUserRemark());
    inFields.append(pObj->getUserLastLogTime());
    inFields.append(pObj->getUserCreateTime());

    outFields.append(pObj->getUserID());

    return BaseDao::callProc("USER_INSERT_PROC", inFields, outFields);
}

/*
 * @brief
 * 本函数实现向数据库中删除User的信息
 * @name Delete
 * @arg
 * pObj QObject* ：@class User*, 需要删除到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoUser::Delete(User *pObj)
{
    Q_ASSERT(pObj != NULL);
    return BaseDao::Delete(pObj, "USER", "USER_ID");
}

/*
 * @brief
 * 本函数实现向数据库中更新User的信息
 * @name Update
 * @arg
 * pObj QObject* ：@class User*, 需要更新到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool DaoUser::Update(User *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions("USER_ID");
    QStringList updateFields;
    updateFields.append("USER_CODE");
    updateFields.append("USER_NAME");
    updateFields.append("USER_PSW");
    updateFields.append("SEX");
    updateFields.append("BIRTHDAY");
    updateFields.append("PHONE");
    updateFields.append("MOBILE");
    updateFields.append("MAIL");
    updateFields.append("USER_TYPE");
    updateFields.append("USER_REMARK");
    updateFields.append("USER_LASTLOGTIME");
    updateFields.append("USER_CREATETIME");

    return BaseDao::Update(pObj, "USER", updateFields, conditions);
}

/*
 * @brief
 * 本函数实现向数据库中查询User的信息
 * @name Select
 * @arg
 * pObj QObject* ：@class User*, 需要查询数据库的信息
 * @return
 * QVector<User*>
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
QVector<User*> DaoUser::Select(User *pObj, int cond)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions;

    if (cond > 0)
    {
        if (cond & COND_ID)
        {
            conditions.append("USER_ID");
        }
        if (cond & COND_NAME)
        {
            conditions.append("USER_CODE");
        }
        if (cond & COND_TYPE_ID)
        {
            conditions.append("USER_TYPE");
        }
    }

    QRetVec retVec = BaseDao::Select(pObj, "USER", conditions);
    QVector<User*> ret(retVec.size());

    for (int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new User();
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
