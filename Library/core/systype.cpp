#include "systype.h"
#include <QMessageBox>
#include "model/sysenviroment.h"
#include "dao/daouser.h"
#include "model/user.h"
#include "dao/daoreaders.h"
#include "model/readers.h"
#include "model/managers.h"
#include "dao/daomanagers.h"
#include "model/books.h"
#include "dao/daobooks.h"
#include "model/uniquebook.h"
#include "dao/daouniquebook.h"
#include "dao/daobookcategory.h"
#include "model/bookcategory.h"
#include "model/memberlevel.h"
#include "dao/daomemberlevel.h"
#include "dao/daoborrow.h"
#include "model/borrow.h"
#include "model/lossreporting.h"
#include "dao/daolossreporting.h"
#include "model/usertype.h"
#include "dao/daousertype.h"
#include "dao/DaoHeader.h"
#include "core/sysinclude.h"
#include <iterator>
#include "model/sysenviroment.h"

template <typename T>
class Clear {
public:
    static void clear(QMap<int, T*> &temp) {
        QMap<int, T*> clearMap = temp;

        typename QMap<int, T*>::iterator it;
        for(it = clearMap.begin(); it != clearMap.end(); )
        {
            SAFE_DELETE(it.value());
            clearMap.erase(it++);
        }
        clearMap.clear();
    }
};

SysType* SysType::pInstance = NULL;

SysType::SysType()
{
}

SysType::~SysType()
{
    cleanUp();
}

bool SysType::sysInit()
{
    GLobal_DB->open();
    if (SysEnviroment::getInstance()->getUser()->getUserType() != sysinclude::reader)
    {
        this->initUserInfo();
        this->initReaderInfo();
        this->initManagerInfo();
        this->initUserTypeInfo();
    }
    this->initBooksInfo();
    this->initUniqueBookInfo();
    this->initBookCateGoryInfo();
    this->initBorrowInfo();
    this->initMemberLevelInfo();
    this->initLossReportingInfo();
    GLobal_DB->close();
    return true;
}

bool SysType::update()
{
    return true;
}

bool SysType::cleanUp()
{
    if (SysEnviroment::getInstance()->getUser()->getUserType() != sysinclude::reader)
    {
        Clear<User>::clear(m_UserMap);
        Clear<Readers>::clear(m_ReaderMap);
        Clear<Managers>::clear(m_ManagerMap);
        Clear<UserType>::clear(m_UserTypeMap);
    }
    Clear<Books>::clear(m_BookMap);
    Clear<BookCateGory>::clear(m_BookCateGoryMap);
    Clear<Borrow>::clear(m_BorrowMap);
    Clear<MemberLevel>::clear(m_MemberLevelMap);
    Clear<LossReporting>::clear(m_LossReportingMap);
    return true;
}

QList<User*> SysType::getAllUser()
{
    return this->m_UserMap.values();
}

QList<Readers*> SysType::getAllReaders()
{
    return this->m_ReaderMap.values();
}

QList<Managers*> SysType::getAllManagers()
{
    return this->m_ManagerMap.values();
}

QList<UserType*> SysType::getAllUserType()
{
    return this->m_UserTypeMap.values();
}

QList<Books*> SysType::getAllBooks()
{
    return this->m_BookMap.values();
}

QList<UniqueBook*> SysType::getAllUniqueBook()
{
    return this->m_UniqueBookMap.values();
}

QList<BookCateGory*> SysType::getAllBookCateGory()
{
    return this->m_BookCateGoryMap.values();
}

QList<Borrow*> SysType::getAllBorrow()
{
    return this->m_BorrowMap.values();
}

QList<MemberLevel*> SysType::getAllMemberLevel()
{
    return this->m_MemberLevelMap.values();
}

User* SysType::getUser(int userId)
{
    QMap<int, User*>::const_iterator it = this->m_UserMap.find(userId);
    if (it != this->m_UserMap.end())
        return it.value();
    else
        return NULL;
}

