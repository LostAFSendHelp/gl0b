#include "../Renderer/GL0bRenderer.h"
#include "GL0bShader.h"
#include <iostream>
#include <fstream>
#include <memory>

GL0bShader::GL0bShader(GLenum type, const std::string& path): mID(glCreateShader(type))
{
    std::ifstream reader(path);
    std::string line;

    while (std::getline(reader, line)) {
        mSource.append(line + "\n");
    }
    
    reader.close();
    auto sourcePointer = mSource.c_str();
    std::cout << mSource << std::endl;
    
    glShaderSource(mID, 1, &sourcePointer, nullptr);
    glCompileShader(mID);
    auto status = gl0bGetStatus(GL_COMPILE_STATUS, mID);
    
    if (status != nullptr) {
        std::cout << "SHADER COMPILATION ERROR [ID " << mID << "]: " << status << std::endl;
        delete[] status;
    }
    else {
        std::cout << "SHADER COMPILATION SUCCESS: " << mID << std::endl;
    }
}

GL0bShader::~GL0bShader()
{
}

const unsigned int& GL0bShader::id()
{
    return mID;
}

const std::string& GL0bShader::source()
{
    return mSource;
}

void GL0bShader::dispose() const
{
    int deleteStatus;
    glGetShaderiv(mID, GL_DELETE_STATUS, &deleteStatus);

    if (deleteStatus == GL_FALSE) {
        glDeleteShader(mID);
        std::cout << "SHADER DELETED: " << mID << std::endl;
    }
}
