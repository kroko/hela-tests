#ifndef warp_shader_functions_hpp
#define warp_shader_functions_hpp

// No RAIIs, just functions

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "nucleus/Nucleus.hpp"

namespace warp { namespace shader {

  // ----------------------------------------------------------------------------
  std::string shaderFileRead(const std::string shaderFilePath) {
    std::string shaderCode;
    std::ifstream shaderStream(shaderFilePath, std::ios::in);
    try
    {
      shaderStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      if (shaderStream.is_open()) {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
      }
      else{
        throw std::invalid_argument(std::string("ERROR: shaderFileRead: Did not throw, but file is not open..."));
      }
    }
    catch (std::ios_base::failure& e) {
      throw std::runtime_error(std::string("ERROR: shaderFileRead: Base I/O error for: " + shaderFilePath + " Exception: " + e.what() ));
    }
    catch (...) {
      throw std::runtime_error(std::string("ERROR: shaderFileRead: Shader file not read, some error for: " + shaderFilePath));
    }
    return shaderCode;
  }

  // ----------------------------------------------------------------------------
  std::string shaderFileRead(const char* shaderFilePath) {
    return shaderFileRead(std::string(shaderFilePath));
  }

  // ----------------------------------------------------------------------------
  GLuint shaderCreateAndCompileShader(const std::string shaderSource, const GLuint shaderType) {
    if (shaderSource.empty()) {
      throw std::invalid_argument(std::string("ERROR: shaderCreateAndCompileShader: Shader source empty"));
    }
    GLuint id = glCreateShader(shaderType);
    std::cout << "shaderCreateAndCompileShader: Compiling shader source that might have ID(" << id << ")" << std::endl;
    char const * shaderSourcePtr = shaderSource.c_str();
    glShaderSource(id, 1, &shaderSourcePtr , NULL);
    glCompileShader(id);
    GLint resultCode = GL_FALSE;
    GLint resultLogLen;
    glGetShaderiv(id, GL_COMPILE_STATUS, &resultCode);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &resultLogLen);
    if (resultCode == GL_FALSE) {
      if (resultLogLen > 0) {
        std::vector<char> errMsg(static_cast<std::size_t>(resultLogLen) + 1);
        glGetShaderInfoLog(id, resultLogLen, NULL, &errMsg[0]);
        std::cerr << &errMsg.front() << std::endl;
      }
      throw std::runtime_error(std::string("ERROR: shaderCreateAndCompileShader: Shader not compiled, see error above)."));
    }
    return id;
  }

  // ----------------------------------------------------------------------------
  GLuint shaderCreateAndLinkProgram(const std::vector<GLuint> shaderIds, const bool detachAndDelete = true) {
    GLuint id = glCreateProgram();
    std::cout << "shaderCreateAndLinkProgram: Creating and linking program that might have ID(" << id << ")" << std::endl;
    // TODO: check for glCreateProgram() error
    for (auto& sId : shaderIds) {
      if (sId == 0) {
        throw std::runtime_error(std::string("ERROR: shaderCreateAndLinkProgram: Will not attach shader with ID(0) to program with ID(" + std::to_string(id) + ")"));
      }
      else {
        std::cout << "shaderCreateAndLinkProgram: Attaching shader source with ID(" << sId << ") to program with ID(" << id << ")" << std::endl;
        glAttachShader(id, sId);
      }
    }

    glLinkProgram(id);
    GLint resultCode = GL_FALSE;
    GLint resultLogLen;
    glGetProgramiv(id, GL_LINK_STATUS, &resultCode);
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &resultLogLen);
    if (resultCode == GL_FALSE) {
      if (resultLogLen > 0) {
        std::vector<char> errMsg(static_cast<std::size_t>(resultLogLen) + 1);
        glGetProgramInfoLog(id, resultLogLen, NULL, &errMsg[0]);
        std::cerr << &errMsg.front() << std::endl;
      }
      throw std::runtime_error(std::string("ERROR: shaderCreateAndLinkProgram: Program not linked, see error above."));
    }

    if (detachAndDelete) {
      for (auto& sId : shaderIds) {
        std::cout << "shaderCreateAndLinkProgram: After program with ID(" << id << ") creation detaching and deleting shader source with ID(" << sId << ") from memory" << std::endl;
        glDetachShader(id, sId);
        glDeleteShader(sId);
      }
    }
    return id;
  }

} }

#endif // warp_shader_functions_hpp


