#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <QString>
#include <QTreeWidgetItem>

class QVBoxLayout;

class Component;

class Entity : public QTreeWidgetItem
{
public:
    Entity(QString& name, Entity *parent = nullptr);

    void SetName(QString& name);

    //Component functions
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    //Inspector
    QVBoxLayout* GenerateWidgets();

private:
    std::vector<Entity*> childs;
    std::vector<Component*> components;
};

#endif // ENTITY_H
