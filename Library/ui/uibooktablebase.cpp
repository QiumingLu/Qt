#include "uibooktablebase.h"
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QMessageBox>

UIBookTableBase::UIBookTableBase(QString assembly, QWidget *parent) :
    QWidget(parent), assembly(assembly)
{
    this->initBookTableBase();
}

UIBookTableBase::~UIBookTableBase()
{

}

void UIBookTableBase::initBookTableBase()
{
    QString temp = "";
    this->tableviewDataChange = temp;
    this->model = NULL;

    this->saveModelBtn = new QPushButton(tr("保存(&S)"));
    this->saveModelBtn->setShortcut(tr("Ctrl+S"));
    this->saveModelBtn->setIcon(QIcon(""));

    this->deleteModelBtn = new QPushButton(tr("删除(&D)"));
    this->deleteModelBtn->setShortcut(tr("Ctrl+D"));
    this->deleteModelBtn->setIcon(QIcon(""));

    this->insertBtn = new QPushButton(tr("新增(&N"));
    this->insertBtn->setShortcut(tr("Ctrl+N"));
    this->insertBtn->setIcon(QIcon(""));

    this->saveModelBtn->setEnabled(false);
    this->deleteModelBtn->setEnabled(false);
    emit signalIfChanged(false);

    this->outputTable = new QTableView();
    this->rightLayout = new QVBoxLayout();
    this->rightLayout->addWidget(outputTable);

    this->rightGridLayout = new QGridLayout();
    this->rightGridLayout->addLayout(rightLayout, 0, 1, 1, 2);

    this->buttomLayout = new QHBoxLayout();
    this->buttomLayout->addStretch();
    this->buttomLayout->addWidget(this->insertBtn);
    this->buttomLayout->addWidget(this->saveModelBtn);
    this->buttomLayout->addWidget(this->deleteModelBtn);
    this->buttomLayout->setAlignment(rightGridLayout, Qt::AlignRight);

    this->rightGridLayout->addLayout(buttomLayout, 2, 1, 1, 1);
    this->setLayout(rightGridLayout);

    this->outputTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->outputTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
}

void UIBookTableBase::setUpView()
{
    this->outputTable->setMinimumWidth(50);
    this->outputTable->setModel(this->model);
    this->selectionModel = new QItemSelectionModel(this->model);
    this->outputTable->setSelectionModel(this->selectionModel);
    QObject::connect(this->selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this->outputTable, SLOT(selectionChanged(QItemSelection,QItemSelection)));
}

void UIBookTableBase::createConnections()
{
    QObject::connect(this->insertBtn, SIGNAL(clicked()), this, SLOT(slotInsertRow()));
    QObject::connect(this->deleteModelBtn, SIGNAL(clicked()), this, SLOT(slotDeleteRow()));
    QObject::connect(this->saveModelBtn, SIGNAL(clicked()), this, SLOT(slotSave()));
    QObject::connect(this->model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                     this, SLOT(dataChanged(QModelIndex,QModelIndex)));
    QObject::connect(this->model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                     this, SLOT(insertList(QModelIndex,int,int)));
    QObject::connect(this->model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
                     this, SLOT(deleteList(QModelIndex,int,int)));
    QObject::connect(this->outputTable, SIGNAL(clicked(QModelIndex)),
                     this, SLOT(indexClicked(QModelIndex)));
    QObject::connect(this->outputTable, SIGNAL(pressed(QModelIndex)),
                      this, SLOT(slotItemPress(QModelIndex)));
    //保存修改前的信息
    QObject::connect(this->outputTable, SIGNAL(doubleClicked(QModelIndex)),
                     this, SLOT(slotSaveChangedData(QModelIndex)));
}

//保存修改前的信息， 用于合法性判断读后恢复原值
void UIBookTableBase::slotSaveChangedData(QModelIndex)
{
    this->tableviewDataChange = index.data().toString();
}

void UIBookTableBase::slotItemPress(QModelIndex)
{
    QModelIndex list = this->outputTable->currentIndex();
    if (list.isValid()) {
        deleteModelBtn->setEnabled(true);
    } else {
        deleteModelBtn->setEnabled(false);
    }
}

void UIBookTableBase::slotDeleteRow()
{
    if (1 != QMessageBox::information(this, tr("删除提醒"), tr("确认删除数据项？"), "取消", "删除")) {
        return ;
    }

    QModelIndex index = this->outputTable->currentIndex();
    if (index.isValid())
    {
        this->model->removeRow(index.row(), QModelIndex());
    }

    this->saveModelBtn->setEnabled(true);
    emit signalIfChanged(true);
}

void UIBookTableBase::addModifyData(int mid)
{
    foreach (int tmp, this->modifiedData)
    {
        if (tmp == mid)
            return ;
    }
    this->modifiedData.append(mid);
}
