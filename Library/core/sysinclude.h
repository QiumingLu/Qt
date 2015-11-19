#ifndef SYSINCLUDE_H
#define SYSINCLUDE_H

#include <QString>

const QString userpath = "/sysinfo/user.xml";
#define UserPath userpath
#define SAFE_DELETE(pObj) if(pObj != NULL){delete(pObj); pObj = NULL;}
#define STRING_ABNORMITY "#"  //字符串异常值定义

namespace sysinclude {
enum sex
{
    male = 0,        //性别:男
    female = 1,      //性别:女
    other = 2       //性别:保密
};

enum userType
{
    superAdmin = 1,  //超级管理员
    admin = 2,       //普通管理员
    reader = 3       //读者
};

enum cardLevel
{
    goldCard = 1,   //金卡，级别为1
    selverCard = 2  //银卡，级别为2
};

enum cardDay
{
    goldDay = 60,
    selverDay = 30
};

enum BookEnum
{
    GRAP = 2,    //控件四周间隙，可更改
    WIDTH = 260 + 2*GRAP, //+ 2*GRAP不能更改，只能改前面的数字。
    HEIGHT = 380 + 2*GRAP,
    COUNT = 1,
    MyLibrary = 0,
    BookBox = 1
};

enum Loss
{
    yesLoss = 1,
    noLoss = 0
};

enum Borrow
{
    yesBorrow = 1,
    noBorrow = 0
};
}

#endif // SYSINCLUDE_H
