#ifndef DAOREADERS_H
#define DAOREADERS_H

#include "basedao.h"

class Readers;
class DaoReaders : public BaseDao
{
public:
    DaoReaders();

    bool Add(Readers *pObj);
    bool Delete(Readers *pObj);
    bool Update(Readers *pObj);
    QVector<Readers*> Select(Readers *pObj, int cond);
};

#endif // DAOREADERS_H
