#include "sample_instances.h"

namespace gl0b {

    std::vector<Point> generate_vertex_samples() {
        return {
            {-.25f, .25f, .25f, 0.0f, 0.0f, 1.0f },     // TLF
            { .25f, .25f, .25f, 1.0f, 0.0f, 0.0f },     // TRF
            { .25f, -.25f, .25f, 1.0f, 1.0f, 0.0f},     // BRF
            {-.25f, -.25f, .25f, 0.0f, 1.0f, 0.0f},     // BLF
            
            {-.25f, .25f, -.25f, 0.0f, 0.0f, 1.0f },    // TLB
            { .25f, .25f, -.25f, 1.0f, 0.0f, 0.0f },    // TRB
            { .25f, -.25f, -.25f, 1.0f, 1.0f, 0.0f},    // BRB
            {-.25f, -.25f, -.25f, 0.0f, 1.0f, 0.0f}     // BLB
        };
    }

    std::vector<unsigned int> generate_index_samples() {
        return {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
        };
    }

    GL0bVertexArray generate_va_sample(const std::vector<Point>& vertices, const std::vector<unsigned int>& indices) {
        auto va = GL0bVertexArray{ true };
        va.genBuffer<GL0bArrayBuffer>();
        va.genBuffer<GL0bIndexBuffer>();
        va.push(vertices, true);
        va.push(indices, true);
        va.unbind();

        return std::move(va);
    }
}