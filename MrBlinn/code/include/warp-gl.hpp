#ifndef warp_gl_hpp
#define warp_gl_hpp

#define warpGlVertexAttribPointerOffset(i) (GLvoid*)(uintptr_t)(i)
#define warpGlIndicesPtr0 (GLvoid*)(uintptr_t)(0)
#define warpGlIndicesPtr(i) (GLvoid*)(uintptr_t)(i)
#define UNBIND 0
#define UNUSE 0

namespace warp { namespace gl {

  struct BufferHolder_t {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    BufferHolder_t(): vao(0), vbo(0), ebo(0) {}
  };


} }

#endif // warp_gl_hpp
