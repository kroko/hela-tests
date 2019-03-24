#include "HelloFBdevNucleus.hpp"
#include "HelloFBdevGeometry.hpp"
#include "HelloFBdevAssets.hpp"
#include "warp-shader-functions.hpp"
#include "warp-helpers.hpp"

// make alias for calls to hela::nucleus
namespace hln = hela::nucleus;

// ----------------------------------------------------------------------------
void HelloFBdev::setup() {

  // --------------------------------

  spdlog::info("Hello FBdev greets you at window size {}x{}", hln::getWindowWidth(), hln::getWindowHeight());

  // --------------------------------

  glViewport(0, 0, hln::getWindowWidth(), hln::getWindowHeight());
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glDisable(GL_DEPTH_TEST); // We set motor with no depth buffer for Hello FBdev, see prepareMotor()

  // --------------------------------

  {
    using namespace warp::shader;
    m_helloShaderProgram = shaderCreateAndLinkProgram({
      shaderCreateAndCompileShader(shaderFileRead(hln::constructAssetPathString(ASSET_SHADER_HELLO_VERT)), GL_VERTEX_SHADER),
      shaderCreateAndCompileShader(shaderFileRead(hln::constructAssetPathString(ASSET_SHADER_HELLO_FRAG)), GL_FRAGMENT_SHADER)
    });
  }

  // --------------------------------
  // This uses VAO to test GL_OES_vertex_array_object
  // No EBO for one triangle

  GLsizei vboNdcTraingleVerticesElSize = sizeof(decltype(vboNdcTraingleVerticesData)::value_type);
  glGenVertexArrays(1, &m_helloVAO);
  glBindVertexArray(m_helloVAO);
  glGenBuffers(1, &m_helloVBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_helloVBO);
  glBufferData(
               GL_ARRAY_BUFFER,
               warp::helpers::sizeofVector(vboNdcTraingleVerticesData),
               vboNdcTraingleVerticesData.data(),
               GL_STATIC_DRAW);
  glVertexAttribPointer(
                        glGetAttribLocation(m_helloShaderProgram, "aPos"),
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        vboNdcTraingleVerticesStrideLen * vboNdcTraingleVerticesElSize,
                        GLsizeiToGLvoid(0));
  glVertexAttribPointer(
                        glGetAttribLocation(m_helloShaderProgram, "aColor"),
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        vboNdcTraingleVerticesStrideLen * vboNdcTraingleVerticesElSize,
                        GLsizeiToGLvoid(2 * vboNdcTraingleVerticesElSize)
                        );
  glEnableVertexAttribArray(glGetAttribLocation(m_helloShaderProgram, "aPos"));
  glEnableVertexAttribArray(glGetAttribLocation(m_helloShaderProgram, "aColor"));
  glBindVertexArray(UNBIND);
  glBindBuffer(GL_ARRAY_BUFFER, UNBIND);

  // --------------------------------

  // ...

  // --------------------------------

  glUseProgram(m_helloShaderProgram);
  glBindVertexArray(m_helloVAO);
  m_uTimeLoc = glGetUniformLocation(m_helloShaderProgram, "uTime");

}

// ----------------------------------------------------------------------------
void HelloFBdev::draw() {

  float currTime = hln::getElapsedSeconds();
  glClearColor(
               (std::sin(currTime + 0.0f) + 1.1f) / 2.2f,
               (std::cos(currTime + 2.0f) + 1.1f) / 2.2f,
               (std::cos(currTime + 4.0f) + 1.1f) / 2.2f,
               0.5f
               );
  glClear(GL_COLOR_BUFFER_BIT); // depth disabled

  glUniform1f(m_uTimeLoc, currTime);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)vboNdcTraingleVerticesData.size() / vboNdcTraingleVerticesStrideLen);

  // Check OpenGL error
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    spdlog::error("OpenGL error: {0:d} (0x{0:x})", err);
  }

}

// ----------------------------------------------------------------------------
void HelloFBdev::cleanup() {

  glBindVertexArray(UNBIND);
  glDeleteVertexArrays(1, &m_helloVAO);

  glBindBuffer(GL_ARRAY_BUFFER, UNBIND);
  glDeleteBuffers(1, &m_helloVBO);

  glUseProgram(UNUSE);
  glDeleteProgram(m_helloShaderProgram);

}

// ----------------------------------------------------------------------------
void HelloFBdev::prepareNucleus(hln::Nucleus::NucleusSettings* prepNucleus) {
  // ! All these settings are optional, Hela has defaults

  prepNucleus->setWindowSize(640, 480);
  prepNucleus->setUserInputAllowed(false); // disable user input for Hello FBdev
  prepNucleus->setPerfStats(true);
  // These will apply only to devbench, FBdev ignores
  prepNucleus->setWindowFitMonitor(true);
  prepNucleus->setFullScreen(false);
  prepNucleus->setResizable(true);
  prepNucleus->setBorderless(false);
  prepNucleus->setAlwaysOnTop(true);
  prepNucleus->setCaptureCursor(false);
  prepNucleus->setTitle("Hello FBdev");

}

// ----------------------------------------------------------------------------
void HelloFBdev::prepareMotor(hela::motor::Motor::MotorSettings* prepMotor) {
  // ! All these settings are optional, Hela has defaults

  prepMotor->setMsaa(0);
  prepMotor->setVsync(true);
  prepMotor->setColorBufferChannelBits(8);
  prepMotor->setDepthBufferEnabled(false); // set depth buffer disabled
  prepMotor->setDepthBufferBits(24); // whateva
  prepMotor->setStencilBufferEnabled(false); // set stencil buffer disabled
  prepMotor->setStencilBufferBits(8); // whateva

  // These will apply only to devbench, FBdev ignores
  prepMotor->setVersion(3, 3);
  prepMotor->setCoreProfile(true); // we use vao, so we need core context

}
