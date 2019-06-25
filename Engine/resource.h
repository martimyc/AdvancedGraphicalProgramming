#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

#include <qstring.h>

enum RESOURCE_TYPE
{
    NO_TYPE = 0,
    MESH
};

class Mesh;

class Resource
{
public:
    Resource(RESOURCE_TYPE type): type(type)
    {}

    virtual ~Resource()
    {}

    // Basic Methods
    virtual void Update() = 0;
    virtual void Destroy() = 0;

    // Setters
    void SetName(QString name) {this->name = name;}

    // Getters
    const QString GetName() const { return name;}
    RESOURCE_TYPE GetType() const {return type;}

    // Type Getters
    virtual Mesh* AsMesh() {return nullptr;}

private:
    RESOURCE_TYPE type;
    QString name;
};

#endif // RESOURCE_H
