#ifndef BASEDAO_H
#define BASEDAO_H

#include <QVariant>
class SysEnviroment;
class QStringList;
class QObject;
class QMetaObject;

struct CPair {
    CPair() {}
    CPair(const QString &str, const QVariant &_var)
        :string(str), var(_var){}
    QString string;
    QVariant var;
};

typedef QVector< QVector< CPair> > QRetVec;

class BaseDao
{
public:
    BaseDao();

    bool openDB();
    bool closeDB();

    bool transaction();
    bool commit();

    bool call_proc(QObject *pObj, const QString &proc_name,
                   const QStringList &inFields, const QStringList &outFields, bool isOutputDebug = true);
    bool call_proc(QObject *pObj, const QString &proc_name,
                   const QStringList &outFields, bool isOutputDebug = true);

    bool Insert(QObject *pObj, const QString &tableName);
    bool Insert(QObject *pObj, const QString &tableName, const QStringList &inFields);

    bool Update(QObject *pObj, const QString &tableName, const QStringList &conditions);
    bool Update(QObject *pObj, const QString &tableName,
                const QStringList &updateFields, const QStringList &conditions);

    bool Delete(QObject *pObj, const QString &tableName, const QStringList &condition);
    bool Delete(QObject *pObj, const QString &tableName, const QString &conditions);

    QRetVec Select(QObject *pObj, const QString &tableName, const QString &condition);
    QRetVec Select(QObject *pObj, const QString &tableName, const QStringList &conditions);
    QRetVec Select(QObject *pObj, const QString &tableName,
                   const QStringList &outFields, const QStringList &conditions);
    QRetVec Select(QObject *pObj, const QString &tableName,
                   const QStringList &outFields, const QString &condition);

    bool callADUSql(QObject *pObj, const QString &sql, const QStringList &fields);
    QRetVec callSelectSql(QObject *pObj, const QString &sql,
                          const QStringList &inFields, const QStringList &outFields);
    QVariant callSql(const QString &sql);
    QVariant callSql(const QString &sql, QList<QVariant>);
    bool callProc(const QString &proc_name, QList<QVariant> &inFields,
                  QList<QVariant> &outFields, bool isOutputDebug = true);

    int getId(QString &tableName, QString &outFields);

private:
    QString makeQuestionMarkList(int nSize);
    QStringList getProperties(const QMetaObject *pMeta);
    QStringList getAvaProperties(const QMetaObject *pMeta, const QStringList &excludes);
};

#endif // BASEDAO_H
