/*
 * @Author: QiumingLu
 * @Date: 2014.11.22
 */
#ifndef USERTYPE_H
#define USERTYPE_H

#include <QObject>

class UserType : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int USER_TYPE_ID READ getUserTypeId WRITE setUserTypeId)
    Q_PROPERTY(QString USER_TYPE_NAME READ getUserTypeName WRITE setUserTypeName)

public:
    UserType();
    ~UserType();

    int getUserTypeId() const;
    void setUserTypeId(int);

    QString getUserTypeName() const;
    void setUserTypeName(const QString&);

private:
    int userTypeId;
    QString userTypeName;
};

#endif // USERTYPE_H
