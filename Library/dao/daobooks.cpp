#include "daobooks.h"
#include <QStringList>
#include <QVector>
#include "DaoHeader.h"
#include "model/books.h"
#include "core/systype.h"

DaoBooks::DaoBooks()
{
}

/*
 * @brief
 * 本函数实现向数据库中存放Books的信息
 * @name Add
 * @arg
 * pObj QObject* ：@class Books*, 需要添加到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoBooks::Add(Books *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList outFields("BOOK_ID");   //primary key
    return call_proc(pObj, "BOOKS_INSERT_PROC", outFields);
}

/*
 * @brief
 * 本函数实现向数据库中删除Books的信息
 * @name Delete
 * @arg
 * pObj QObject* ：@class Books*, 需要删除到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */

bool DaoBooks::Delete(Books *pObj)
{
    Q_ASSERT(pObj != NULL);
    return BaseDao::Delete(pObj, "BOOKS", "BOOK_ID");
}

/*
 * @brief
 * 本函数实现向数据库中更新Books的信息
 * @name Delete
 * @arg
 * pObj QObject* ：@class Books*, 需要更新到数据库的信息
 * @return bool
 * true 执行成功
 * false 执行失败
 * @author
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
bool DaoBooks::Update(Books *pObj)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions("BOOK_ID");  //primary key
    return BaseDao::Update(pObj, "BOOKS", conditions);
}

/*
 * @brief
 * 本函数实现向数据库中查询Books的信息
 * @name Select
 * @arg
 * pObj QObject* ：@class Books*, 需要查询到数据库的信息
 * @return
 * QVector<Books*>
 * @author
 * QiumingLu Email:cming_cs@163.com
 * @test
 * no
 */
QVector<Books*> DaoBooks::Select(Books *pObj, int cond)
{
    Q_ASSERT(pObj != NULL);
    QStringList conditions;
    if (cond > 0)
    {
        if (cond & COND_ID)
        {
            conditions.append("BOOK_ID");
        }
        if (cond & COND_NICKNAME)
        {
            conditions.append("BOOK_CODE");
        }
        if (cond & COND_NAME)
        {
            conditions.append("BOOK_NAME");
        }
        if (cond & COND_TYPE_ID)
        {
            conditions.append("CATEGORY_ID");
        }
    }
    QRetVec retVec = BaseDao::Select(pObj, "BOOKS",conditions);
    QVector<Books*> ret(retVec.size());
    for (int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new Books();
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

QVector<Books*> DaoBooks::SelectByCond(Books *pObj, const QString &conditions)
{
    Q_ASSERT(pObj != NULL);

    QStringList inFields;
    inFields.append("BOOK_NAME");
    inFields.append("AUTHOR");
    inFields.append("PUBLISHING");

    QStringList outFields;
    outFields.append("BOOK_ID");
    outFields.append("BOOK_NAME");
    outFields.append("AUTHOR");
    outFields.append("PUBLISHING");
    outFields.append("CATEGORY_ID");
    outFields.append("PRICE");
    outFields.append("DATE_IN");
    outFields.append("QUANTITY_IN");
    outFields.append("QUANTITY_OUT");
    outFields.append("QUANTITY");

    QString sql = QString("select * from BOOKS where %1").arg(inFields.at(0));
    sql = sql + " like '%" + conditions + "%'";
    sql = sql + " or " + QString("%1").arg(inFields.at(1));
    sql = sql + " like '%" + conditions + "%'";
    sql = sql + " or " + QString("%1").arg(inFields.at(2));
    sql = sql + " like '%" + conditions + "%'";

    QRetVec retVec = BaseDao::callSelectSql(pObj, sql, inFields, outFields);
    QVector<Books*> ret(retVec.size());
    for (int i = 0; i < retVec.size(); ++i)
    {
        ret[i] = new Books();
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

QVector<Books*> DaoBooks::findBook(const QString &inputBook)
{
    QStringList inputBookList;
    if (inputBook == "")
    {
        return this->findBookVec;
    } else {
        inputBookList = inputBook.split(QRegExp("\\W+"), QString::SkipEmptyParts);
    }

    Books books;
    foreach(QString s, inputBookList)
    {
         QVector<Books*> bookVec = this->SelectByCond(&books, s);
         this->findBookVec += bookVec;
    }
    return this->findBookVec;
}

QList<UniqueBook*> DaoBooks::findUniqueBook()
{
    foreach(Books* book, findBookVec)
    {
        QVector<UniqueBook*> uniqueBookVec = SYSTYPE->getUniqueBookByBookId(book->getBookId());
        foreach (UniqueBook *uniqueBook, uniqueBookVec)
        {
            this->uniqueBookList.push_back(uniqueBook);
        }
    }

    return uniqueBookList;
}
