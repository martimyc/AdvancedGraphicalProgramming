#include "entity.h"

#include <iostream>

#include <QBoxLayout>

#include "globals.h"
#include "component.h"

Entity::Entity(QString& name, Entity* parent): QTreeWidgetItem(parent)
{
    SetName(name);
}

void Entity::SetName(QString &name)
{
    this->setText(0,name);
}

void Entity::AddComponent(Component* component)
{
    components.push_back(component);
}

void Entity::RemoveComponent(Component* component)
{
    for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
    {
        if(*it == component)
        {
            components.erase(it);
            return;
        }
    }

    std::cout << "Entity: All components removed from " << this->text(0).toStdString() << std::endl;
}

void Entity::DeleteAllComponents()
{
    for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
    {
        delete *it;
        *it = nullptr;
    }
    components.clear();

    std::cout << "Entity: Could not find child" << std::endl;
}

QVBoxLayout* Entity::GenerateWidgets()
{
    //Create Layout
    QVBoxLayout* layout = new QVBoxLayout;

    for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
    {
        //Add component widgets to layout
        layout->addWidget((*it)->GenerateWidget());

        //Add separation lines
        /*QWidget *horizontalLineWidget = new QWidget;
        horizontalLineWidget->setFixedHeight(2);
        horizontalLineWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        layout->addWidget(horizontalLineWidget);*/

        layout->addWidget((*it)->GenerateWidget());
    }

    //Return layout
    return layout;
}
