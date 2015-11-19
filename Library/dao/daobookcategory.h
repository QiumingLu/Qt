#ifndef DAOBOOKCATEGORY_H
#define DAOBOOKCATEGORY_H

#include "basedao.h"

class BookCateGory;
class DaoBookCateGory : public BaseDao
{
public:
    DaoBookCateGory();

    bool Add(BookCateGory *pObj);
    bool Delete(BookCateGory *pObj);
    bool Update(BookCateGory *pObj);
    QVector<BookCateGory*> Select(BookCateGory *pObj, int cond);
};

#endif // DAOBOOKCATEGORY_H
