#include "booklistview.h"
#include <QGroupBox>
#include <QLabel>
#include <QList>
#include <QLineEdit>
#include <QPushButton>
#include "bookgroupbox.h"
#include "ui/mylibrarybox.h"
#include "core/sysinclude.h"
#include "core/systype.h"
#include "model/readers.h"
#include "model/borrow.h"
#include "model/sysenviroment.h"
#include "model/uniquebook.h"
#include "model/books.h"
#include "model/bookcategory.h"

BookListView::BookListView(QWidget *parent) :
    QListView(parent)
{
}

BookListView::~BookListView()
{
}
