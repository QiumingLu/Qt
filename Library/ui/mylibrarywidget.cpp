#include "mylibrarywidget.h"
#include "ui/booklistwidget.h"
#include "ui/booklistview.h"
#include "ui/mylibrarylistview.h"
#include "ui/booktypelistview.h"
#include "core/sysinclude.h"
#include "model/sysenviroment.h"
#include "model/readers.h"
#include "core/systype.h"
#include "model/uniquebook.h"
#include <QScrollBar>
#include <QHBoxLayout>


MyLibraryWidget::MyLibraryWidget(QWidget *parent, int type) :
    QWidget(parent)
{
    this->type = type;
    this->initUI();
    this->createConnections();
}

MyLibraryWidget::~MyLibraryWidget()
{

}

void MyLibraryWidget::initUI()
{

    this->m_BookListWidget = new BookListWidget(this, type);
    this->m_VScrollBar = new QScrollBar(Qt::Vertical, this);
    this->mainLayout = new QHBoxLayout(this);

    this->mainLayout->addWidget(this->m_BookListWidget);
    this->mainLayout->addWidget(this->m_VScrollBar);
    this->mainLayout->setMargin(0);
    this->mainLayout->setSpacing(0);
    this->setLayout(mainLayout);
}

void MyLibraryWidget::createConnections()
{
    QObject::connect(this->m_VScrollBar, SIGNAL(valueChanged(int)),
                     this, SLOT(displayListView(int)));
    QObject::connect(this, SIGNAL(SendReSizeSignal(int,int)),
                     this->m_BookListWidget->getBookListView(), SLOT(reSizeSlot(int,int)));
}

void MyLibraryWidget::displayListView(int len)
{
    this->m_BookListWidget->getBookListView()->move(0, -len);
}

void MyLibraryWidget::resizeEvent(QResizeEvent *event)
{
    int width = this->size().width()-m_VScrollBar->width();
    int column = width/(sysinclude::WIDTH);
    column = width/(sysinclude::WIDTH)==0 ? 1 : column;

    int booksize = this->m_BookListWidget->getBookListView()->getBookSize();
    int row = booksize/column;
    row = booksize%column==0 ? row : (row+1) ;

    if(height()>=row*(sysinclude::HEIGHT))
    {
        m_VScrollBar->setMinimum(0);
        m_VScrollBar->setMaximum(0);
        m_VScrollBar->setHidden(true);
    }
    else
    {
        m_VScrollBar->setHidden(false);
        int itemHeight = (sysinclude::HEIGHT)+(sysinclude::GRAP);
        m_VScrollBar->setMinimum(0);
        int max = row*itemHeight-height();
        int pageStep = height()-max;
        m_VScrollBar->setMaximum(max);
        m_VScrollBar->setPageStep(pageStep);
        m_VScrollBar->setSingleStep(10);
    }

    int listViewHeight = row*((sysinclude::HEIGHT)+(sysinclude::GRAP));
    listViewHeight = listViewHeight > this->size().height() ? listViewHeight : this->size().height();
    this->m_BookListWidget->getBookListView()->resize(this->size().width(),listViewHeight);

    emit SendReSizeSignal(row,column);

    QWidget::resizeEvent(event);
}

BookListWidget* MyLibraryWidget::getBookListWidget() const
{
    return this->m_BookListWidget;
}

