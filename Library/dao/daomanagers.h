#ifndef DAOMANAGERS_H
#define DAOMANAGERS_H

#include "basedao.h"
#include <QVector>

class Managers;
class DaoManagers : public BaseDao
{
public:
    DaoManagers();

    bool Add(Managers *pObj);
    bool Delete(Managers *pObj);
    bool Update(Managers *pObj);
    QVector<Managers*> Select(Managers *pObj, int cond);
};

#endif // DAOMANAGERS_H
