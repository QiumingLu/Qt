#ifndef DAOBORROW_H
#define DAOBORROW_H

#include "basedao.h"

class Borrow;
class DaoBorrow : public BaseDao
{
public:
    DaoBorrow();

    bool Add(Borrow *pObj);
    bool Delete(Borrow *pObj);
    bool Update(Borrow *pObj);
    QVector<Borrow*> Select(Borrow *pObj, int cond);
};

#endif // DAOBORROW_H
