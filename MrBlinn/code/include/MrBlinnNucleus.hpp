#ifndef MrBlinnNucleus_hpp
#define MrBlinnNucleus_hpp

// --------------------------------
// Get Nucleus and OpenGL motor with it
#include "nucleus/Nucleus.hpp"

// --------------------------------
// As of writing 0.9.9.4

#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4

#include "glm/gtc/constants.hpp" // glm::pi
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

// #define GLM_ENABLE_EXPERIMENTAL
// #include "glm/gtx/string_cast.hpp" // glm::to_string
// #include "glm/gtx/rotate_vector.hpp"
// #include "glm/gtx/transform.hpp"
// #include "glm/gtx/vector_angle.hpp"
// #include "glm/gtc/matrix_inverse.hpp"

// --------------------------------

#include "warp-gl.hpp"

#include "warp-helpers.hpp"

#include "warp-materials.hpp"

#include "warp-time.hpp"
#include "warp-camera.hpp"
#include "warp-controls.hpp"


// --------------------------------

class MrBlinn : public hela::nucleus::Nucleus {

public:

  static void prepareNucleus(hela::nucleus::Nucleus::NucleusSettings * prepNucleus);
  static void prepareMotor(hela::motor::Motor::MotorSettings * prepMotor);

public:

  void setup() override;
  void update() override;
  void draw() override;
  void cleanup() override;

  void eventKeyboardKey(unsigned short key, int action) override;
  void eventMousePositionDelta(int xpos, int ypos) override;
  // void eventMouseButton(unsigned short button, int action) override;
  // void eventMouseWheel(int xoffset, int yoffset) override;
   void eventWindowResize(int width, int height) override;
  // void eventWindowDrop(int count, const char** paths) override;

private:

  float m_currTime;

  GLuint m_helloShaderProgram;
  GLuint m_helloVAO;
  GLuint m_helloVBO;
  GLuint m_uTimeLoc;

  // size holders
  glm::ivec2 sizeWindow;
  glm::ivec2 sizeBuffer;

  // update subroutines
  void timeSetup();
  void timeUpdate();
  void controlsUpdate();
  void cameraUpdate();

  // Materials
  void materialSetup();
  warp::materials::TexturePackBlinn_t tex_TC002;
  warp::materials::TexturePackBlinn_t tex_DIRT006;

  // Shaders
  void shaderSetup();
  GLuint shaderBlinn01Program;
  //  GLuint shaderDebugUnitCubeProgram;
  //  GLuint shaderQTSNdcProgram;

  // Framebuffer - 01
  GLuint framebuffer01FBO, framebuffer01RBO, framebuffer01TBO;

  // Geometry - test cube
  warp::gl::BufferHolder_t testCubeBuff;

  // Geometry - test plane
  warp::gl::BufferHolder_t testPlaneBuff;

  // Geometry - debug cube
  GLuint debugUnitCubeVAO, debugUnitCubeVBO, debugUnitCubeEBO;

  // Geometry - quad ndc
  GLuint qtsndcVAO, qtsndcVBO;


  void ndcTriangleSetup();
  void ndcTriangleDraw();
  
  void testCubeSetup();
  void testCubeDraw();
  void testPlaneSetup();
  void testPlaneDraw();

  warp::time::TimeHolder_t<> timerProgramHolder;
  warp::controls::ControlsWASDState_t controlsWasdState;
  warp::controls::ControlsMouseState_t controlsMouseState;
  warp::camera::CameraControllerWasdSimple cameraController1;

  glm::mat4 projection = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 model = glm::mat4(1.0f);

}; // MrBlinn

#endif // MrBlinnNucleus_hpp
