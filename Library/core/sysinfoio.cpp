#include "sysinfoio.h"
#include <QDir>
#include <QFile>
#include <QDomDocument>
#include <QDomNode>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>
#include "sysinclude.h"
#include "model/usertype.h"
#include "model/user.h"

SysInfoIO::SysInfoIO()
{
}

QList<User*> SysInfoIO::readfromfileforUser()
{
    QString filepath = QDir::currentPath() + UserPath;
    QFile file(filepath);
    QDomDocument doc;
    bool flag = doc.setContent(&file, false);
    if(!flag) {
        qDebug() << "error";
    }

    QList<User*> users;

    QDomElement root = doc.documentElement();
    QDomNodeList nodelist = root.childNodes();

    for (int i = 0; i < nodelist.count(); ++i)
    {
        QDomNode node = nodelist.at(i);
        QDomElement nodeuser = node.toElement();

        User *user = new User();

        QString userCode = nodeuser.elementsByTagName("UserCode").at(0).toElement().attribute("value");
        QString password = nodeuser.elementsByTagName("Psw").at(0).toElement().attribute("value");
        int userType = nodeuser.elementsByTagName("UserType").at(0).toElement().attribute("value").toInt();

        user->setUserCode(userCode);
        user->setUserPsw(password);
        user->setUserType(userType);

        users.append(user);
    }
    return users;
}

/*
 * 把user信息写到相应的xml文件中
 */
bool SysInfoIO::writetofileforUser(QList<User *> listUser)
{
    QString filepath = QDir::currentPath() + UserPath;
    QFile file(filepath);

    if (!file.exists()) {
        if (file.open(QIODevice::ReadWrite)) {
            file.close();
        }
    }

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return false;
    }

    file.flush();

    QDomDocument doc;
    QDomNode xmlNode = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(xmlNode);
    QDomNode root = doc.createElement("Root");

    foreach (User *tmp, listUser) {
        QString userCode = tmp->getUserCode();
        QString password = tmp->getUserPsw();
        int userType = tmp->getUserType();

        QDomElement user = doc.createElement("User");

        QDomElement xmlname = doc.createElement("UserCode");
        xmlname.setAttribute("value", userCode);
        user.appendChild(xmlname);

        QDomElement xmlpasswor = doc.createElement("Psw");
        xmlpasswor.setAttribute("value", password);
        user.appendChild(xmlpasswor);

        QDomElement xmlusertype = doc.createElement("UserType");
        xmlusertype.setAttribute("value", QString::number(userType));
        user.appendChild(xmlusertype);

        root.appendChild(user);
    }

    doc.appendChild(root);

    QTextStream out(&file);
    out.setCodec(QTextCodec::codecForName("UTF-8"));

    int indent = 4;
    doc.save(out, indent);
    file.close();
    return true;
}
