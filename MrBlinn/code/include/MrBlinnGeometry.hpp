#ifndef MrBlinnGeometry_hpp
#define MrBlinnGeometry_hpp

// ----------------------------------------------------------------------------
// Vertices for triangle in NDC
constexpr GLsizei vboNdcTraingleVerticesStrideLen = 5;
std::vector<GLfloat> vboNdcTraingleVerticesData = {
  // positions  // colors
  -0.5f, +0.5f, 1.0f, 0.0f, 0.0f,
  +0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
  +0.5f, +0.5f, 0.0f, 0.0f, 1.0f
};

// ----------------------------------------------------------------------------
// Vertices for quad, buffer in triangle strip, NDC coords, do UVs in shader
constexpr GLsizei vboNdcQuadVerticesStrideLen = 2;
std::vector<GLfloat> vboNdcQuadVerticesData = {
  -1.0f, -1.0f,
  1.0f, -1.0f,
  -1.0f,  1.0f,
  1.0f,  1.0f,
};

// ----------------------------------------------------------------------------
// only positions in stride as we use this only to visually test positions in space with separate shader
constexpr GLuint eboDebugUnitCubeVerticesStrideLen = 0;
constexpr GLenum eboDebugUnitCubeIndicesGlType = GL_UNSIGNED_BYTE;
std::vector<GLubyte> eboDebugUnitCubeIndicesData = {
  0, 1, 2, 2, 1, 3, 4, 6, 5, 5, 6, 7, 0, 4, 1, 1, 4, 5, 6, 2, 7, 7, 2, 3, 4, 0, 6, 6, 0, 2, 5, 7, 1, 1, 7, 3
};
std::vector<GLfloat> eboDebugUnitCubeVerticesData = {
  -0.5f, -0.5f, -0.5f,
  -0.5f, +0.5f, -0.5f,
  +0.5f, -0.5f, -0.5f,
  +0.5f, +0.5f, -0.5f,
  -0.5f, -0.5f, +0.5f,
  -0.5f, +0.5f, +0.5f,
  +0.5f, -0.5f, +0.5f,
  +0.5f, +0.5f, +0.5f
};

// ----------------------------------------------------------------------------
constexpr GLuint eboTestPlaneVerticesStrideLen = 21;
constexpr GLenum eboTestPlaneIndicesGLType = GL_UNSIGNED_BYTE;
std::vector<GLubyte> eboTestPlaneIndicesData = {
  0, 1, 2, 2, 1, 3
};
std::vector<GLfloat> eboTestPlaneVerticesData = {
  // positions          // normals            // uv         // tangent            // bitangent          // colors           // specular         // shiness
  -0.5f, +0.0f, -0.5f,  +0.0f, +1.0f, +0.0f,  0.0f, 4.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, -1.0f,  1.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  -0.5f, +0.0f, +0.5f,  +0.0f, +1.0f, +0.0f,  0.0f, 0.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, -1.0f,  1.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, +0.0f, -0.5f,  +0.0f, +1.0f, +0.0f,  4.0f, 4.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, -1.0f,  1.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, +0.0f, +0.5f,  +0.0f, +1.0f, +0.0f,  4.0f, 0.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, -1.0f,  1.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f
};

// ----------------------------------------------------------------------------
// #define eboTestCubeVerticesStrideCount 24

constexpr GLuint eboTestCubeVerticesStrideLen = 21;
constexpr GLenum eboTestCubeIndicesGlType = GL_UNSIGNED_BYTE;
std::vector<GLubyte> eboTestCubeIndicesData = {
  // Back face
  0, 1, 2,
  2, 1, 3,
  // Front face
  4, 5, 6,
  6, 5, 7,
  // Left face
  8, 9, 10,
  10, 9, 11,
  // Right face,
  12, 13, 14,
  14, 13, 15,
  // Bottom face
  16, 17, 18,
  18, 17, 19,
  // Top face
  20, 21, 22,
  22, 21, 23
};

