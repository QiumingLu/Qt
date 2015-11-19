#include "user.h"

User::User()
{
}

User::~User()
{
}

/*
User::User(const User &user)
{
    this->userID = user.userID;
    this->userCode = user.userCode;
    this->userName = user.userName;
    this->userPsw = user.userPsw;
    this->sex = user.sex;
    this->birthday = user.birthday;
    this->phone = user.phone;
    this->mobile = user.mobile;
    this->mail = user.mail;
    this->userType = user.userType;
    this->userRemark = user.userRemark;
    this->lastLogTime = user.lastLogTime;
}

User& User::operator =(const User &user)
{
    if (this != &user)
    {
        this->userID = user.userID;
        this->userCode = user.userCode;
        this->userName = user.userName;
        this->userPsw = user.userPsw;
        this->sex = user.sex;
        this->birthday = user.birthday;
        this->phone = user.phone;
        this->mobile = user.mobile;
        this->mail = user.mail;
        this->userType = user.userType;
        this->userRemark = user.userRemark;
        this->lastLogTime = user.lastLogTime;
    }
    return *this;
}
*/

int User::getUserID() const
{
    return this->userID;
}

void User::setUserID(int userID)
{
    this->userID = userID;
}

QString User::getUserCode() const
{
    return this->userCode;
}

void User::setUserCode(const QString &userCode)
{
    this->userCode = userCode;
}

QString User::getUserName() const
{
    return this->userName;
}

void User::setUserName(const QString &userName)
{
    this->userName = userName;
}

QString User::getUserPsw() const
{
    return this->userPsw;
}

void User::setUserPsw(const QString &userPsw)
{
    this->userPsw = userPsw;
}

unsigned User::getSex() const
{
    return this->sex;
}

void User::setSex(unsigned sex)
{
    this->sex = sex;
}

QString User::getBirthDay() const
{
    return this->birthday;
}

void User::setBirthDay(const QString &birthday)
{
    this->birthday = birthday;
}

QString User::getPhone() const
{
    return this->phone;
}

void User::setPhone(const QString &phone)
{
    this->phone = phone;
}

QString User::getMobile() const
{
    return this->mobile;
}

void User::setMobile(const QString &mobile)
{
    this->mobile = mobile;
}

QString User::getMail() const
{
    return this->mail;
}

void User::setMail(const QString &mail)
{
    this->mail = mail;
}

int User::getUserType() const
{
    return this->userType;
}

void User::setUserType(int userType)
{
    this->userType = userType;
}

QString User::getUserRemark() const
{
    return this->userRemark;
}

void User::setUserRemark(const QString &userRemark)
{
    this->userRemark = userRemark;
}

QDateTime User::getUserLastLogTime() const
{
    return this->lastLogTime;
}

void User::setUserLastLogTime(const QDateTime &lastLogTime)
{
    this->lastLogTime = lastLogTime;
}

QDateTime User::getUserCreateTime() const
{
    return this->createTime;
}

void User::setUserCreateTime(const QDateTime &createTime)
{
    this->createTime = createTime;
}

