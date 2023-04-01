//
//  Shader.cpp
//  khulagl
//
//  Created by Anirudh on 21/03/23.
//

#include "Shader.hpp"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath):
    m_RendererID(0) {
    ShaderSource source = parseShader(filepath);
    
    m_RendererID = createShader(source.Vertex, source.Fragment);
        
    glUseProgram(m_RendererID);
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

void Shader::bind() const {
    glUseProgram(m_RendererID);
}

void Shader::unbind() const {
    glUseProgram(0);
}

ShaderSource Shader::parseShader(const std::string& filePath) {
    std::ifstream stream(filePath);
    std::stringstream ss[2];
    
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    ShaderType mode = ShaderType::NONE;
    std::string line;
    
    while (getline(stream, line)) {
        if (line.find("#Shader") != std::string::npos) {
            if (line.find("Vertex") != std::string::npos) {
                mode = ShaderType::VERTEX;
            }
            else if (line.find("Fragment") != std::string::npos) {
                mode = ShaderType::FRAGMENT;
            }
            
            continue;
        }
        
        ss[(int)mode] << line << '\n';
    }
    
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src =  source.c_str();
    
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    /* Error handling */
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    
    if (status == GL_TRUE) {
        return id;
    }
    
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(sizeof(char) * length);
    
    glGetShaderInfoLog(id, GL_INFO_LOG_LENGTH, &length, message);
    
    std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? " vertex " : " fragment ") << "shader" << std::endl;
    std::cout << message << std::endl;
    
    return 0;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    
    /* Error handling */
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

int Shader::getUniformLocation(const std::string& name) {
    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
        return uniformLocationCache[name];
    }
    
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    
    if (location == -1) {
        std::cout << "No active uniform variable with name " << name << " found" << std::endl;
    }
    
    uniformLocationCache[name] = location;
    
    return location;
}

void Shader::setUniform4f(const std::string& name, float v1, float v2, float v3, float v4) {
    glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
}
