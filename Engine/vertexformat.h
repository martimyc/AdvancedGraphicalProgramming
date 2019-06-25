#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#include <vector>

struct VertexAttribute
{
    bool enabled = false;
    int offset = 0;
    int ncomp = 0;
};

class VertexFormat
{
public:
    void AddVertexAtribute(int offset, int ncomp)
    {
        attributes.push_back(VertexAttribute());
        VertexAttribute& attribute = attributes.back();

        attribute.enabled = true;
        attribute.offset = offset;
        attribute.ncomp = ncomp;
        size += ncomp * sizeof(float);
    }

    std::vector<VertexAttribute> attributes;
    int size = 0;
};

#endif // VERTEXFORMAT_H