User* SysType::getUserByCode(QString &userCode)
{
    QMap<QString, User*>::const_iterator it = this->m_UserCoreMap.find(userCode);
    if (it != this->m_UserCoreMap.end())
        return it.value();
    else
        return NULL;
}

Readers* SysType::getReader(int readerId)
{
    QMap<int, Readers*>::const_iterator it = this->m_ReaderMap.find(readerId);
    if (it != this->m_ReaderMap.end())
        return it.value();
    else
        return NULL;
}

Managers* SysType::getManager(int managerId)
{
    QMap<int, Managers*>::const_iterator it = this->m_ManagerMap.find(managerId);
    if (it != this->m_ManagerMap.end())
        return it.value();
    else
        return NULL;
}

Books* SysType::getBook(int bookId)
{
    QMap<int, Books*>::const_iterator it = this->m_BookMap.find(bookId);
    if (it != this->m_BookMap.end())
        return it.value();
    else
        return NULL;
}

UniqueBook* SysType::getUniqueBook(int id)
{
    QMap<int, UniqueBook*>::const_iterator it = this->m_UniqueBookMap.find(id);
    if (it != this->m_UniqueBookMap.end())
        return it.value();
    else
        return NULL;
}

UniqueBook* SysType::getUniqueBookByBookCode(QString bookCode)
{
    QMap<QString, UniqueBook*>::const_iterator it = this->m_UniqueBookCodeMap.find(bookCode);
    if (it != this->m_UniqueBookCodeMap.end())
        return it.value();
    else
        return NULL;
}

BookCateGory* SysType::getBookCateGrory(int categoryId)
{
    QMap<int, BookCateGory*>::const_iterator it = this->m_BookCateGoryMap.find(categoryId);
    if (it != this->m_BookCateGoryMap.end())
        return it.value();
    else
        return NULL;
}

Borrow* SysType::getBorrow(int borrowId)
{
    QMap<int, Borrow*>::const_iterator it = this->m_BorrowMap.find(borrowId);
    if (it != this->m_BorrowMap.end())
        return it.value();
    else
        return NULL;
}

Borrow* SysType::getBorrowByUniqueBook(int id)
{
    QMap<int, Borrow*>::const_iterator it;
    for (it = this->m_BorrowMap.begin(); it != this->m_BorrowMap.end(); ++it)
    {
        if(it.value()->getBookId() == id)
        {
            return it.value();
        }
    }
    return NULL;
}

MemberLevel* SysType::getMemberLevel(int levelId)
{
    QMap<int, MemberLevel*>::const_iterator it = this->m_MemberLevelMap.find(levelId);
    if (it != this->m_MemberLevelMap.end())
        return it.value();
    else
        return NULL;
}

QVector<Readers*> SysType::getReaderByLevel(int levelId)
{
    QVector<Readers*> readerTypeVec;
    QMap<int, Readers*>::const_iterator it;
    for(it = m_ReaderMap.begin(); it != m_ReaderMap.end(); ++it)
    {
        if(it.value()->getCardLevel() == levelId)
        {
            readerTypeVec.append(it.value());
        }
    }
    return readerTypeVec;
}

QVector<Borrow*> SysType::getReaderBorrow(int readerId)
{
    QVector<Borrow*> readerBorrowVec;
    QMap<int, Borrow*>::const_iterator it;
    for (it = m_BorrowMap.begin(); it != m_BorrowMap.end(); ++it)
    {
        if (it.value()->getReaderId() == readerId)
        {
            readerBorrowVec.append(it.value());
        }
    }
    return readerBorrowVec;
}

QVector<LossReporting*> SysType::getReaderLossReporting(int readerId)
{
    QVector<LossReporting*> readerLossReportingVec;
    QMap<int, LossReporting*>::const_iterator it;
    for (it = m_LossReportingMap.begin(); it != m_LossReportingMap.end(); ++it)
    {
        if (it.value()->getReaderId() == readerId)
        {
            readerLossReportingVec.append(it.value());
        }
    }
    return readerLossReportingVec;
}

