#include "memberlevel.h"

MemberLevel::MemberLevel()
{
}

MemberLevel::~MemberLevel()
{
}

int MemberLevel::getLevelId() const
{
    return this->levelId;
}

void MemberLevel::setLevelId(int levelId)
{
    this->levelId = levelId;
}

QString MemberLevel::getLevelName() const
{
    return this->levelName;
}

void MemberLevel::setLevelName(const QString &levelName)
{
    this->levelName = levelName;
}

int MemberLevel::getDays() const
{
    return this->days;
}

void MemberLevel::setDays(int days)
{
    this->days = days;
}

int MemberLevel::getNumbers() const
{
    return this->numbers;
}

void MemberLevel::setNumbers(int numbers)
{
    this->numbers = numbers;
}

double MemberLevel::getFee() const
{
    return this->fee;
}

void MemberLevel::setFee(double fee)
{
    this->fee = fee;
}
