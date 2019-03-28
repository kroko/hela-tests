#include "MrBlinnNucleus.hpp"

namespace hln = hela::nucleus;

// ----------------------------------------------------------------------------
void MrBlinn::draw() {

  // set default framebuffer
  // no GL_DRAW_FRAMEBUFFER on mali
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, sizeWindow.x, sizeWindow.y);

  glClearColor(
               (std::sin(m_currTime + 0.0f) + 1.1f) / 2.2f,
               (std::cos(m_currTime + 2.0f) + 1.1f) / 2.2f,
               (std::cos(m_currTime + 4.0f) + 1.1f) / 2.2f,
               0.5f
               );
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//  ndcTriangleDraw();

  testPlaneDraw();
  testCubeDraw();

  // Check OpenGL error
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    spdlog::error("OpenGL error: {0:d} (0x{0:x})", err);
  }

}
