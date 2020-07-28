#pragma once
#include <vector>
#include "../Structures/Point.h"
#include "../GL0b/GL0bVertexArray.h"

namespace gl0b {
    
    std::vector<Point> generate_vertex_samples();

    std::vector<unsigned int> generate_index_samples();

    GL0bVertexArray generate_va_sample(const std::vector<Point>& vertices, const std::vector<unsigned int>& indices);
}