QVector<Books*> SysType::getBookByType(int typeId)
{
    QVector<Books*> bookByTypeVec;
    QMap<int, Books*>::const_iterator it;
    for (it = m_BookMap.begin(); it != m_BookMap.end(); ++it)
    {
        if (it.value()->getCateGoryId() == typeId)
        {
            bookByTypeVec.append(it.value());
        }
    }
    return bookByTypeVec;
}

QVector<UniqueBook*> SysType::getUniqueBookByType(int typeId)
{
    QVector<UniqueBook*> uniqueBookVec;
    QMap<int, UniqueBook*>::const_iterator it;
    for (it = m_UniqueBookMap.begin(); it != m_UniqueBookMap.end(); ++it)
    {
        if (this->m_BookMap.find(it.value()->getBookId()).value()->getCateGoryId() == typeId)
        {
            uniqueBookVec.append(it.value());
        }
    }
    return uniqueBookVec;
}

QVector<UniqueBook*> SysType::getUniqueBookByBookId(int bookId)
{
    QVector<UniqueBook*> uniqueBookVec;
    QMap<int, UniqueBook*>::const_iterator it;
    for (it = m_UniqueBookMap.begin(); it != m_UniqueBookMap.end(); ++it)
    {
        if (it.value()->getBookId() == bookId)
        {
            uniqueBookVec.append(it.value());
        }
    }
    return uniqueBookVec;
}

void SysType::resetUserMap()
{
    Clear<User>::clear(m_UserMap);
    initUserInfo();
}

void SysType::resetReaderMap()
{
    Clear<Readers>::clear(m_ReaderMap);
    initReaderInfo();
}

void SysType::resetManagerMap()
{
    Clear<Managers>::clear(m_ManagerMap);
    initManagerInfo();
}

void SysType::resetBookMap()
{
    Clear<Books>::clear(m_BookMap);
    initBooksInfo();
}

void SysType::resetUniqueBookMap()
{
    Clear<UniqueBook>::clear(m_UniqueBookMap);
    initUniqueBookInfo();
}

void SysType::resetBookCateGoryMap()
{
    Clear<BookCateGory>::clear(m_BookCateGoryMap);
    initBookCateGoryInfo();
}

void SysType::resetBorrowMap()
{
    Clear<Borrow>::clear(m_BorrowMap);
    initBorrowInfo();
}

void SysType::resetMemberLevelMap()
{
    Clear<MemberLevel>::clear(m_MemberLevelMap);
    initMemberLevelInfo();
}

void SysType::resetLossReportingMap()
{
    Clear<LossReporting>::clear(m_LossReportingMap);
    initLossReportingInfo();
}

