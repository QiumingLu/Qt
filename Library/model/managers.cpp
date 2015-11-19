#include "managers.h"

Managers::Managers()
{
}

Managers::~Managers()
{
}

int Managers::getId() const
{
    return this->id;
}

void Managers::setId(int id)
{
    this->id = id;
}

int Managers::getManagerId() const
{
    return this->managerId;
}

void Managers::setManagerId(int managerId)
{
    this->managerId = managerId;
}
