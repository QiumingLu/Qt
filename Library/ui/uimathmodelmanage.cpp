#include "uimathmodelmanage.h"

#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>

UIMathModelManage::UIMathModelManage(QString assembly, QWidget *parent) :
    UIBookTableBase(assembly, parent)
{
    this->deleteModelBtn->setVisible(false);
    this->paraManage = NULL;
    this->setUpModel();
    this->setUpView();
    this->createConnections();
}

UIMathModelManage::~UIMathModelManage()
{

}

void UIMathModelManage::indexClicked(QModelIndex)
{
    this->index = QModelIndex(index);
    QModelIndex list = this->outputTable->currentIndex();
}

void UIMathModelManage::slotSetParaName(QString name)
{
    this->model->setData(this->outputTable->currentIndex(), name);
}

void UIMathModelManage::insertList(QModelIndex parent, int start, int end)
{

}

void UIMathModelManage::deleteList(QModelIndex parent, int start, int end)
{

}

void UIMathModelManage::dataChanged(QModelIndex topleft, QModelIndex bottomRight)
{

}

void UIMathModelManage::slotSave()
{

}

void UIMathModelManage::slotInsertRow()
{

}

void UIMathModelManage::setUpModel()
{

}
