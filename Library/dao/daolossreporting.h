#ifndef DAOLOSSREPORTING_H
#define DAOLOSSREPORTING_H

#include "basedao.h"

class LossReporting;
class DaoLossReporting : public BaseDao
{
public:
    DaoLossReporting();

    bool Add(LossReporting *pObj);
    bool Delete(LossReporting *pObj);
    bool Update(LossReporting *pObj);
    QVector<LossReporting*> Select(LossReporting *pObj, int cond);
};

#endif // DAOLOSSREPORTING_H
