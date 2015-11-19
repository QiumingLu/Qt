#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include "ui/uilogon.h"
#include "ui/uiuserlibrary.h"
#include "model/sysenviroment.h"
#include "model/user.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(QDir::currentPath() + "/Library.qss");
    bool flag = file.open(QFile::ReadOnly);
    if (flag)
    {
        a.setStyleSheet(QLatin1String(file.readAll()));
        file.close();
    }

    UILogon *logonUI = new UILogon();
    logonUI->setObjectName(QString("LibraryLogon"));
    int ret = logonUI->exec();
    MainWindow *managerLibrary;
    UIUserLibrary *userLibrary;
    if (ret == QDialog::Accepted)
    {
        UILogon::updateLastTime();
        if (SysEnviroment::getInstance()->getUser()->getUserType() == 3) {
            userLibrary = new UIUserLibrary();
            userLibrary->show();
        } else {
            managerLibrary = new MainWindow();
            managerLibrary->show();
        }
    }

    return a.exec();
}
