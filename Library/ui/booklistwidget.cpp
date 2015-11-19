#include "booklistwidget.h"
#include "ui/booklistview.h"
#include "core/sysinclude.h"
#include "ui/mylibrarylistview.h"
#include "ui/booktypelistview.h"
#include <QGridLayout>

BookListWidget::BookListWidget(QWidget *parent, int type) :
    QWidget(parent)
{
    this->type = type;
    this->initUI();
}

BookListWidget::~BookListWidget()
{
    SAFE_DELETE(m_bookListView);
    SAFE_DELETE(mainLayout);
}

void BookListWidget::initUI()
{
    this->mainLayout = new QGridLayout(this);
    if (type == sysinclude::MyLibrary)
        this->m_bookListView = new MyLibraryListView();
    else if (type == sysinclude::BookBox)
        this->m_bookListView = new BookTypeListView();
    this->mainLayout->addWidget(this->m_bookListView);
    this->mainLayout->setMargin(0);
    this->mainLayout->setSpacing(0);
    this->setLayout(this->mainLayout);
}

BookListView* BookListWidget::getBookListView() const
{
    return this->m_bookListView;
}
