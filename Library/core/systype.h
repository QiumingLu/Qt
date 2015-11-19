#ifndef SYSTYPE_H
#define SYSTYPE_H
#include <QMap>

class User;
class Readers;
class Managers;
class Books;
class UniqueBook;
class BookCateGory;
class Borrow;
class MemberLevel;
class LossReporting;
class UserType;

#define SYSTYPE SysType::getInstance()
class SysType
{    
private:
    SysType();
    SysType(const SysType &){}
    SysType &operator=(const SysType &)
    {
        return *this;
    }

    class GarBo
    {
    public:
        ~GarBo()
        {
            if (SysType::getInstance() != NULL)
            {
                delete SysType::getInstance();
            }
        }
    };
    static GarBo foo;
    static SysType *pInstance;

public:
    static SysType* getInstance()
    {
        if (pInstance == NULL)
        {
            pInstance = new SysType();
        }
        return pInstance;
    }
    ~SysType();
    bool sysInit();
    bool update();
    bool cleanUp();

    QList<User*> getAllUser();
    QList<Readers*> getAllReaders();
    QList<Managers*> getAllManagers();
    QList<UserType*> getAllUserType();
    QList<Books*> getAllBooks();
    QList<UniqueBook*> getAllUniqueBook();
    QList<BookCateGory*> getAllBookCateGory();
    QList<Borrow*> getAllBorrow();
    QList<MemberLevel*> getAllMemberLevel();

    User* getUser(int userId);
    User* getUserByCode(QString &userCode);
    Readers* getReader(int readerId);
    Managers* getManager(int managerId);
    Books* getBook(int bookId);
    UniqueBook* getUniqueBook(int id);
    UniqueBook* getUniqueBookByBookCode(QString bookCode);
    BookCateGory* getBookCateGrory(int categoryId);
    Borrow* getBorrow(int borrowId);
    Borrow* getBorrowByUniqueBook(int id);
    MemberLevel* getMemberLevel(int levelId);

    QVector<Readers*> getReaderByLevel(int levelId);
    QVector<Borrow*> getReaderBorrow(int readerId);
    QVector<LossReporting*> getReaderLossReporting(int readerId);
    QVector<Books*> getBookByType(int typeId);
    QVector<UniqueBook*> getUniqueBookByType(int typeId);
    QVector<UniqueBook*> getUniqueBookByBookId(int bookId);

    void resetUserMap();
    void resetReaderMap();
    void resetManagerMap();
    void resetBookMap();
    void resetUniqueBookMap();
    void resetBookCateGoryMap();
    void resetBorrowMap();
    void resetMemberLevelMap();
    void resetLossReportingMap();

    User *reverUser(int userId);
    Readers* reverReader(int readerId);
    Managers *reverManager(int managerId);
    Books *reverBook(int bookId);
    UniqueBook *reverUniqueBook(int id);
    Borrow* reverBorrow(int id);
    MemberLevel* reverMemberLevel(int id);

    bool deleteUser(int id);
    bool deleteReader(int id);
    bool deleteManager(int id);
    bool deleteUniqueBook(int id);
    bool deleteBook(int id);
    bool deleteBorrow(int id);
    bool deleteMemberLevel(int id);

    void addUser(int id, User *user);
    void addReader(int userId, Readers *reader);
    void addManager(int userId, Managers *manager);
    void addUserType(int id, UserType *pObj);
    void addBook(int id, Books *book);
    void addUniqueBook(int id, UniqueBook *uniqueBook);
    void addBorrow(int id, Borrow *borrow);
    void addMemberLevel(int id, MemberLevel *memberLevel);
    void addBookCateGory(int id, BookCateGory *bookCateGory);

private:
    void initUserInfo();
    void initReaderInfo();
    void initManagerInfo();
    void initUserTypeInfo();
    void initBooksInfo();
    void initUniqueBookInfo();
    void initBookCateGoryInfo();
    void initBorrowInfo();
    void initMemberLevelInfo();
    void initLossReportingInfo();

private:
    QMap<int, User*> m_UserMap;
    QMap<QString, User*> m_UserCoreMap;
    QMap<int, Readers*> m_ReaderMap;
    QMap<int, Managers*> m_ManagerMap;
    QMap<int, UserType*> m_UserTypeMap;
    QMap<int, Books*> m_BookMap;
    QMap<int, UniqueBook*> m_UniqueBookMap;
    QMap<QString, UniqueBook*> m_UniqueBookCodeMap;
    QMap<int, BookCateGory*> m_BookCateGoryMap;
    QMap<int, Borrow*> m_BorrowMap;
    QMap<int, MemberLevel*> m_MemberLevelMap;
    QMap<int, LossReporting*> m_LossReportingMap;
};

#endif // SYSTYPE_H
