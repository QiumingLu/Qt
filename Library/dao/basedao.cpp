#include "basedao.h"
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlResult>
#include <QVector>
#include <QSql>
#include <QMessageBox>
#include <QMetaObject>
#include <QMetaProperty>
#include <iostream>
#include "model/sysenviroment.h"

//开启数据库连接
#define DB_BEGIN(x) \
    bool ismyOpen = true; \
    if (GLobal_DB->isOpen()) \
{\
    ismyOpen = false;\
    } else {\
    if (!GLobal_DB->open())\
{\
    Q_ASSERT_X(false, #x, "database can not open ");\
    }\
    }\

//关闭数据库连接
#define DB_END()\
    if(ismyOpen)\
    GLobal_DB->close();\

BaseDao::BaseDao()
{               
}

/*
 * @brief
 * 提高Dao层打开数据库
 * @name openDB()
 * @arg
 * void
 * @return bool
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool BaseDao::openDB()
{
    if (!GLobal_DB->isOpen())
        return GLobal_DB->open();
    return true;
}

bool BaseDao::closeDB()
{
    if (GLobal_DB->isOpen())
    {
        GLobal_DB->close();
    }
    return true;
}

/*
 * @brief
 * 创建事物
 * @name transaction()
 * @arg
 * void
 * @return bool
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool BaseDao::transaction()
{
    return GLobal_DB->transaction();
}

/*
 * @brief
 * 创建事物
 * @name
 * commit()
 * @arg void
 * @return bool
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 * @test
 * no
 */
bool BaseDao::commit()
{
    return GLobal_DB->commit();
}


/*
 * @brief
 * 执行存储过程
 * @name call_proc
 * @arg
 * pObj QObject* [In]需要进行数据库操作的对象，需要继承与QObject
 * proc_name const [In] QString& 存储过程的名字
 * inFields const [In] QStringList& 需要输入的信息
 * outFields const [In] QStringList& 需要输出的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @remark
 * 本函数默认是为insert写的存储过程，默认是插入所有的信息，out是信息主要是返回id
 * 输出的信息，通过pObj返回
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 * @test
 * no
 */
bool BaseDao::call_proc(QObject *pObj, const QString &proc_name,
                        const QStringList &inFields, const QStringList &outFields, bool isOutputDebug)
{
    QString sql = QString("call %1 (").arg(proc_name);
    sql += makeQuestionMarkList(inFields.size() + outFields.size());
    sql += ")";

    DB_BEGIN(call_proc);
    QSqlQuery query( (*GLobal_DB) );
    query.prepare(sql);

    int idx = 0;
    for (int i = 0; i < inFields.size(); ++i)
    {
        QVariant var = pObj->property(inFields[i].toStdString().c_str());
        std::cout << inFields[i].toStdString() << " " << var.toString().toStdString() << std::endl;
        if (var.type() == QVariant::Double) {
            float tmp = var.toDouble();
            query.bindValue(idx++, tmp);
        }
        //ID 外键
        else if (var.type() == QVariant::Int && inFields[i].indexOf("_ID", 0, Qt::CaseInsensitive)
                 && pObj->property(inFields[i].toStdString().c_str()).toInt() == -1)
        {
            query.bindValue(idx++, QVariant());
        }
        else
        {
            query.bindValue(idx++, var);
        }
    }

    for (int i = 0; i < outFields.size(); ++i)
    {
        query.bindValue(idx++, "0", QSql::Out);
    }

    bool ret = query.exec();
    if (ret)
    {
        idx = idx - outFields.size();
        for (int i = 0; i < outFields.size(); ++i)
        {
            pObj->setProperty(outFields[i].toStdString().c_str(), query.boundValue(idx + i));
        }
    } else {
        if (isOutputDebug) {
            qDebug() << "[DATABASE][*INSERT*][PROC_NAME: " << proc_name << "]ERROR: "
                     << query.lastError().text() << "\n";
        }
    }
    DB_END();
    return ret;
}

/*
 * @brief
 * 执行存储过程
 * @name call_proc
 * @arg
 * pObj QObject* [In]需要进行数据库操作的对象，需要继承与QObject
 * proc_name const [In] QString& 存储过程的名字
 * outFields const [In] QStringList& 需要输出的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @remark
 * 本函数默认是为insert写的存储过程，默认是插入所有的信息，out是信息主要是返回id
 * 输出的信息，通过pObj返回
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 * @test
 * no
 */
bool BaseDao::call_proc(QObject *pObj, const QString &proc_name,
                        const QStringList &outFields, bool isOutputDebug)
{
    QStringList excludeList("objectName");
    excludeList.append(outFields);
    QStringList inFields = getAvaProperties(pObj->metaObject(), excludeList);
    return call_proc(pObj, proc_name, inFields, outFields, isOutputDebug);
}

/*
 * @brief
 * 插入整个对象
 * @name Insert()
 * @arg
 * pObj QObject* [In] 需要进行数据库操作的对象，需要继承与QObject
 * tableName [In] const QString& 表名
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool BaseDao::Insert(QObject *pObj, const QString &tableName)
{
    QStringList excludeList("objectName");
    QStringList inFields = getAvaProperties(pObj->metaObject(), excludeList);
    return Insert(pObj, tableName, inFields);
}

/*
 * @brief
 * 插入制定的属性
 * @name Insert
 * @arg
 * pObj QObject* [In] 需要进行数据库操作的对象，需要继承与QObject
 * tableName [In] const QString& 表名
 * inFields [In] const QStringList& 插入的属性信息列表
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */

bool BaseDao::Insert(QObject *pObj, const QString &tableName, const QStringList &inFields)
{
    QString sql = QString(" insert into %1(").arg(tableName);
    QString joins = inFields.join(",");
    sql += joins + ") values (";
    sql += makeQuestionMarkList(inFields.size());
    sql += ")";
    DB_BEGIN(Insert);

    QSqlQuery query( *(GLobal_DB) );
    query.prepare(sql);
    for (int i = 0; i < inFields.size(); ++i)
    {
        //ID外键
        if (inFields[i].indexOf("_ID", 0, Qt::CaseInsensitive)
                && pObj->property(inFields[i].toStdString().c_str()).toInt() == -1) {
            query.bindValue(i, QVariant());
        } else {
            query.bindValue(i, pObj->property(inFields[i].toStdString().c_str()));
        }
    }

    bool ret = query.exec();
    if (!ret)
    {
        qDebug() << query.lastError().text();
    }
    DB_END();
    return ret;
}

/*
 * @brief
 * 更新制定的属性
 * @name Update
 * @arg
 * pObj QObject* [In] 需要进行数据库操作的对象，需要继承与QObject
 * tableName [In] const QString& 表名
 * conditions [In] const QStringLis& 条件
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */

bool BaseDao::Update(QObject *pObj, const QString &tableName, const QStringList &conditions)
{
    QStringList excludeList("objectName");
    excludeList.append(conditions);
    QStringList updateFields = getAvaProperties(pObj->metaObject(), excludeList);
    return Update(pObj, tableName, updateFields, conditions);
}

/*
 * @brief
 * 更新制定的属性
 * @name Update
 * @arg
 * pObj QObject* [In] 需要进行数据库操作的对象，需要继承与QObject
 * tableName [In] const QString& 表名
 * updateFields [In] const QStringList& 更新属性信息列表
 * conditions [In] const QStringLis& 条件
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */

bool BaseDao::Update(QObject *pObj, const QString &tableName, const QStringList &updateFields, const QStringList &conditions)
{
    QString sql = QString(" update %1 set ").arg(tableName);
    int nSize = updateFields.size();
    for (int i = 0; i < nSize; ++i)
    {
        if (i != nSize - 1) {
            sql += updateFields[i] + " = ?, ";
        } else {
            sql += updateFields[i] + " = ? ";
        }
    }

    sql += " where 1 = 1";
    for (int i = 0; i < conditions.size(); ++i)
    {
        sql += " and " + conditions[i] + " =? ";
    }

    DB_BEGIN(Update);

    QSqlQuery query( *(GLobal_DB) );
    query.prepare(sql);
    int nIdx = 0;
    for (int i = 0; i < nSize; ++i)
    {
        QVariant variant = pObj->property(updateFields[i].toStdString().c_str());
        if (updateFields[i].indexOf("_ID", 0, Qt::CaseInsensitive)
                || updateFields[i].indexOf("locker", 0, Qt::CaseInsensitive)) {
            int tmp = pObj->property(updateFields[i].toStdString().c_str()).toInt();
            if (tmp == -1)
                variant = QVariant();
        }
        query.bindValue(nIdx++, variant);
    }

    for (int i = 0; i < conditions.size(); ++i)
    {
        QVariant variant = pObj->property(conditions[i].toStdString().c_str());
        if (conditions[i].indexOf("_ID", 0, Qt::CaseInsensitive)) {
            int tmp = pObj->property(conditions[i].toStdString().c_str()).toInt();
            if (tmp == -1)
                variant = QVariant("NULL");
        }
        query.bindValue(nIdx++, variant);
    }

    bool ret = query.exec();
    QString exedState = ret? "SUCCESS" : "**FAILURE**";
    qDebug() << "[DATABASE][*UPDATE*][CLASSNAME:" << pObj->metaObject()->className() << "]"
                << "[TABLENAME:" << tableName << "]" << "EXECUTEDSTATE:" << exedState << "]";
    if (!ret)
        qDebug() << query.lastError().text();
    DB_END();
    return ret;
}

/*
 * @brief
 * 删除满足条件的属性
 * @name Delete
 * @arg
 * pObj QObject* [In] 需要进行数据库操作的对象，需要继承与QObject
 * tableName [In] const QString& 表名
 * conditions [In] const QStringLis& 条件
 * @return bool
 * true 执行成功
 * false 执行失败
 * @remark
 * 本函数只是为只有一个条件做准备的
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */

bool BaseDao::Delete(QObject *pObj, const QString &tableName, const QString &condition)
{
    QStringList conditions(condition);
    return Delete(pObj, tableName, conditions);
}

/*
 * @brief
 * 删除满足条件的属性
 * @name Delete
 * @arg
 * pObj QObject* [In] 需要进行数据库操作的对象，需要继承与QObject
 * tableName [In] const QString& 表名
 * conditions [In] const QStringLis& 条件
 * @return bool
 * true 执行成功
 * false 执行失败
 * @remark
 * 本函数支持多条件拼接
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */

bool BaseDao::Delete(QObject *pObj, const QString &tableName, const QStringList &conditions)
{
    QString sql = QString(" delete from %1 where 1 = 1 ").arg(tableName);
    foreach (QString item, conditions) {
        sql += " and " + item + " = ? ";
    }
    DB_BEGIN(Delete);

    QSqlQuery query(*(GLobal_DB));
    query.prepare(sql);
    for (int i = 0; i < conditions.size(); ++i)
    {
        query.bindValue(i, pObj->property(conditions[i].toStdString().c_str()));
    }

    bool ret = query.exec();
    QString exedState = ret? "SUCCESS" : "**FAILURE**";
    if (!ret)
        qDebug() << query.lastError().text();
    else
        qDebug() << "[DATABASE][*DELETE*][CLASSNAME:" << pObj->metaObject()->className()
                    << "]" << "[TABLENAME:" << tableName << "]" << "[EXECUTEDSTATE:" << exedState <<"]";
    DB_END();
    return ret;
}

/*
 * @brief
 * 查询满足条件的数据
 * @name Select
 * @arg
 * pObj QObject* [In] 需要进行数据库操作的对象，需要继承与QObject
 * tableName     [In] const QString& 表名
 * outFields     [In] const QStringList& outFields 要查询输出的信息
 * conditions     [In] const QStringList& 条件
 * @return QRetVec
 * 返回查询的信息
 * @remark
 * 本函数仅支持多个条件的查询
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 */
QRetVec BaseDao::Select(QObject *pObj, const QString &tableName,
                        const QStringList &outFields, const QStringList &conditions)
{
    QRetVec ret;
    Q_ASSERT(outFields.size() != 0);
    QString sql("select ");
    int nSize = outFields.size();
    for (int i = 0; i < nSize; ++i)
    {
        if (i != nSize - 1)
        {
            sql += outFields[i] + ",";
        } else {
            sql += outFields[i];
        }
    }
    sql += QString(" from %1 where 1 = 1").arg(tableName);
    int nCnt = conditions.size();
    for (int i = 0; i < nCnt; ++i)
    {
        sql += " and " + conditions[i] + " = ? ";
    }

    DB_BEGIN(Select);

    QSqlQuery query( (*GLobal_DB) );
    query.prepare(sql);
    for (int i = 0; i < nCnt; ++i)
    {
        query.bindValue(i, pObj->property( conditions[i].toStdString().c_str() ) );
    }

    if (query.exec())
    {
        while (query.next()) {
            QVector< CPair > oneRet(outFields.size());
            for (int i = 0; i < outFields.size(); ++i)
            {
                int idx = query.record().indexOf( outFields[i] );
                oneRet[i] = CPair( outFields[i], query.value(idx));
            }
            ret.append(oneRet);
        }
    }

    DB_END();
    return ret;
}

/*
 * @brief
 * 查询满足条件的数据
 * @name Select
 * @arg
 * pObj QObject* [In] 需要进行数据库操作的对象，需要继承与QObject
 * tableName     [In] const QString& 表名
 * condition     [In] const QString& 条件
 * @return QRetVec
 * 返回查询的信息
 * @remark
 * 本函数仅支持一个条件的查询
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 */
QRetVec BaseDao::Select(QObject *pObj, const QString &tableName, const QString &condition)
{
    QStringList conditions(condition);
    return Select(pObj, tableName, conditions);
}

/*
 * @brief
 * 查询满足条件的数据
 * @name Select
 * @arg
 * pObj QObject* [In] 需要进行数据库操作的对象，需要继承与QObject
 * tableName     [In] const QString& 表名
 * conditions     [In] const QStringList& 条件
 * @return QRetVec
 * 返回查询的信息
 * @remark
 * 本函数仅支持多个条件的查询
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 */
QRetVec BaseDao::Select(QObject *pObj, const QString &tableName, const QStringList &conditions)
{
    QStringList excludeList("objectName");
    QStringList outFields = getAvaProperties( pObj->metaObject(), excludeList );
    return Select(pObj, tableName, outFields, conditions);
}


/*
 * @brief
 * 查询满足条件的数据
 * @name Select
 * @arg
 * pObj QObject* [In] 需要进行数据库操作的对象，需要继承与QObject
 * tableName     [In] const QString& 表名
 * outFields     [In] const QStringList &outFields 要查询输出的信息
 * condition     [In] const QString& 条件
 * @return QRetVec
 * 返回查询的信息
 * @remark
 * 本函数仅支持多个条件的查询
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 */
QRetVec BaseDao::Select(QObject *pObj, const QString &tableName,
                        const QStringList &outFields, const QString &condition)
{
    QStringList conditions(condition);
    return Select(pObj, tableName, outFields, conditions);
}

/*
 * @brief
 * 执行sql语句，进行增删改操作
 * @name callADUSql
 * @arg
 * pObj QObject*            [In] 操作的对象
 * sql const QString&       [In] 待执行的sql语句
 * fields const QStringList [In] 对应于sql语句中需要填充的?字段
 * @return QRetVec
 * 需要注意本函数仅能处理曾删改操作
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 */
bool BaseDao::callADUSql(QObject *pObj, const QString &sql, const QStringList &fields)
{
    DB_BEGIN(callADUSql);
    QSqlQuery query( *(GLobal_DB) );
    query.prepare(sql);

    for (int i = 0; i < fields.size(); ++i)
    {
        if (fields[i].indexOf("_ID", 0, Qt::CaseInsensitive)
                && pObj->property(fields[i].toStdString().c_str()).toInt() == -1) {
            query.bindValue(i, QVariant());
        } else {
            query.bindValue(i, pObj->property(fields[i].toStdString().c_str()) );
        }
    }

    bool ret = query.exec();

    DB_END();
    return ret;
}

/*
 * @brief
 * 执行sql语句，进行查询操作
 * @name callSelectSql
 * @arg
 * pObj QObject*            [In] 操作的对象
 * sql const QString&       [In] 待执行的sql语句
 * inFields const QStringList [In] 输入字段
 * outFields const QStringList [In]输出字段
 * @return QRetVec
 * 需要注意本函数仅能处理查询操作
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 */
QRetVec BaseDao::callSelectSql(QObject *pObj, const QString &sql,
                            const QStringList &inFields, const QStringList &outFields)
{
    DB_BEGIN(callSelectSql);
    QSqlQuery query( *(GLobal_DB) );
    query.prepare(sql);

    int idx = 0;
    for (int i = 0; i < inFields.size(); ++i)
    {
        query.bindValue(idx++, pObj->property(inFields[i].toStdString().c_str()) );
    }

    for (int i = 0; i < outFields.size(); ++i)
    {
        query.bindValue(idx++, pObj->property(outFields[i].toStdString().c_str()) );
    }

    QRetVec ret;
    if (query.exec())
    {
        while (query.next())
        {
            QVector<CPair> oneRet;
            foreach (QString field, outFields) {
                int idx = query.record().indexOf(field);
                oneRet.append( CPair (field, query.value(idx) ) );
            }
            ret.append(oneRet);
        }
    }
    DB_END();
    return ret;
}

/*
 * @brief
 * 执行sql语句
 * @name callSql
 * @arg
 * sql const QString&       [In] 待执行的sql语句
 *
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 */
QVariant BaseDao::callSql(const QString &sql)
{
    DB_BEGIN(callSql);
    QSqlQuery query( (*GLobal_DB) );
    if (!query.prepare(sql))
    {
        qDebug() << query.lastError().text();
        return -1;
    }
    if (query.exec())
    {
        if (query.next()) {
            return query.value(0);
        }
        return -1;
    } else {
        qDebug() << query.lastError().text();
    }

    DB_END();
    return -1;
}

QVariant BaseDao::callSql(const QString &sql, QList<QVariant> conditions)
{
    DB_BEGIN(callSql);
    QSqlQuery query( (*GLobal_DB) );
    query.prepare(sql);

    for (int i = 0; i < conditions.size(); ++i)
    {
        query.bindValue(i, conditions[i]);
    }

    if (query.exec())
    {
        while (query.next()) {
            return query.value(0);
        }
    }
    DB_END();
    return -1;
}

/*
 * @brief
 * 执行存储过程，自定义输入输出参数
 * @name callProc
 * @arg
 * proc_name                [In] const QString& 存储过程名字
 * inFields                 [In] QList<QVariant> & 需要输入的信息
 * outFields                [In] QList<QVariant> & 需要输出的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email: 12281116@bjtu.edu.cn
 */
bool BaseDao::callProc(const QString &proc_name, QList<QVariant> &inFields,
                       QList<QVariant> &outFields, bool isOutputDebug)
{
    QString sql = QString("call %1 (").arg(proc_name);
    sql += makeQuestionMarkList(inFields.size() + outFields.size());
    sql += ")";

    DB_BEGIN(call_proc);
    QSqlQuery query( (*GLobal_DB) );
    query.prepare(sql);

    int idx = 0;
    for (int i = 0; i < inFields.size(); ++i)
    {
        QVariant var = inFields[i];

        if (var.type() == QVariant::Double) {
            float tmp = var.toDouble();
            query.bindValue(idx++, tmp);
        } else {
            query.bindValue(idx++, var);
        }
    }

    for (int i = 0; i < outFields.size(); ++i)
    {
        query.bindValue(idx++, QSql::Out);
    }

    bool ret = query.exec();
    if (ret)
    {
        idx = idx - outFields.size();
        for (int i = 0; i < outFields.size(); ++i)
        {
            outFields[i] = query.boundValue(idx + i);
        }
    } else {
        if (isOutputDebug) {
            qDebug() << "[DATABASE][*INSERT*][PROC_NAME: " << proc_name << "]ERROR: "
                     << query.lastError().text() << "\n";
        }
    }

    DB_END();
    return ret;
}

/*
 * @brief
 * 根据需要创建问号的个数，输出由逗号分隔的字符串
 * @name makeQuestionMarkList(int nSize)
 * @arg
 * nSize int [In] 输入问号的数量
 * @return QString
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
QString BaseDao::makeQuestionMarkList(int nSize)
{
    QString ret = "";
    for(int i = 0; i < nSize; ++i)
    {
        if (i != nSize - 1)
            ret += "?,";
        else
            ret += "?";
    }
    return ret;
}


/*
 * @brief
 * 通过反射得到反射表中的属性
 * @name getProperties
 * @arg
 * pMeta const QMetaObject* 元对象
 * @return QStringList
 * 返回列表属性
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
QStringList BaseDao::getProperties(const QMetaObject *pMeta)
{
    Q_ASSERT(pMeta != NULL);

    QStringList retList;
    int properyCnt = pMeta->propertyCount();
    for (int idx = 0; idx < properyCnt; ++idx)
    {
        retList.append(pMeta->property(idx).name());
    }
    return retList;
}

QStringList BaseDao::getAvaProperties(const QMetaObject *pMeta, const QStringList &excludes)
{
    Q_ASSERT(pMeta != NULL);

    QStringList retList;
    int properyCnt = pMeta->propertyCount();
    for (int idx = 0; idx < properyCnt; ++idx)
    {
        QString name = pMeta->property(idx).name();
        if (excludes.contains(name))
            continue;
        retList.append(name);
    }
    return retList;
}

int BaseDao::getId(QString &tableName, QString &outFields)
{
    QString sql = "select max(" + outFields + ") from " + tableName;

    DB_BEGIN(getId())
    QSqlQuery query(*GLobal_DB);
    query.prepare(sql);
    int id;
    bool flags = query.exec();
    if (flags)
    {
        if (!query.next()) {
            QMessageBox::warning(0, "错误", "失败", "确定");
        } else {
            id = query.value(0).toInt();
        }
    }
    DB_END();
    return id;
}
