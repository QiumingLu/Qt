#ifndef ADDMANAGER_H
#define ADDMANAGER_H

#include <QWidget>
#include "ui/addbasewidget.h"

class QLineEdit;
class AddManager : public AddBaseWidget
{
    Q_OBJECT

public:
    explicit AddManager(QWidget *parent = 0);
    virtual ~AddManager();

protected:
    void initTable();
    QVector<QString> getTableText() const;

protected:
    QLineEdit *passEdit;
    QLineEdit *morePswEdit;

protected slots:
    virtual void slotSave() = 0;
};

#endif // ADDMANAGER_H
