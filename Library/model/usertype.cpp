#include "usertype.h"

UserType::UserType()
{
}

UserType::~UserType()
{
}

int UserType::getUserTypeId() const
{
    return this->userTypeId;
}

void UserType::setUserTypeId(int userTypeId)
{
    this->userTypeId = userTypeId;
}

QString UserType::getUserTypeName() const
{
    return this->userTypeName;
}

void UserType::setUserTypeName(const QString &userTypeName)
{
    this->userTypeName = userTypeName;
}
