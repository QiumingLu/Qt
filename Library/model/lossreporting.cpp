#include "lossreporting.h"

LossReporting::LossReporting()
{
}

LossReporting::~LossReporting()
{
}

int LossReporting::getId() const
{
    return this->id;
}

void LossReporting::setId(int id)
{
    this->id = id;
}

int LossReporting::getReaderId() const
{
    return this->readerId;
}

void LossReporting::setReaderId(int readerId)
{
    this->readerId = readerId;
}

QDateTime LossReporting::getLossDate() const
{
    return this->lossDate;
}

void LossReporting::setLossDate(const QDateTime &lossDate)
{
    this->lossDate = lossDate;
}

QString LossReporting::getRemark() const
{
    return this->remark;
}

void LossReporting::setRemark(const QString &remark)
{
    this->remark = remark;
}
