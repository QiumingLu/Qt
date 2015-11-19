#ifndef UIMATHMODELMANAGE_H
#define UIMATHMODELMANAGE_H
#include "ui/uibooktablebase.h"

class UIMathModelManage : public UIBookTableBase
{
    Q_OBJECT

public:
    explicit UIMathModelManage(QString assembly, QWidget *parent = 0);
    ~UIMathModelManage();

protected:
    void setUpModel();

private:
    QDialog *paraManage;

signals:

public slots:
    void indexClicked(QModelIndex);
    void insertList(QModelIndex parent, int start, int end);
    void deleteList(QModelIndex parent, int start, int end);
    void dataChanged(QModelIndex topleft, QModelIndex bottomRight);
    void slotSave();
    void slotInsertRow();
    void slotSetParaName(QString);
};

#endif // UIMATHMODELMANAGE_H
