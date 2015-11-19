#ifndef EDITMANAGERBTN_H
#define EDITMANAGERBTN_H

#include "ui/addmanager.h"

class Managers;
class EditManagerBtn : public AddManager
{
    Q_OBJECT

public:
    EditManagerBtn(QWidget *parent = 0);
    ~EditManagerBtn();

    bool setTableText(Managers *manager);

private:

    Managers *manager;

private slots:
    void slotSave();
};

#endif // EDITMANAGERBTN_H
