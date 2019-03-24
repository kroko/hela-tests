#ifndef HelloFBdevGeometry_hpp
#define HelloFBdevGeometry_hpp

// Vertices for triangle in NDC
constexpr GLsizei vboNdcTraingleVerticesStrideLen = 5;
std::vector<GLfloat> vboNdcTraingleVerticesData = {
  // positions  // colors
  -0.5f, +0.5f, 1.0f, 0.0f, 0.0f,
  +0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
  +0.5f, +0.5f, 0.0f, 0.0f, 1.0f
};

#endif // HelloFBdevGeometry_hpp
