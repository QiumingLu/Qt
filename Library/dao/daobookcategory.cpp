#include "daobookcategory.h"
#include <QVector>
#include "DaoHeader.h"
#include "model/bookcategory.h"

DaoBookCateGory::DaoBookCateGory()
{
}

/*
 * @brief
 * 本函数实现向数据库中存放BookCategory的信息
 * @name Add
 * @arg
 * pObj QObject* :@class BookCateGory*, 需要添加到数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoBookCateGory::Add(BookCateGory *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList outFields("CATEGORY_ID");    //primary key
    return call_proc(pObj, "BOOK_CATEGORY_INSERT_PROC", outFields);
}

/*
 * @brief
 * 本函数实现向数据库中删除BookCategory的信息
 * @name Delete
 * @arg
 * pObj QObject* :@class BookCateGory*, 需要删除的数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */

bool DaoBookCateGory::Delete(BookCateGory *pObj)
{
    Q_ASSERT(pObj != NULL);
    return BaseDao::Delete(pObj, "BOOK_CATEGORY", "CATEGORY_ID");
}

/*
 * @brief
 * 本函数实现向数据库中更新BookCategory的信息
 * @name Update
 * @arg
 * pObj QObject* :@class BookCateGory*, 需要更新的数据库中的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */

bool DaoBookCateGory::Update(BookCateGory *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions("CATEGORY_ID");  //primary key
    return BaseDao::Update(pObj, "BOOK_CATEGORY", conditions);
}

/*
 * @brief
 * 本函数实现向数据库中查询BookCategory的信息
 * @name Select
 * @arg
 * pObj QObject* :@class BookCateGory*, 需要查询数据库中的信息
 * @return
 * QVector<BookCateGory*>
 * @auhotr
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
QVector<BookCateGory*> DaoBookCateGory::Select(BookCateGory *pObj, int cond)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions;
    if (cond > 0)
    {
        if (cond & COND_ID)
        {
            conditions.append("CATEGORY_ID");
        }
        if (cond & COND_NAME)
        {
            conditions.append("CATEGORY_NAME");
        }
    }

    QRetVec retVec = BaseDao::Select(pObj, "BOOK_CATEGORY", conditions);
    QVector<BookCateGory*> ret(retVec.size());

    for (int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new BookCateGory();
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
