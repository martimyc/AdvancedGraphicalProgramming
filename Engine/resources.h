#ifndef RESOURCES_H
#define RESOURCES_H

#include <vector>

#include <QWidget>

namespace Ui {
class Resources;
}

class Resource;
class Mesh;

class Resources : public QWidget
{
    Q_OBJECT

public:
    explicit Resources(QWidget *parent = nullptr);
    ~Resources();

    Mesh* CreateMesh(QString name);

private:
    // Add
    void AddResource(Resource* resource);

    // Delete
    void DeleteResource(Resource* resource);


    bool AlreadySaved(Resource* resource) const;

    Ui::Resources *ui;
    std::vector<Resource*> resources;
};

#endif // RESOURCES_H
