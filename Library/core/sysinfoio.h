#ifndef SYSINFOIO_H
#define SYSINFOIO_H

#include <QList>

class User;
class SysInfoIO
{
public:
    SysInfoIO();

    static QList<User*> readfromfileforUser();
    static bool writetofileforUser(QList<User *> listUser);
};

#endif // SYSINFOIO_H
