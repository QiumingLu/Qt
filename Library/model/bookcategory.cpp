#include "bookcategory.h"

BookCateGory::BookCateGory()
{
}

BookCateGory::~BookCateGory()
{
}

int BookCateGory::getCateGoryId() const
{
    return this->categoryId;
}

void BookCateGory::setCateGoryId(int categoryId)
{
    this->categoryId = categoryId;
}

QString BookCateGory::getCateGoryName() const
{
    return this->categoryName;
}

void BookCateGory::setCateGoryName(const QString &categoryName)
{
    this->categoryName = categoryName;
}
