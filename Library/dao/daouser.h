#ifndef DAOUSER_H
#define DAOUSER_H

#include "basedao.h"

class User;
class DaoUser : public BaseDao
{
public:
    DaoUser();

    bool Add(User *pObj);
    bool Delete(User *pObj);
    bool Update(User *pObj);
    QVector<User*> Select(User *pObj, int cond);
};

#endif // DAOUSER_H
