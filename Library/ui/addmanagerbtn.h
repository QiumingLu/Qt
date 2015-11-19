#ifndef ADDMANAGERBTN_H
#define ADDMANAGERBTN_H

#include "ui/addmanager.h"

class Managers;
class AddManagerBtn : public AddManager
{
    Q_OBJECT

public:
    AddManagerBtn(QWidget *parent = 0);
    ~AddManagerBtn();

private:
    Managers *manager;

private slots:
    void slotSave();
};

#endif // ADDMANAGERBTN_H
