#ifndef COMPONENT_H
#define COMPONENT_H

#include <QWidget>

class Entity;

class Component
{
public:
    Component(Entity* entity);
    virtual ~Component();

    virtual QWidget* GenerateWidget() = 0;

private:
    Entity* entity;
};

#endif // COMPONENT_H
