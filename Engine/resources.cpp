#include "resources.h"
#include "ui_resources.h"

#include <iostream>

#include "resource.h"
#include "mesh.h"

Resources::Resources(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resources)
{
    ui->setupUi(this);
}

Resources::~Resources()
{
    delete ui;
}

Mesh* Resources::CreateMesh(QString name)
{
    Mesh* newMesh = new Mesh();
    newMesh->SetName(name);
    AddResource(newMesh);
    return newMesh;
}

void Resources::AddResource(Resource* resource)
{
    if(AlreadySaved(resource))
    {
        std::cout << "Resources: Resource already saved" << std::endl;
        return;
    }

    resources.push_back(resource);
    ui->listWidget->addItem(resource->GetName());
}

void Resources::DeleteResource(Resource* resource)
{
    for(std::vector<Resource*>::iterator it = resources.begin(); it != resources.end(); it++)
    {
        if(resource == *it)
        {
            resources.erase(it);
            return;
        }
    }

    std::cout << "Resources: could not delete resource, not found" << std::endl;
}

bool Resources::AlreadySaved(Resource* resource) const
{
    for(std::vector<Resource*>::const_iterator it = resources.begin(); it != resources.end(); it++)
    {
        if(resource == *it)
            return true;
    }
    return false;
}
