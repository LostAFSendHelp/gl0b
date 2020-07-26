#pragma once
#include <GL/glew.h>
#include "../GL0b/GL0bVertexArray.h"
#include "../Progam/GL0bProgram.h"

const char* gl0bGetStatus(GLenum statusType, GLint unit);

class GL0bRenderer {
public:
    void drawElements(const GL0bVertexArray& va, GL0bProgram& pr);
    void clear();

    static GL0bRenderer& shared;
};