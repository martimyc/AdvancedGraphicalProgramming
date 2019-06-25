#ifndef COMPONENT_H
#define COMPONENT_H

#include <QWidget>

class Entity;

class Component
{
public:
    Component(Entity* entity, bool draw = false);
    virtual ~Component();

    virtual QWidget* GenerateWidget() = 0;

private:
    Entity* entity;
    bool draw;
};

#endif // COMPONENT_H
