/*
 * @Author: QiumingLu
 * @Date:2014.11.22
 */
#ifndef MEMBERLEVEL_H
#define MEMBERLEVEL_H

#include <QObject>

class MemberLevel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int LEVEL_ID READ getLevelId WRITE setLevelId)
    Q_PROPERTY(QString LEVEL_NAME READ getLevelName WRITE setLevelName)
    Q_PROPERTY(int DAYS READ getDays WRITE setDays)
    Q_PROPERTY(int NUMBERS READ getNumbers WRITE setNumbers)
    Q_PROPERTY(double FEE READ getFee WRITE setFee)

public:
    MemberLevel();
    ~MemberLevel();

    int getLevelId() const;
    void setLevelId(int);

    QString getLevelName() const;
    void setLevelName(const QString &);

    int getDays() const;
    void setDays(int);

    int getNumbers() const;
    void setNumbers(int);

    double getFee() const;
    void setFee(double);

private:
    int levelId;
    QString levelName;
    int days;
    int numbers;
    double fee;
};

#endif // MEMBERLEVEL_H
