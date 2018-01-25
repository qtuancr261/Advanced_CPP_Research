#include "client.h"

client::client(int id, QString name)
    : id{id}, name{name}
{
    // default constructor
}

int client::getId() const
{
    return id;
}

void client::setId(int value)
{
    id = value;
}

QString client::getName() const
{
    return name;
}

void client::setName(const QString &value)
{
    name = value;
}


