/*
 * @Author: QiumingLu
 * @Date: 2014.11.22
 */
#ifndef LOSSREPORTING_H
#define LOSSREPORTING_H

#include <QObject>
#include <QDateTime>

class LossReporting : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int ID READ getId WRITE setId)
    Q_PROPERTY(int READER_ID READ getReaderId WRITE setReaderId)
    Q_PROPERTY(QDateTime LOSS_DATE READ getLossDate WRITE setLossDate)
    Q_PROPERTY(QString REMARK READ getRemark WRITE setRemark)

public:
    LossReporting();
    ~LossReporting();

    int getId() const;
    void setId(int);

    int getReaderId() const;
    void setReaderId(int);

    QDateTime getLossDate() const;
    void setLossDate(const QDateTime &);

    QString getRemark() const;
    void setRemark(const QString&);

private:
    int id;
    int readerId;
    QDateTime lossDate;
    QString remark;
};

#endif // LOSSREPORTING_H
