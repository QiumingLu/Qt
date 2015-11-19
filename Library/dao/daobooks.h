#ifndef DAOBOOKS_H
#define DAOBOOKS_H

#include "basedao.h"
#include <QVector>

class Books;
class UniqueBook;
class DaoBooks : public BaseDao
{
public:
    DaoBooks();

    bool Add(Books *pObj);
    bool Delete(Books *pObj);
    bool Update(Books *pObj);
    QVector<Books*> Select(Books *pObj, int cond);
    QVector<Books*> SelectByCond(Books *pObj, const QString &conditions);
    QList<UniqueBook*> findUniqueBook();
    QVector<Books*> findBook(const QString &inputBook);

private:
    QList<UniqueBook*> uniqueBookList;
    QVector<Books*> findBookVec;
};

#endif // DAOBOOKS_H