User* SysType::reverUser(int userId)
{
    QMap<int, User*>::iterator it = m_UserMap.find(userId);
    if (it != m_UserMap.end())
    {
        SAFE_DELETE(it.value());
        this->m_UserMap.remove(userId);

        User user;
        user.setUserID(userId);
        DaoUser daouser;
        QVector<User*> userVec = daouser.Select(&user, COND_ID);
        if (userVec.size() > 0)
        {
            User *pObj = userVec.at(0);
            this->m_UserMap.insert(userId, pObj);
            return pObj;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        QMessageBox::warning(0, "警告！", "没有此user。", "确定");
        return NULL;
    }
}

Readers *SysType::reverReader(int readerId)
{
    QMap<int, Readers*>::iterator it = m_ReaderMap.find(readerId);
    if (it != m_ReaderMap.end())
    {
        SAFE_DELETE(it.value());
        this->m_ReaderMap.remove(readerId);

        User user;
        user.setUserID(readerId);
        DaoUser daoUser;
        QVector<User*> userVec = daoUser.Select(&user, COND_ID);
        if (userVec.size() > 0)
        {
            User *pUser = userVec.at(0);

            Readers reader;
            reader.setReaderId(readerId);
            DaoReaders daoReaders;

            QVector<Readers*> readerVec = daoReaders.Select(&reader, COND_NAME);
            if(readerVec.size() > 0)
            {
                Readers *pReader = readerVec.at(0);

                pReader->setUserID(pUser->getUserID());
                pReader->setUserCode(pUser->getUserCode());
                pReader->setUserName(pUser->getUserName());
                pReader->setUserPsw(pUser->getUserPsw());
                pReader->setSex(pUser->getSex());
                pReader->setBirthDay(pUser->getBirthDay());
                pReader->setPhone(pUser->getPhone());
                pReader->setMobile(pUser->getMobile());
                pReader->setMail(pUser->getMail());
                pReader->setUserType(pUser->getUserType());
                pReader->setUserRemark(pUser->getUserRemark());
                pReader->setUserLastLogTime(pUser->getUserLastLogTime());
                pReader->setUserCreateTime(pUser->getUserCreateTime());

                this->m_ReaderMap.insert(readerId, pReader);

                return pReader;
            } else {
                return NULL;
            }
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        QMessageBox::warning(0, "警告！", "没有此reader。", "确定");
        return NULL;
    }
}

Managers* SysType::reverManager(int managerId)
{
    QMap<int, Managers*>::iterator it = this->m_ManagerMap.find(managerId);
    if (it != this->m_ManagerMap.end())
    {
        SAFE_DELETE(it.value());
        this->m_ManagerMap.remove(managerId);

        User user;
        user.setUserID(managerId);
        DaoUser daoUser;
        QVector<User*> userVec = daoUser.Select(&user, COND_ID);
        if (userVec.size() > 0)
        {
            User *pUser = daoUser.Select(&user, COND_ID).at(0);

            DaoManagers daoManager;
            Managers manager;
            manager.setManagerId(managerId);

            QVector<Managers*> managerVec = daoManager.Select(&manager, COND_NAME);
            if (managerVec.size() > 0)
            {
                Managers *pManager = managerVec.at(0);

                pManager->setUserID(pUser->getUserID());
                pManager->setUserCode(pUser->getUserCode());
                pManager->setUserName(pUser->getUserName());
                pManager->setUserPsw(pUser->getUserPsw());
                pManager->setSex(pUser->getSex());
                pManager->setBirthDay(pUser->getBirthDay());
                pManager->setPhone(pUser->getPhone());
                pManager->setMobile(pUser->getMobile());
                pManager->setMail(pUser->getMail());
                pManager->setUserType(pUser->getUserType());
                pManager->setUserRemark(pUser->getUserRemark());
                pManager->setUserLastLogTime(pUser->getUserLastLogTime());
                pManager->setUserCreateTime(pUser->getUserCreateTime());

                this->m_ManagerMap.insert(pManager->getUserID(), pManager);

                return pManager;
            } else {
                return NULL;
            }
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        QMessageBox::warning(0, "警告！", "没有此manager。", "确定");
        return NULL;
    }
}

Books* SysType::reverBook(int bookId)
{
    QMap<int, Books*>::iterator it = this->m_BookMap.find(bookId);
    if (it != this->m_BookMap.end())
    {
        SAFE_DELETE(it.value());
        this->m_BookMap.remove(bookId);

        DaoBooks daoBook;
        Books book;
        book.setBookId(bookId);
        QVector<Books*> bookVec = daoBook.Select(&book, COND_ID);
        if (bookVec.size() > 0)
        {
            Books *pBook = bookVec.at(0);
            this->m_BookMap.insert(bookId,pBook);
            return pBook;
        } else {
            return NULL;
        }
    }
    else
    {
        QMessageBox::warning(0, "警告！", "没有此book。", "确定");
        return NULL;
    }
}

UniqueBook* SysType::reverUniqueBook(int id)
{
    QMap<int, UniqueBook*>::iterator it = this->m_UniqueBookMap.find(id);

    QMap<QString, UniqueBook*>::iterator coreIt;
    for (coreIt = this->m_UniqueBookCodeMap.begin(); coreIt != this->m_UniqueBookCodeMap.end(); ++coreIt)
    {
        if (coreIt.value()->getId() == id) {
            this->m_UniqueBookCodeMap.erase(coreIt);
            break;
        }
    }

    if (it != this->m_UniqueBookMap.end())
    {
        SAFE_DELETE(it.value());
        this->m_UniqueBookMap.remove(id);

        DaoUniqueBook daoUniqueBook;
        UniqueBook uniqueBook;
        uniqueBook.setId(id);

        QVector<UniqueBook*> uniqueBookVec = daoUniqueBook.Select(&uniqueBook, COND_ID);
        if (uniqueBookVec.size() > 0)
        {
            UniqueBook *pUniqueBook = uniqueBookVec.at(0);
            this->m_UniqueBookCodeMap.insert(pUniqueBook->getBookCode(), pUniqueBook);
            this->m_UniqueBookMap.insert(id, pUniqueBook);
            return pUniqueBook;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        QMessageBox::warning(0, "警告！", "没有此UniqueBook。", "确定");
        return NULL;
    }
}

Borrow *SysType::reverBorrow(int id)
{
    QMap<int, Borrow*>::iterator it = this->m_BorrowMap.find(id);
    if (it != this->m_BorrowMap.end())
    {
        SAFE_DELETE(it.value());
        this->m_BorrowMap.remove(id);

        DaoBorrow daoBorrow;
        Borrow borrow;
        borrow.setBorrowId(id);
        QVector<Borrow*> borrowVec = daoBorrow.Select(&borrow, COND_ID);
        if (borrowVec.size() > 0)
        {
            Borrow *pBorrow = borrowVec.at(0);
            this->m_BorrowMap.insert(id, pBorrow);
            return pBorrow;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        QMessageBox::warning(0, "警告！", "没有此Borrow。", "确定");
        return NULL;
    }
}

MemberLevel* SysType::reverMemberLevel(int id)
{
    QMap<int, MemberLevel*>::iterator it = this->m_MemberLevelMap.find(id);

    if (it != this->m_MemberLevelMap.end())
    {
        SAFE_DELETE(it.value());
        this->m_MemberLevelMap.remove(id);

        MemberLevel memberLevel;
        DaoMemberLevel daoMemberLevel;
        memberLevel.setLevelId(id);
        QVector<MemberLevel*> memberLevelVec = daoMemberLevel.Select(&memberLevel, COND_ID);
        if (memberLevelVec.size() > 0)
        {
            MemberLevel *pMemberLevel = memberLevelVec.at(0);
            this->m_MemberLevelMap.insert(id, pMemberLevel);
            return pMemberLevel;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        QMessageBox::warning(0, "警告", "没有此MemberLevel。", "确定");
        return NULL;
    }
}

void SysType::addBook(int id, Books *book)
{
    this->m_BookMap.insert(id, book);
}

void SysType::addUniqueBook(int id, UniqueBook *uniqueBook)
{
    this->m_UniqueBookCodeMap.insert(uniqueBook->getBookCode(), uniqueBook);
    this->m_UniqueBookMap.insert(id, uniqueBook);
}

void SysType::addBorrow(int id, Borrow *borrow)
{
    this->m_BorrowMap.insert(id, borrow);
}

void SysType::addMemberLevel(int id, MemberLevel *memberLevel)
{
    this->m_MemberLevelMap.insert(id, memberLevel);
}

void SysType::addBookCateGory(int id, BookCateGory *bookCateGory)
{
    this->m_BookCateGoryMap.insert(id, bookCateGory);
}

bool SysType::deleteUser(int id)
{
    QMap<int, User*>::iterator it = this->m_UserMap.find(id);
    this->m_UserCoreMap.remove(it.value()->getUserCode());
    if (it != this->m_UserMap.end())
        SAFE_DELETE(it.value());
    this->m_UserMap.remove(id);
    return true;
}

bool SysType::deleteReader(int userId)
{
    QMap<int, Readers*>::iterator it = this->m_ReaderMap.find(userId);
    if (it != this->m_ReaderMap.end())
        SAFE_DELETE(it.value());
    this->m_ReaderMap.remove(userId);
    return true;
}

bool SysType::deleteManager(int userId)
{
    QMap<int, Managers*>::iterator it = this->m_ManagerMap.find(userId);
    if(it != this->m_ManagerMap.end())
        SAFE_DELETE(it.value());
    this->m_ManagerMap.remove(userId);
    return true;
}

bool SysType::deleteUniqueBook(int id)
{
    QMap<int, UniqueBook*>::iterator it = this->m_UniqueBookMap.find(id);
    if (it != this->m_UniqueBookMap.end())
        SAFE_DELETE(it.value());
    this->m_UniqueBookMap.remove(id);
    return true;
}

bool SysType::deleteBook(int id)
{
    QMap<int, Books*>::iterator it = this->m_BookMap.find(id);
    if (it != this->m_BookMap.end())
        SAFE_DELETE(it.value());
    this->m_BookMap.remove(id);
    return true;
}

bool SysType::deleteBorrow(int id)
{
    QMap<int, Borrow*>::iterator it = this->m_BorrowMap.find(id);
    if (it != this->m_BorrowMap.end())
        SAFE_DELETE(it.value());
    this->m_BorrowMap.remove(id);
    return true;
}

bool SysType::deleteMemberLevel(int id)
{
    QMap<int, MemberLevel*>::iterator it = this->m_MemberLevelMap.find(id);
    if (it != this->m_MemberLevelMap.end())
        SAFE_DELETE(it.value());
    this->m_MemberLevelMap.remove(id);
    return true;
}

void SysType::addUser(int id, User *user)
{
    this->m_UserMap.insert(id, user);
    this->m_UserCoreMap.insert(user->getUserCode(), user);
}

void SysType::addReader(int userId, Readers *reader)
{
    this->m_ReaderMap.insert(userId, reader);
}

void SysType::addManager(int userId, Managers *manager)
{
    this->m_ManagerMap.insert(userId, manager);
}

void SysType::addUserType(int id, UserType *pObj)
{
    this->m_UserTypeMap.insert(id, pObj);
}

void SysType::initUserInfo()
{
    DaoUser daoUser;
    User user;
    QVector<User*> userVec = daoUser.Select(&user, COND_NULL);
    foreach (User *pUser, userVec) {
        this->m_UserMap.insert(pUser->getUserID(), pUser);
        this->m_UserCoreMap.insert(pUser->getUserCode(), pUser);
    }
}

void SysType::initReaderInfo()
{
    DaoReaders daoReaders;
    Readers readers;
    QVector<Readers*> readerVec = daoReaders.Select(&readers, COND_NULL);
    QMap<int, User*>::iterator it;
    foreach (Readers *pReader, readerVec) {
         it = m_UserMap.find(pReader->getReaderId());
         if (it == m_UserMap.end())
         {
             int ret = QMessageBox::warning(0, "警告",
                                            "数据库出现严重！程序将立即结束！", "确定");
             if (ret == 0)
                 exit(0);
         }
         User *user = it.value();
         pReader->setUserID(user->getUserID());
         pReader->setUserCode(user->getUserCode());
         pReader->setUserName(user->getUserName());
         pReader->setUserPsw(user->getUserPsw());
         pReader->setSex(user->getSex());
         pReader->setBirthDay(user->getBirthDay());
         pReader->setPhone(user->getPhone());
         pReader->setMobile(user->getMobile());
         pReader->setMail(user->getMail());
         pReader->setUserType(user->getUserType());
         pReader->setUserRemark(user->getUserRemark());
         pReader->setUserLastLogTime(user->getUserLastLogTime());
         pReader->setUserCreateTime(user->getUserCreateTime());
         this->m_ReaderMap.insert(pReader->getUserID(), pReader);
    }
}

void SysType::initManagerInfo()
{
    DaoManagers daoManagers;
    Managers managers;
    QVector<Managers*> managerVec = daoManagers.Select(&managers, COND_NULL);
    QMap<int, User*>::iterator it;
    foreach (Managers *pManager, managerVec) {
         it = m_UserMap.find(pManager->getManagerId());
         if (it == m_UserMap.end())
         {
             int ret = QMessageBox::warning(0, "警告",
                                            "数据库出现严重！程序将立即结束！", "确定");
             if (ret == 0)
                 exit(0);
         }
         User *user = it.value();
         pManager->setUserID(user->getUserID());
         pManager->setUserCode(user->getUserCode());
         pManager->setUserName(user->getUserName());
         pManager->setUserPsw(user->getUserPsw());
         pManager->setSex(user->getSex());
         pManager->setBirthDay(user->getBirthDay());
         pManager->setPhone(user->getPhone());
         pManager->setMobile(user->getMobile());
         pManager->setMail(user->getMail());
         pManager->setUserType(user->getUserType());
         pManager->setUserRemark(user->getUserRemark());
         pManager->setUserLastLogTime(user->getUserLastLogTime());
         pManager->setUserCreateTime(user->getUserCreateTime());
         this->m_ManagerMap.insert(pManager->getUserID(), pManager);
    }
}

void SysType::initUserTypeInfo()
{
    DaoUserType daoUserType;
    UserType userType;
    QVector<UserType*> userTypeVec = daoUserType.Select(&userType, COND_NULL);
    foreach (UserType *pUserType, userTypeVec) {
        this->m_UserTypeMap.insert(pUserType->getUserTypeId(), pUserType);
    }
}

void SysType::initBooksInfo()
{
    DaoBooks daoBooks;
    Books books;
    QVector<Books*> bookVec = daoBooks.Select(&books, COND_NULL);
    foreach (Books *pBook, bookVec) {
        this->m_BookMap.insert(pBook->getBookId(), pBook);
    }
}

void SysType::initUniqueBookInfo()
{
    DaoUniqueBook daoUniqueBook;
    UniqueBook uniqueBook;
    QVector<UniqueBook*> uniqueBookVec = daoUniqueBook.Select(&uniqueBook, COND_NULL);
    foreach (UniqueBook *pUniqueBook, uniqueBookVec) {
        this->m_UniqueBookMap.insert(pUniqueBook->getId(), pUniqueBook);
        this->m_UniqueBookCodeMap.insert(pUniqueBook->getBookCode(), pUniqueBook);
    }
}

void SysType::initBookCateGoryInfo()
{
    DaoBookCateGory daoBookCateGory;
    BookCateGory bookCateGory;
    QVector<BookCateGory*> bookCateGoryVec = daoBookCateGory.Select(&bookCateGory, COND_NULL);
    foreach (BookCateGory *pBookCateGory, bookCateGoryVec) {
        this->m_BookCateGoryMap.insert(pBookCateGory->getCateGoryId(), pBookCateGory);
    }
}

void SysType::initBorrowInfo()
{
    DaoBorrow daoBorrow;
    Borrow borrow;
    QVector<Borrow*> borrowVec = daoBorrow.Select(&borrow, COND_NULL);
    foreach (Borrow *pBorrow, borrowVec) {
        this->m_BorrowMap.insert(pBorrow->getBorrowId(), pBorrow);
    }
}

void SysType::initMemberLevelInfo()
{
    DaoMemberLevel daoMemberLevel;
    MemberLevel memberLevel;
    QVector<MemberLevel*> memberLevelVec = daoMemberLevel.Select(&memberLevel, COND_NULL);
    foreach (MemberLevel *pMemberLevel, memberLevelVec) {
        this->m_MemberLevelMap.insert(pMemberLevel->getLevelId(), pMemberLevel);
    }
}

void SysType::initLossReportingInfo()
{
    DaoLossReporting daoLossReporting;
    LossReporting lossReporting;
    QVector<LossReporting*> lossReportingVec = daoLossReporting.Select(&lossReporting, COND_NULL);
    foreach (LossReporting *pLossReporting, lossReportingVec) {
        this->m_LossReportingMap.insert(pLossReporting->getId(), pLossReporting);
    }
}
