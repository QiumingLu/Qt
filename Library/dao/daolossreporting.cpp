#include "daolossreporting.h"
#include <QVector>
#include "DaoHeader.h"
#include "model/lossreporting.h"

DaoLossReporting::DaoLossReporting()
{
}

/*
 * @brief
 * 本函数实现向数据库中存放LossReporting的信息
 * @name Add
 * @arg
 * pObj QObject* :@class LossReporting*, 需要存放到数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoLossReporting::Add(LossReporting *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList outFields("ID");     //primary key
    return call_proc(pObj, "LOSS_REPORTING_INSERT_PROC", outFields);
}

/*
 * @brief
 * 本函数实现向数据库中删除LossReporting的信息
 * @name Delete
 * @arg
 * pObj QObject* :@class LossReporting*, 需要存放到数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoLossReporting::Delete(LossReporting *pObj)
{
    Q_ASSERT(pObj != NULL);
    return BaseDao::Delete(pObj, "LOSS_REPORTING", "ID");
}

/*
 * @brief
 * 本函数实现向数据库中更新LossReporting的信息
 * @name Update
 * @arg
 * pObj QObject* :@class LossReporting*, 需要更新到数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoLossReporting::Update(LossReporting *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions("ID");      //primary key
    return BaseDao::Update(pObj, "LOSS_REPORTING", conditions);
}

/*
 * @brief
 * 本函数实现向数据库中查询LossReporting的信息
 * @name Select
 * @arg
 * pObj QObject* ：@class LossReporting*, 需要查询到数据库的信息
 * @return
 * QVector<LossReporting*>
 * @author
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
QVector<LossReporting*> DaoLossReporting::Select(LossReporting *pObj, int cond)
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
            conditions.append("READER_ID");
        }
    }

    QRetVec retVec = BaseDao::Select(pObj, "LOSS_REPORTING", conditions);
    QVector<LossReporting*> ret(retVec.size());
    for (int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new LossReporting();
        QObject *p_Obj = ret[i];
        QVector<CPair> oneRet = retVec[i];
        for (int idx = 0; idx < oneRet.size(); ++idx)
        {
            p_Obj->setProperty(oneRet[i].string.toStdString().c_str(),
                               oneRet[i].var);
        }
    }
    return ret;
}
