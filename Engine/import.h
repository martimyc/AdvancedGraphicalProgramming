#ifndef IMPORT_H
#define IMPORT_H

#include <QString>
#include "vertexformat.h"

class ImportMesh
{
public:
    ImportMesh(QString name, size_t num_vertices, unsigned char* data, size_t dataSize, unsigned int* indicies, size_t indiciesCount, VertexFormat* vertexFormat) :
        name(name), num_vertices(num_vertices), data(data), dataSize(dataSize), indicies(indicies), indiciesCount(indiciesCount), vertexFormat(vertexFormat)
    {}

    ~ImportMesh()
    {
        if (data != nullptr)
        {
            delete [] data;
            data = nullptr;
        }

        if (indicies != nullptr)
        {
            delete [] indicies;
            indicies = nullptr;
        }
    }

    size_t num_vertices;

    unsigned char* data;
    size_t dataSize;

    unsigned int* indicies;
    size_t indiciesCount;

    VertexFormat* vertexFormat;

    QString name;
};

#endif // IMPORT_H
