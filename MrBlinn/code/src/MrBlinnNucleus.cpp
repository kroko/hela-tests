#include "MrBlinnNucleus.hpp"
#include "MrBlinnAssets.hpp"

#include "warp-shader-functions.hpp"
#include "warp-texture.hpp"
//#define STB_IMAGE_IMPLEMENTATION

// make alias for calls to hela::nucleus
namespace hln = hela::nucleus;

// ----------------------------------------------------------------------------
void MrBlinn::prepareNucleus(hln::Nucleus::NucleusSettings* prepNucleus) {
  // ! All these settings are optional, Hela has defaults

  prepNucleus->setWindowSize(1920, 1080);
  prepNucleus->setUserInputAllowed(true); // disable user input for Hello FBdev
  prepNucleus->setPerfStats(true);
  // These will apply only to devbench, FBdev ignores
  prepNucleus->setWindowFitMonitor(true);
  prepNucleus->setFullScreen(false);
  prepNucleus->setResizable(true);
  prepNucleus->setBorderless(false);
  prepNucleus->setAlwaysOnTop(true);
  prepNucleus->setCaptureCursor(true);
  prepNucleus->setTitle("Hello FBdev");

}

// ----------------------------------------------------------------------------
void MrBlinn::prepareMotor(hela::motor::Motor::MotorSettings* prepMotor) {
  // ! All these settings are optional, Hela has defaults

  prepMotor->setMsaa(0);
  prepMotor->setVsync(true);
  prepMotor->setColorBufferChannelBits(8);
  prepMotor->setDepthBufferEnabled(true); // set depth buffer disabled
  prepMotor->setDepthBufferBits(24); // whateva
  prepMotor->setStencilBufferEnabled(false); // set stencil buffer disabled
  prepMotor->setStencilBufferBits(8); // whateva

  // These will apply only to devbench, FBdev ignores
  prepMotor->setVersion(3, 3);
  prepMotor->setCoreProfile(true); // we use vao, so we need core context

}

// ----------------------------------------------------------------------------
void MrBlinn::setup() {

  // --------------------------------
  spdlog::info("Hello FBdev greets you at window size {}x{}", hln::getWindowWidth(), hln::getWindowHeight());

  // --------------------------------
  sizeWindow = glm::ivec2(hln::getWindowWidth(), hln::getWindowHeight());
  sizeBuffer = sizeWindow;

  // --------------------------------
  glViewport(0, 0, sizeWindow.x, sizeWindow.y);

  // --------------------------------
  // Front face winding
  glFrontFace(GL_CCW);

  // --------------------------------
  // Cull
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  // --------------------------------
  // Enable depth test & accept closer fragment
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE); // enable writing to the depth buffer
  glDepthFunc(GL_LESS);

  // --------------------------------
  // Stencil test
  //glEnable(GL_STENCIL_TEST);
  //glStencilMask(0xFF); // enable write to stencil buffer in all bits
  //glStencilFunc(GL_ALWAYS, 0, 0xFF); // pass always
  //glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // always keep
  ////glStencilOpSeparate(...)

  // --------------------------------
  // Enable blending
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glBlendFuncSeparate(...)
  //glBlendColor(...)
  //glBlendEquation(...)

  // --------------------------------
#if defined(GL_FRAMEBUFFER_SRGB)
  // Just in case align with EGL FBdev, although GL_FRAMEBUFFER_SRGB on devbench should be disabled by default
  if (glIsEnabled(GL_FRAMEBUFFER_SRGB)) {
    spdlog::trace("GL_FRAMEBUFFER_SRGB was indeed enabled, disabling");
    glDisable(GL_FRAMEBUFFER_SRGB);
  }
#endif

  // --------------------------------
  shaderSetup();
  materialSetup();

  // --------------------------------
//  ndcTriangleSetup();
  testPlaneSetup();
  testCubeSetup();

  // --------------------------------
  cameraController1 = warp::camera::CameraControllerWasdSimple(glm::vec3(0.0f, 1.4f, 3.0f));

}

// ----------------------------------------------------------------------------
void MrBlinn::timeSetup() {
  timerProgramHolder.curr = hln::getElapsedSeconds();
  timerProgramHolder.prev = timerProgramHolder.curr;
}

// ----------------------------------------------------------------------------
void MrBlinn::shaderSetup() {
  {
    using namespace warp::shader;
    m_helloShaderProgram = shaderCreateAndLinkProgram({
      shaderCreateAndCompileShader(shaderFileRead(hln::constructAssetPathString(ASSET_SHADER_HELLO_VERT)), GL_VERTEX_SHADER),
      shaderCreateAndCompileShader(shaderFileRead(hln::constructAssetPathString(ASSET_SHADER_HELLO_FRAG)), GL_FRAGMENT_SHADER)
    });
  }

  {
    using namespace warp::shader;
    shaderBlinn01Program = shaderCreateAndLinkProgram({
      shaderCreateAndCompileShader(shaderFileRead(hln::constructAssetPathString(ASSET_SHADER_BLINN01_VERT)), GL_VERTEX_SHADER),
      shaderCreateAndCompileShader(shaderFileRead(hln::constructAssetPathString(ASSET_SHADER_BLINN01_FRAG)), GL_FRAGMENT_SHADER)
    });
  }
}

// ----------------------------------------------------------------------------
void MrBlinn::materialSetup() {
  tex_TC002.base = warp::texture::textureLoadFromDisk(hln::constructAssetPathString(ASSET_TEXTURE_TC002_ALBEDO), true);
  tex_TC002.prefUnit = 2;

  tex_DIRT006.base = warp::texture::textureLoadFromDisk(hln::constructAssetPathString(ASSET_TEXTURE_DIRT006_ALBEDO), true);
  tex_DIRT006.prefUnit = 2;

}


// ----------------------------------------------------------------------------
void MrBlinn::cleanup() {

  glBindVertexArray(UNBIND);
  glDeleteVertexArrays(1, &m_helloVAO);

  glBindBuffer(GL_ARRAY_BUFFER, UNBIND);
  glDeleteBuffers(1, &m_helloVBO);

  glUseProgram(UNUSE);
  glDeleteProgram(m_helloShaderProgram);

}
