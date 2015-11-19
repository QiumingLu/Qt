/*
 * @Author: QiumingLu
 * @Date: 2014.11.22
 */
#ifndef USER_H
#define USER_H

#include <QObject>
#include <QDate>

class User : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int USER_ID READ getUserID WRITE setUserID)
    Q_PROPERTY(QString USER_CODE READ getUserCode WRITE setUserCode)
    Q_PROPERTY(QString USER_NAME READ getUserName WRITE setUserName)
    Q_PROPERTY(QString USER_PSW READ getUserPsw WRITE setUserPsw)
    Q_PROPERTY(unsigned SEX READ getSex WRITE setSex)
    Q_PROPERTY(QString BIRTHDAY READ getBirthDay WRITE setBirthDay)
    Q_PROPERTY(QString PHONE READ getPhone WRITE setPhone)
    Q_PROPERTY(QString MOBILE READ getMobile WRITE setMobile)
    Q_PROPERTY(QString MAIL READ getMail WRITE setMail)
    Q_PROPERTY(int USER_TYPE READ getUserType WRITE setUserType)
    Q_PROPERTY(QString USER_REMARK READ getUserRemark WRITE setUserRemark)
    Q_PROPERTY(QDateTime USER_LASTLOGTIME READ getUserLastLogTime WRITE setUserLastLogTime)
    Q_PROPERTY(QDateTime USER_CREATETIME READ getUserCreateTime WRITE setUserCreateTime)

public:
    explicit User();
    virtual ~User();

//    User(const User &);
//    User &operator =(const User &);

    int getUserID() const;
    void setUserID(int);

    QString getUserCode() const;
    void setUserCode(const QString &);

    QString getUserName() const;
    void setUserName(const QString &);

    QString getUserPsw() const;
    void setUserPsw(const QString &);

    unsigned getSex() const;
    void setSex(unsigned);

    QString getBirthDay() const;
    void setBirthDay(const QString &);

    QString getPhone() const;
    void setPhone(const QString &);

    QString getMobile() const;
    void setMobile(const QString &);

    QString getMail() const;
    void setMail(const QString &);

    int getUserType() const;
    void setUserType(int);

    QString getUserRemark() const;
    void setUserRemark(const QString &);

    QDateTime getUserLastLogTime() const;
    void setUserLastLogTime(const QDateTime &);

    QDateTime getUserCreateTime() const;
    void setUserCreateTime(const QDateTime &);


private:
    int userID;
    QString userCode;
    QString userName;
    QString userPsw;
    unsigned sex;
    QString birthday;
    QString phone;
    QString mobile;
    QString mail;
    int userType;
    QString userRemark;
    QDateTime lastLogTime;
    QDateTime createTime;

};

#endif // USER_H
