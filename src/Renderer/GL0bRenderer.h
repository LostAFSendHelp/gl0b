#pragma once
#include <GL/glew.h>
#include "../GL0b/GL0bVertexArray.h"
#include "../Progam/GL0bProgram.h"

const char* gl0bGetStatus(GLenum statusType, GLint unit);

class GL0bRenderer {
public:
    explicit GL0bRenderer(const GL0bProgram& program);
    ~GL0bRenderer();

    void drawElements(const GL0bVertexArray& va);
    void clear();

private:
    GL0bProgram mProgram;
};