std::vector<GLfloat> eboTestCubeVerticesData = {
  // positions          // normals            // uv         // tangent            // bitangent          // colors           // specular         // shiness
  // Back face
  -0.5f, -0.5f, -0.5f,  +0.0f, +0.0f, -1.0f,  1.0f, 0.0f,   -1.0f, +0.0f, +0.0f,  +0.0f, +1.0f, +0.0f,  1.0f, 0.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  -0.5f, +0.5f, -0.5f,  +0.0f, +0.0f, -1.0f,  1.0f, 1.0f,   -1.0f, +0.0f, +0.0f,  +0.0f, +1.0f, +0.0f,  1.0f, 0.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, -0.5f, -0.5f,  +0.0f, +0.0f, -1.0f,  0.0f, 0.0f,   -1.0f, +0.0f, +0.0f,  +0.0f, +1.0f, +0.0f,  1.0f, 0.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, +0.5f, -0.5f,  +0.0f, +0.0f, -1.0f,  0.0f, 1.0f,   -1.0f, +0.0f, +0.0f,  +0.0f, +1.0f, +0.0f,  1.0f, 0.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  // Front face
  +0.5f, -0.5f, +0.5f,  +0.0f, +0.0f, +1.0f,  1.0f, 0.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +1.0f, +0.0f,  0.0f, 1.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, +0.5f, +0.5f,  +0.0f, +0.0f, +1.0f,  1.0f, 1.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +1.0f, +0.0f,  0.0f, 1.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  -0.5f, -0.5f, +0.5f,  +0.0f, +0.0f, +1.0f,  0.0f, 0.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +1.0f, +0.0f,  0.0f, 1.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  -0.5f, +0.5f, +0.5f,  +0.0f, +0.0f, +1.0f,  0.0f, 1.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +1.0f, +0.0f,  0.0f, 1.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  // Left face
  -0.5f, -0.5f, +0.5f,  -1.0f, +0.0f, +0.0f,  1.0f, 0.0f,   +0.0f, +0.0f, +1.0f,  +0.0f, +1.0f, +0.0f,  0.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  -0.5f, +0.5f, +0.5f,  -1.0f, +0.0f, +0.0f,  1.0f, 1.0f,   +0.0f, +0.0f, +1.0f,  +0.0f, +1.0f, +0.0f,  0.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  -0.5f, -0.5f, -0.5f,  -1.0f, +0.0f, +0.0f,  0.0f, 0.0f,   +0.0f, +0.0f, +1.0f,  +0.0f, +1.0f, +0.0f,  0.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  -0.5f, +0.5f, -0.5f,  -1.0f, +0.0f, +0.0f,  0.0f, 1.0f,   +0.0f, +0.0f, +1.0f,  +0.0f, +1.0f, +0.0f,  0.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  // Right face
  +0.5f, -0.5f, -0.5f,  +1.0f, +0.0f, +0.0f,  1.0f, 0.0f,   +0.0f, +0.0f, -1.0f,  +0.0f, +1.0f, +0.0f,  1.0f, 1.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, +0.5f, -0.5f,  +1.0f, +0.0f, +0.0f,  1.0f, 1.0f,   +0.0f, +0.0f, -1.0f,  +0.0f, +1.0f, +0.0f,  1.0f, 1.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, -0.5f, +0.5f,  +1.0f, +0.0f, +0.0f,  0.0f, 0.0f,   +0.0f, +0.0f, -1.0f,  +0.0f, +1.0f, +0.0f,  1.0f, 1.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, +0.5f, +0.5f,  +1.0f, +0.0f, +0.0f,  0.0f, 1.0f,   +0.0f, +0.0f, -1.0f,  +0.0f, +1.0f, +0.0f,  1.0f, 1.0f, 0.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  // Bottom face
  -0.5f, -0.5f, +0.5f,  +0.0f, -1.0f, +0.0f,  0.0f, 1.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, +1.0f,  0.0f, 1.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  -0.5f, -0.5f, -0.5f,  +0.0f, -1.0f, +0.0f,  0.0f, 0.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, +1.0f,  0.0f, 1.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, -0.5f, +0.5f,  +0.0f, -1.0f, +0.0f,  1.0f, 1.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, +1.0f,  0.0f, 1.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, -0.5f, -0.5f,  +0.0f, -1.0f, +0.0f,  1.0f, 0.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, +1.0f,  0.0f, 1.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  // Top face
  -0.5f, +0.5f, -0.5f,  +0.0f, +1.0f, +0.0f,  0.0f, 1.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, -1.0f,  1.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  -0.5f, +0.5f, +0.5f,  +0.0f, +1.0f, +0.0f,  0.0f, 0.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, -1.0f,  1.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, +0.5f, -0.5f,  +0.0f, +1.0f, +0.0f,  1.0f, 1.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, -1.0f,  1.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f,
  +0.5f, +0.5f, +0.5f,  +0.0f, +1.0f, +0.0f,  1.0f, 0.0f,   +1.0f, +0.0f, +0.0f,  +0.0f, +0.0f, -1.0f,  1.0f, 0.0f, 1.0f,   0.5f, 0.5f, 0.5f,   32.0f
};

// ----------------------------------------------------------------------------

#endif // MrBlinnGeometry_hpp
