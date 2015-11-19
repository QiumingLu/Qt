#ifndef DAOUSERTYPE_H
#define DAOUSERTYPE_H

#include "basedao.h"

class UserType;
class DaoUserType : public BaseDao
{
public:
    DaoUserType();

    bool Add(UserType *pObj);
    bool Delete(UserType *pObj);
    bool Update(UserType *pObj);
    QVector<UserType*> Select(UserType *pObj, int cond);
};

#endif // DAOUSERTYPE_H
