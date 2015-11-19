#ifndef DAOMEMBERLEVEL_H
#define DAOMEMBERLEVEL_H

#include "basedao.h"

class MemberLevel;
class DaoMemberLevel : public BaseDao
{
public:
    DaoMemberLevel();

    bool Add(MemberLevel *pObj);
    bool Delete(MemberLevel *pObj);
    bool Update(MemberLevel *pObj);
    QVector<MemberLevel*> Select(MemberLevel *pObj, int cond);
};

#endif // DAOMEMBERLEVEL_H
