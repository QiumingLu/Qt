#include "uiusercenter.h"
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QSplitter>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QList>
#include <QVector>
#include "model/books.h"
#include "dao/daobooks.h"
#include "ui/myinfowidget.h"
#include "ui/mylibrarywidget.h"
#include "core/sysinclude.h"
#include "model/uniquebook.h"
#include "core/systype.h"
#include "model/bookcategory.h"
#include "ui/iconedlineedit.h"
#include "dao/DaoHeader.h"
#include "model/sysenviroment.h"
#include "ui/booklistwidget.h"
#include "ui/booklistview.h"

UIUserCenter::UIUserCenter(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags)
{
    this->infoflags = true;
    this->ifInputBook = false;
    this->initUi();
    this->createConnections();
}

UIUserCenter::~UIUserCenter()
{

}

void UIUserCenter::initUi()
{
    this->setWindowTitle("我的图书中心[*]");
    this->setWindowState(Qt::WindowMaximized);

    this->banner = new QLabel();
    this->banner->setPixmap(QPixmap(":/006.jpg"));
    this->banner->setScaledContents(true);

    this->m_findBook = new IconedLineEdit(this);
    this->findBook = new QPushButton(tr("高级检索"));
    this->myInfomation = new QPushButton(tr("我的个人资料"));
    this->myLibrary = new QPushButton(tr("我的图书馆"));
    this->refleshBtn = new QPushButton(tr("刷新"));
    this->bookCateGory = new QComboBox();

    this->bookCateGoryList = SYSTYPE->getAllBookCateGory();
    for (int i = 0; i < bookCateGoryList.size(); ++i)
    {
        this->bookCateGory->addItem(bookCateGoryList.at(i)->getCateGoryName(), i);

        MyLibraryWidget* bookType = new MyLibraryWidget(this, sysinclude::BookBox);
        bookType->setWindowTitle("馆藏图书列表");

        this->bookVect = SYSTYPE->getUniqueBookByType(this->bookCateGoryList.at(i)->getCateGoryId());
        bookType->getBookListWidget()->getBookListView()->setUniqueBookList(bookVect.toList());
        bookType->getBookListWidget()->getBookListView()->initBookBoxList();

        this->bookTypeWidget.append(bookType);
    }

    this->btnLayout = new QHBoxLayout();
    this->btnLayout->addWidget(this->m_findBook);
    this->btnLayout->addWidget(this->findBook);
    this->btnLayout->addStretch(6);
    this->btnLayout->addWidget(this->myInfomation);
    this->btnLayout->addWidget(this->myLibrary);
    this->btnLayout->addWidget(this->bookCateGory);
    this->btnLayout->addWidget(this->refleshBtn);
    this->btnLayout->addStretch(1);

    this->btnWidget = new QWidget();
    this->btnWidget->setLayout(this->btnLayout);

    this->myInfoWidget = new MyInfoWidget(this);

    this->myInfoWidget->hide();

    this->mainSplitter = new QSplitter(Qt::Horizontal);
    this->mainSplitter->addWidget(this->myInfoWidget);
    for (int i = 0; i < bookTypeWidget.size(); ++i)
    {
        this->mainSplitter->addWidget(bookTypeWidget.at(i));
        bookTypeWidget.at(i)->hide();
    }

    this->mainSplitter->setStretchFactor(1, 1);

    this->mainBox = new QGroupBox();

    this->mainLayout = new QGridLayout();
    this->mainLayout->setRowStretch(0, 1);
    this->mainLayout->setRowStretch(1, 1);
    this->mainLayout->setRowStretch(2, 5);
    this->mainLayout->addWidget(this->banner, 0, 0, 1, 1);
    this->mainLayout->addWidget(this->btnWidget, 1, 0, 1, 1);
    this->mainLayout->addWidget(this->mainSplitter, 2, 0, 5, 1);

    this->mainWidget = new QWidget();
    this->mainWidget->setLayout(this->mainLayout);
    this->setCentralWidget(this->mainWidget);
}

void UIUserCenter::createConnections()
{
    QObject::connect(this->myInfomation, SIGNAL(clicked()), this, SLOT(slotMyInfoShow()));
    QObject::connect(this->myLibrary, SIGNAL(clicked()), this, SLOT(slotMyLibraryShow()));
    QObject::connect(this->bookCateGory, SIGNAL(activated(int)), this, SLOT(slotShowBook(int)));
    QObject::connect(this->findBook, SIGNAL(clicked()), this, SLOT(slotFindBook()));
    QObject::connect(this->refleshBtn, SIGNAL(clicked()), this, SLOT(slotReflesh()));
}

void UIUserCenter::slotMyInfoShow()
{
    if (infoflags) {
        this->myInfoWidget->initInfomation(SysEnviroment::getInstance()->getReader());
        this->myInfoWidget->show();
        infoflags = false;
    } else {
        this->myInfoWidget->hide();
        infoflags = true;
    }
}

void UIUserCenter::slotMyLibraryShow()
{
    this->myLibraryWidget = new MyLibraryWidget(0, sysinclude::MyLibrary);
    this->myLibraryWidget->setFixedSize(750, 500);
    this->myLibraryWidget->setWindowTitle("我的图书馆");
    this->myLibraryWidget->getBookListWidget()->getBookListView()->initBookBoxList();
    this->myLibraryWidget->show();
}


void UIUserCenter::slotShowBook(int bookType)
{
    for (int i = 0; i < bookTypeWidget.size(); ++i)
    {
        if (i == bookType)
        {
            this->bookTypeWidget.at(i)->show();
        }
        else
        {
            this->bookTypeWidget.at(i)->hide();
        }
    }
}

void UIUserCenter::slotReflesh()
{
    for (int i = 0; i < bookTypeWidget.size(); ++i)
    {
        this->bookVect.clear();
        this->bookVect = SYSTYPE->getUniqueBookByType(this->bookCateGoryList.at(i)->getCateGoryId());
        this->bookTypeWidget.at(i)->getBookListWidget()->getBookListView()->setUniqueBookList(bookVect.toList());
        this->bookTypeWidget.at(i)->getBookListWidget()->getBookListView()->initBookBoxList();
    }
}

void UIUserCenter::slotFindBook()
{
    QString inputBook = this->m_findBook->text();
    DaoBooks daoBook;
    daoBook.findBook(inputBook);
    QList<UniqueBook*> uniqueBookList = daoBook.findUniqueBook();

    MyLibraryWidget *findBookWidget = new MyLibraryWidget(0, sysinclude::BookBox);
    findBookWidget->getBookListWidget()->getBookListView()->setUniqueBookList(uniqueBookList);
    findBookWidget->getBookListWidget()->getBookListView()->initBookBoxList();
    findBookWidget->show();
}
