#include "entitymanager.h"
#include "ui_entitymanager.h"

#include <iostream>

#include <QString>

#include "entity.h"
#include "mainwindow.h"
#include "transform.h"

EntityManager::EntityManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityManager)
{
    ui->setupUi(this);

    QString name ("Root");
    root = new Entity(name);

    //Add transform
    Component* transform = new Transform(root);
    root->AddComponent(transform);

    //Add it to widget hirarchy
    ui->treeWidget->addTopLevelItem(root);

    //Connect buttons
    connect(ui->createButton, SIGNAL(clicked()), this, SLOT(createEntityButton()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteEntityButton()));
}

EntityManager::~EntityManager()
{
    delete ui;
}

Entity* EntityManager::CreateEntity(Entity* parent, QString name)
{
    if(name == NULL)
    {
        //Name
        name = "Entity_" + QString::number(entities.size());
    }

    //Ensure parent is not null
    if(parent == nullptr)
    {
        parent = root;
    }

    //Create & add to parent as child
    Entity* new_entity = new Entity( name, parent);
    parent->addChild(new_entity);
    entities.push_back(new_entity);

    //Add transform
    Component* transform = new Transform(new_entity);
    new_entity->AddComponent(transform);

    return new_entity;
}

void EntityManager::DeleteEntity(Entity* del)
{
    if(del == root)
    {
        std::cout << "EntityManager: Root can not be deleted" << std::endl;
        return;
    }

    for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
    {
        if(*it == del)
        {
            entities.erase(it);

            for(int i = 0; i < del->childCount(); i++)
            {
                DeleteEntity(static_cast<Entity*>(del->child(i)));
            }

            del->parent()->removeChild(del);
            del->DeleteAllComponents();
            delete del;
            return;
        }
    }

    std::cout << "EntityManager: Could not find entity to delete" << std::endl;
}

Entity* EntityManager::GetFocused() const
{
    if(ui->treeWidget->selectedItems().size() > 0)
        return static_cast<Entity*>(ui->treeWidget->selectedItems().first());
    return nullptr;
}

const QTreeWidget* EntityManager::GetTreeWidget() const
{
    return ui->treeWidget;
}

void EntityManager::DrawEntities() const
{
    for(std::vector<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
    {
        (*it)->Draw();
    }
}

//Slots
void EntityManager::createEntityButton()
{
    Entity* focused = GetFocused();
    if(focused != nullptr)
        CreateEntity(focused);
    else
        CreateEntity();
}

void EntityManager::deleteEntityButton()
{
    Entity* focused = GetFocused();
    if(focused != nullptr)
        DeleteEntity(focused);
    else
        std::cout << "EntityManager: No item selected to delete" << std::endl;
}
