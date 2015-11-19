/*
 * @Author: QiumingLu
 * @Date: 2014.11.22
 */
#ifndef MANAGERS_H
#define MANAGERS_H

#include <QObject>
#include "user.h"

class Managers : public User
{
    Q_OBJECT

    Q_PROPERTY(int ID READ getId WRITE setId)
    Q_PROPERTY(int MANAGER_ID READ getManagerId WRITE setManagerId)

public:
    Managers();
    ~Managers();

    int getId() const;
    void setId(int);

    int getManagerId() const;
    void setManagerId(int);

private:
    int id;
    int managerId;
};

#endif // MANAGERS_H
