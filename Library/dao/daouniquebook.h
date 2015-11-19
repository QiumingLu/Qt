#ifndef DAOUNIQUEBOOK_H
#define DAOUNIQUEBOOK_H

#include "dao/basedao.h"

class UniqueBook;
class DaoUniqueBook : public BaseDao
{
public:
    DaoUniqueBook();

    bool Add(UniqueBook *pObj);
    bool Delete(UniqueBook *pObj);
    bool Update(UniqueBook *pObj);
    QVector<UniqueBook*> Select(UniqueBook *pObj, int cond);
};

#endif // DAOUNIQUEBOOK_H
